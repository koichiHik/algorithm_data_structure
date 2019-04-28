
// STD
#include <iostream>
#include <string>

// STL
#include <vector>

using namespace std;

enum class NodeType : int {
  ROOT,
  INTERNAL_NODE,
  LEAF,
  NONE
};

string to_string(NodeType nodeType) {

  string val;
  switch(nodeType) 
  {
    case NodeType::ROOT:
      val = "root";        
      break;
    case NodeType::INTERNAL_NODE:
      val = "internal node";
      break;
    case NodeType::LEAF:
      val = "leaf";
      break;
    case NodeType::NONE:
      val = "none";
      break;
    default:
      val = "none";
      break;
  }

  return val;
}

class Node {
public:
  Node() 
   : id(-1), parentId(-1), 
   childIds(), depth(-1), 
   type(NodeType::NONE)
  {}

  int id;
  int parentId;
  vector<int> childIds;
  int depth;
  NodeType type;
};

vector<string> parseLineToTokens(const std::string& line) {
  vector<string> tokens;
  string token;
  for (int pos = 0; pos <= line.length(); pos++) {
    if (pos == line.length() || line[pos] == ' ') {
      tokens.push_back(token);
      token.clear();
    } else {
      token = token + line[pos];
    }
  }

  return tokens;
}

void parseLineForNode(const std::string& line, Node& node) {
  vector<string> tokens = parseLineToTokens(line);
  node.id = std::stoi(tokens[0]);
  int childNum = std::stoi(tokens[1]);
  for (int i = 0; i < childNum; i++) {
    node.childIds.push_back(std::stoi(tokens[i + 2]));
  }
}

void printResult(vector<Node>& vecNodes) {

  for (vector<Node>::const_iterator itr = vecNodes.cbegin();
       itr != vecNodes.cend();
       itr++) {
    cout << "node " << itr->id << ": parent =" << itr->parentId << ", depth = " 
    << itr->depth << ", " << to_string(itr->type) << ", [";

    if (itr->childIds.size() != 0) {
      for (int cur = 0; cur < itr->childIds.size()-1; cur++) {
        cout << itr->childIds[cur] << ", ";
      }
      cout << itr->childIds[itr->childIds.size()-1];
    }
    cout << "]" << endl;;
  }
}

int checkDepthRecursively(int nodeId, const vector<Node>& nodeVecs) {

  if (nodeVecs[nodeId].depth != -1) {
    return nodeVecs[nodeId].depth;
  } else if (nodeVecs[nodeId].parentId == -1) {
    return 0;
  }
  return checkDepthRecursively(nodeVecs[nodeId].parentId, nodeVecs) + 1;
}

NodeType checkNodeType(const Node& node) {

  if (node.parentId == -1) {
    return NodeType::ROOT;
  } else if (node.childIds.size() == 0) {
    return NodeType::LEAF;
  } else  {
    return NodeType::INTERNAL_NODE;
  }

}

void checkParent(int nodeId, vector<Node>& nodeVecs) {
  for (vector<int>::iterator itr = nodeVecs[nodeId].childIds.begin();
       itr != nodeVecs[nodeId].childIds.end();
       itr++) {
    nodeVecs[*itr].parentId = nodeId;
  }
}

int main(int, char**) {

  std::cout << __FILE__ << std::endl;

  // 1. Node Number 読み取り．
  string token;
  getline(cin, token);
  int nodeNum = stoi(token);

  // 2. 全行読み取り．
  vector<string> lines;
  for (int i = 0; i < nodeNum; i++) {
    string line;
    getline(cin, line);
    lines.push_back(line);
  }

  // 3. Node Vector の作成
  vector<Node> nodeVec(nodeNum, Node());

  // 4. lines をパース
  for (std::vector<string>::const_iterator itr = lines.cbegin();
       itr != lines.cend();
       itr++) {
    Node node;
    parseLineForNode(*itr, node);
    nodeVec[node.id] = node;
  }

  for (int i = 0; i < nodeVec.size(); i++) {
    checkParent(i, nodeVec);
    nodeVec[i].type = checkNodeType(nodeVec[i]);
    nodeVec[i].depth = checkDepthRecursively(i, nodeVec);
  }

  // 5. 結果のアウトプット
  printResult(nodeVec);

  return 0;
}
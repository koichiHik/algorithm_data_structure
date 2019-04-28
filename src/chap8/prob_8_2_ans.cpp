
// STD
#include <iostream>
#include <string>

// STL
#include <vector>

#define MAX 100005
#define NIL -1

// 構造体宣言
struct Node {
  int parent;
  int leftChild;
  int rightSib;
};

// Nodeを保持する配列．
Node T[MAX];
int n, D[MAX];

using namespace std;

void print(int u) {

  int i, c;
  cout << "node " << u << "; ";
  cout << "parent = " << T[u].parent << ", ";
  cout << "depth = " << D[u] << ", ";

  if (T[u].parent == NIL) {
    cout << "root, ";
  } else if (T[u].leftChild == NIL) {
    cout << "leaf, ";
  } else {
    cout << "internal node, ";
  }

  cout << "[";

  for (int i = 0, c = T[u].leftChild; c != NIL; i++, c = T[c].rightSib) {
    if (i != 0) {
      cout << ", ";
    }
    cout << c;
  }

  cout << "]" << endl;

}

void rec(int u, int p) {

  D[u] = p;
  // Update for sibling direction.
  if (T[u].rightSib != NIL) {
    rec(T[u].rightSib, p);
  }

  // Update for left most child direction.
  if (T[u].leftChild != NIL) {
    rec(T[u].leftChild, p + 1);
  }
}

int main(int, char**) {

  cin >> n;

  // Initializing n elements.
  for (int i = 0; i < n; i++) {
    T[i].parent = NIL;
    T[i].leftChild = NIL;
    T[i].rightSib = NIL;
  }

  for (int i = 0; i < n; i++) {
    int cur_node, child_num;
    // Read fixed number. cur_node and child_num.
    cin >> cur_node >> child_num;
    
    int child_id, last_child_id;
    for (int j = 0; j < child_num; j++) {
      int child_id;

      // Read child_id one by one.
      cin >> child_id;

      // If this is 1st in the loop, register this as left most child.
      if (j == 0) {
        T[cur_node].leftChild = child_id;
      } else {
        // This will not happen for the right most sibling.
        T[last_child_id].rightSib = child_id;
      }

      // Keep value.
      last_child_id = child_id;
      // Register parent for child nodes.
      T[child_id].parent = cur_node;
    }
  }

  int top_node;
  for (int i = 0; i < n; i++) {
    if (T[i].parent == NIL) {
      top_node = i;
    }
  }

  rec(top_node, 0);

  for (int i = 0; i < n; i++) {
    print(i);
  }

  return 0;
}
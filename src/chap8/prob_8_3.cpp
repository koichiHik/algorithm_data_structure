
// System
#include <iostream>

using namespace std;

#define MAX 25
#define NIL -1

struct Node {
  int id;
  int parent;
  int sibling;
  int left;
  int right;
  int depth;
  int height;
};

Node T[MAX];

void print(int id) {

  int degree = 0;
  if (T[id].left != NIL && T[id].right != NIL) {
    degree = 2;
  } else if (T[id].left != NIL || T[id].right != NIL) {
    degree = 1;
  }

  cout << "node " << id << ": parent = " << T[id].parent << ", sibling = "
  << T[id].sibling << ", degree = " << degree << ", depth = " << T[id].depth
  << ", height = " << T[id].height << ", ";

  if (T[id].parent == NIL) {
    cout << "root";
  } else if (T[id].left == NIL && T[id].right == NIL) {
    cout << "leaf";
  } else {
    cout << "internal node";
  }

  cout << endl;
}

void recursive_parent_check(int id) {

  int left = T[id].left;
  int right = T[id].right;

  // Exit condition.
  if (left == NIL && right == NIL) {
    return;
  } else if (T[left].parent != NIL && T[right].parent != NIL) {
    return;
  }

  if (left != NIL) {
    T[left].parent = id;
    recursive_parent_check(left);
  }

  if (right != NIL) {
    T[right].parent = id;
    recursive_parent_check(right);
  }
}

int recursive_depth_check(int id) {

  if (T[id].depth != NIL) {
    return T[id].depth;
  } else if (T[id].parent == NIL) {
    T[id].depth = 0;
    return 0;
  }
  T[id].depth = recursive_depth_check(T[id].parent) + 1;
  return T[id].depth;
}

int recursive_height_check(int id) {

  if (T[id].height != NIL) {
    return T[id].height;
  } else if (T[id].left == NIL && T[id].right == NIL) {
    T[id].height = 0;
    return 0;
  }
  
  T[id].height = std::max(recursive_height_check(T[id].left) + 1,
                        recursive_height_check(T[id].right) + 1);

  return T[id].height;

}

void sibling_check(int id, int max_id) {

  if (T[id].sibling != NIL) {
    return;
  }

  if (T[id].parent != NIL) {
    int left = T[T[id].parent].left;
    int right = T[T[id].parent].right;

    if (left != NIL && id != left) {
      T[id].sibling = left;
    } else if (right != NIL && id != right) {
      T[id].sibling = right;
    }
  }
}

int main(int, char**) {

  int line_num;
  cin >> line_num;

  // Initialize
  for (int i = 0; i < line_num; i++) {
    T[i].id = T[i].left = T[i].right = T[i].parent = T[i].depth = T[i].sibling = T[i].height = NIL;
  }

  // Read line by line.
  for (int i = 0; i < line_num; i++) {
    int id;
    cin >> id >> T[id].left >> T[id].right;
  }

  // Parent check.
  for (int i = 0; i < line_num; i++) {
    recursive_parent_check(i);
  }

  // Depth check
  for (int i = 0; i < line_num; i++) {
    recursive_depth_check(i);
  }

  // Sibling check.
  for (int i = 0; i < line_num; i++) {
    sibling_check(i, line_num);
  }

  // Height check.
  for (int i = 0; i < line_num; i++) {
    recursive_height_check(i);
  }

  // Print Out
  for (int i = 0; i < line_num; i++) {
    print(i);
  }

  return 0;
}
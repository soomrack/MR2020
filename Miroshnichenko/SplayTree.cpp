#include <iostream>
#include <string>

std::string FindError = "";
std::string NoRootError = "";

class Node {
public:
  int key;
  std::string data;
public:
  Node* left;
  Node* right;
  Node* parent;
public:
  Node();
  Node(const int key, const std::string data);
  ~Node();
};

class Tree {
private:
  Node* root;
  void rotate_left(Node* current);
  void rotate_right(Node* current);
  void zig();
  void splay(Node* current);
  Node* getmin(Node* p) { return p->left ? getmin(p->left) : p; };
public:
  bool add(const int key, const std::string data);  // false if key already exists
  bool del(const int key);  // false if no key
  std::string find(const int key);  // return '' if no key
public:
  Tree();
  ~Tree();
};

Node::Node() {
  left = nullptr;
  right = nullptr;
}

Node::Node(int key, std::string data) {
  this->key = key;
  this->data = data;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

Tree::Tree() {
  root = nullptr;
}

void rotate_left(Node* current) {
  Node* p = current->parent;
  Node* r = current->right;
  if (p != nullptr) {
    if (p->left == current)
      p->left = r;
    else
      p->right = r;
  }
  Node* tmp = r->left;
  r->left = current;
  current->right = tmp;
  current->parent = r;
  r->parent = p;
  if (current->right != nullptr)
    current->right->parent = current;
}

void rotate_right(Node* current) {
  Node* p = current->parent;
  Node* l = current->right;
  if (p != nullptr) {
    if (p->left == current)
      p->left = l;
    else
      p->right = l;
  }
  Node* tmp = l->right;
  l->right = current;
  current->left = tmp;
  current->parent = l;
  l->parent = p;
  if (current->left != nullptr)
    current->left->parent = current;
}

bool zig(Node* current) {
  if (current->parent->left == current) 
    rotate_right(current->parent);
  else
    rotate_left(current->parent);
}

void splay(Node* current) {
  while (current->parent != nullptr) {
    Node* grandp = current->parent->parent;
    if (grandp == nullptr)
      zig(current->parent);
    if (grandp->left == current->parent) {
      if (current->parent->left == current) {
        rotate_right(current->parent);
        rotate_right(grandp);
      }
      else {
        rotate_left(current->parent);
        rotate_right(grandp);
      }
    }
    else {
      if (current->parent->left == current) {
        rotate_right(current->parent);
        rotate_left(grandp);
      }
      else {
        rotate_left(current->parent);
        rotate_left(grandp);
      }
    }
  }
}

std::string Tree::find(const int key) {
  Node* current = root;
  if (current == nullptr)
    return NoRootError;
  while (key != current->key) {
    if (key > current->key) {
      if (current->left == nullptr) return FindError;
      current = current->left;
    }
    else {
      if (current->right == nullptr) return FindError;
      current = current->right;
    }
  }
  splay(current);
  root = current;
  return root->data;

}

bool Tree::add(const int key, const std::string data) {
  Node* current = root;
  while (true) {
    if (key == current->key) return false;
    if (key > current->key) {
      if (current->left == nullptr) {
        current->left->key = key;
        current->left->data = data;
        current->left->parent = current;
        break;
      }
      current = current->left;
    }
    else {
      if (current->right == nullptr) {
        current->right->key = key;
        current->right->data = data;
        current->right->parent = current;
        break;
      }
      current = current->right;
    }
  }
  splay(current);
}

bool Tree::del(const int key) {
  if (root == nullptr)
    return false;
  if (root->key == key) {
    root = nullptr;
    return true;
  }
  Node* right_tree = nullptr;
  Node* left_tree = nullptr;
  find(key);
  right_tree = root->right;
  left_tree = root->left;
  splay(getmin(left_tree));
  root = left_tree;
  root->left = left_tree->left;
  root->right = right_tree;
}



Tree::~Tree() {
  delete root;
}

Node::~Node() {
  delete left;
  delete right;
  delete parent;
}

int main() {
  std::cout << "The end." << std::endl;
}
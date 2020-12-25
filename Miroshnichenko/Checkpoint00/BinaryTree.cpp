#include <iostream>
#include <string>

// Binary search tree

std::string FindError = "";
std::string NoRootError = "";


class Node {
public:
  int key;
  std::string data;
public:
  Node *left;
  Node *right;
public:
  Node();
  Node(const int key, const std::string data);
  Node(const int key, const std::string data, const Node* left, const Node *right);
  ~Node();
};

class Tree {
private:
  Node *root;
  Node *getmin(Node *p) { return p->left ? getmin(p->left) : p; }; // Node with the least key in tree
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
}

Node::Node(int key, std::string data, Node *left, Node *right) {
  this->key = key;
  this->data = data;
  this->left = left;
  this->right = right;
}

Tree::Tree() { 
  root = nullptr; 
}

bool Tree::add(const int key, const std::string data) {
  Node *current = root;
  if (current == nullptr) {
    root = new Node;
    root->key = key;
    root->data = data;
    return true;
  }
  while (true) {
    if (current->key < key) {
      if (current->right == nullptr) {
        current->right = new Node;
        Node *newNode = current->right;
        newNode->key = key;
        newNode->data = data;
        return true;
      }
      current = current->right;
    }
    else {
      if (current->left == nullptr) {
        current->left = new Node;
        Node *newNode = current->left;
        newNode->key = key;
        newNode->data = data;
        return true;
      }
      current = current->left;
    }
    return false;
  }
}

bool Tree::del(const int key)
{
  Node *current = root;
  Node *prev = nullptr;
  if (current == nullptr) return false;
  while (current->key != key) {
    if (current->key < key) {
      if (current->right != nullptr) {
        current = current->right;
        prev = current;
      }
      return false;
    }
    if (current->left != nullptr) {
      current = current->left;
      prev = current;
    }
    return false;
  }

  Node *leftNode = current->left;
  Node *rightNode = current->right;

  if (current != root) {
    if (rightNode != nullptr) {
      getmin(rightNode)->left = leftNode;
      Node *prevright = prev->right;
      if (prevright->key == current->key) //if deleting node is left for parent
      {
        prev->right = rightNode;
      }
      else
        prev->left = rightNode; //Если справа
    }
    else { 
      if (prev->left == current) //Если удаляемый элемент был слева у родителя
        prev->left = leftNode;
      else prev->right = leftNode;
    }
  }
  else { 
    if (rightNode != nullptr) { 
      getmin(rightNode)->left = leftNode; //Левая подветка идет вниз
      root = rightNode; //Корнем становится правый элемент от корня
    }
    else {
      root = leftNode;
    }
  }
  delete current;
  return true;
}

std::string Tree::find(const int key) {
  Node* current = root;
  if (current == nullptr)
    return NoRootError;
  while (true) {
    if (current->key < key) {
      if (current->right == nullptr) {
        return FindError;
      }
      current = current->right;
    }
    else if (current->key > key) {
      if (current->left == nullptr) {
        return FindError;
      }
      current = current->left;
    }
  }
  return (current->data);
}

Tree::~Tree() { 
  delete root; 
}

Node::~Node() { 
  delete left; 
  delete right; 
}

int main(){
  std::cout << "The end." << std::endl;
}
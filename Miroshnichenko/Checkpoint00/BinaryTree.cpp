#include <iostream>
#include <string>

// Binary search tree


class Node {
public:
  int key;
  std::string data;
public:
  Node* left;
  Node* right;
public:
  Node();
  Node(const int key, const std::string data);
  Node(const int key, const std::string data, const Node* left, const Node* right);
  ~Node();
};

class Tree {
private:
  Node* root;
  Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p
  {
    return p->left ? findmin(p->left) : p;
  }
public:
  bool add(const int key, const std::string data) {

  };  // false if key already exists
  bool del(const int key);  // false if no key
  std::string find(const int key);  // return '' if no key
public:
  Tree();
  ~Tree();
};

Node::Node() { left = nullptr; right = nullptr; }
Tree::Tree() { root = nullptr; }
bool Tree::add(const int key, const std::string data) {
  Node* current = root;
  if (current == nullptr) {
    root = new Node;
    root->key = key;
    root->data = data;
  }
  else {
    while (true)
    {
      if (current->key < key) {
        if (current->right == nullptr) {
          current->right = new Node;
          Node* newNode = current->right;
          newNode->key = key;
          newNode->data = data;
          return true;
        }
        else
          current = current->right;
      }
      else if (current->key > key) {
        if (current->left == nullptr) {
          current->left = new Node;
          Node* newNode = current->left;
          newNode->key = key;
          newNode->data = data;
          return true;
        }
        else current = current->left;
      }
      else return false;
    }
  }
}
bool Tree::del(const int key)
{
  Node* current = root;
  Node* prev = nullptr;
  if (current == nullptr)
    return false;
  else {
    while (current->key != key) {
      if (current->key < key) {
        if (current->right != nullptr) {
          prev = current;
          current = current->right;
        }
        else
          return false;
      }
      if (current->key > key) {
        if (current->left != nullptr) {
          prev = current;
          current = current->left;
        }
        else
          return false;
      }
    }
  }

  Node* l = current->left;
  Node* r = current->right;

  if (current != root) {
    if (r != nullptr) {
      findmin(r)->left = l;
      Node* prevright = prev->right;
      if (prevright->key == current->key) //Если удаляемый элемент был слева у родителя
      {
        prev->right = r;
      }
      else
        prev->left = r; //Если справа
    }
    else { 
      if (prev->left == current) //Если удаляемый элемент был слева у родителя
        prev->left = l;
      else prev->right = l;
    }
  }
  else { 
    if (r != nullptr) { 
      findmin(r)->left = l; //Левая подветка идет вниз
      root = r; //Корнем становится правый элемент от корня
    }
    else {
      root = l;
    }
  }
  delete current;
  return true;
}
std::string Tree::find(const int key) {
  Node* current = root;
  if (current == nullptr)
    return " ";
  else {
    while (true) {
      if (current->key < key) {
        if (current->right == nullptr) {
          return " ";
        }
        else
          current = current->right;
      }
      else if (current->key > key) {
        if (current->left == nullptr) {
          return " ";
        }
        else current = current->left;
      }
    }
    return (current->data);
  }
}
Tree::~Tree() { delete root; }
Node::~Node() { delete left; delete right; }
int main(){
  std::cout << "The end." << std::endl;
}
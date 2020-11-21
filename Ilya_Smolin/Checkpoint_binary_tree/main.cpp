#include <iostream>
#include <string>

// Binary search tree


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
    Node(const int key, const std::string data, const Node *left, const Node *right);
    ~Node();
};


class Tree {
private:
    Node *root;
    Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left?findmin(p->left):p;
    }
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};
Node::Node() {left = nullptr; right = nullptr;}
Tree::Tree() {root = nullptr;}
bool Tree::add(const int key, const std::string data)
{
  Node *current = root;
  while (current->key != key)
  {
      if (current->key < key)
      {
          if (current->right == nullptr) {
              current->right = new Node;
              Node *newNode = current->right;
              newNode->key = key;
              newNode->data = data;
              return true;
          }
          else
              current = current->right;
      }
      else if (current->key > key)
      {
          if (current->left == nullptr) {
              current->left = new Node;
              Node *newNode = current->left;
              newNode->key = key;
              newNode->data = data;
              return true;
          }
          else current = current->left;
      }
      else if (current->key = key)
          return false;
  }
    return false;
}
bool Tree::del(const int key)
{
    Node *current = root;
    Node *prev = nullptr;
    while (current->key != key)
    {
        if (current->key < key)
        {
            if (current->right != nullptr) {
                prev = current;
                current = current->right;
            }
            else
                return false;
        }
        if (current->key > key)
        {
            if (current->left != nullptr) {
                prev = current;
                current = current->left;
            }
            else
                return false;
        }
    }
    Node *q = current->left;
    Node *r = current->right;
    delete current;
    if (r == nullptr) return 888;
    Node *min = findmin(r); //То, что мы вытаскиваем наверх
    min->left = q; //Левая подветка идет вниз
    if (prev->left = nullptr) //В этих 3х строчках мы пристраеваем склееное поддерево к тому узлу, к которому был привязан удаляемый
        prev->left = min;
    else prev->right = min;
    return true;
}
Tree::~Tree() {delete root;}
Node::~Node() {delete left; delete right;}
int main() {
    Tree mytree;
}
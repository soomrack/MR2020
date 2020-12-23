#include <iostream>
#include <string>

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
    Node(const int key, const std::string data, Node *left, Node *right);
    ~Node();
};

class Tree {
private:
    Node *root;
    Node *delAdress;
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
private:
    bool insert(Node *node, Node *&parent); //нужна для add()
    Node* find(const int key, Node *parent);//нужна для public del()
    bool del(Node *node);//нужна для public del()
public:
    Tree();
    ~Tree();
};

Node::Node() {
    left = nullptr;
    right = nullptr;
}

Node::Node(const int key, const std::string data) {
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data, Node *left, Node *right) {
    Node *node = new Node();
    node->key = key;
    node->data = data;
    node->left = left;
    node->right = right;
}

Node::~Node() {
    delete this->left;
    delete this->right;
}

Tree::Tree() {
    root = nullptr;
    delAdress = nullptr;
}

bool Tree::insert(Node *node, Node *&parent) {
    if (parent == nullptr){
        parent = node;
        return true;
    } else if (parent->key > node->key){
        return insert(node, parent->left);
    } else if (parent->key < node->key){
        return insert(node, parent->right);
    } else return false;
}

bool Tree::add(const int key, const std::string data) {
    Node *node = new Node(key,data);
    if (root == nullptr) {
        root = node;
        return true;
    } else{
        return insert(node, root);
    }
}

Node* Tree::find(const int key, Node *parent) {
    if (parent == nullptr){
        return nullptr;
    } if (parent->key == key){
        return parent;
    } else if (parent->key > key){
        delAdress = parent->left;
        return find(key, parent->left);
    } else if (parent->key < key) {
        delAdress = parent->right;
        return find(key, parent->right);
    }
}

bool Tree::del(Node *node) {
    if (node == nullptr) return false;
    else{
        del(node->left);
        del(node->right);
        delete node;
        delAdress = nullptr;
        return true;
    }
}

bool Tree::del(const int key) {
    Node *delNode = find(key, this->root);
    if (delNode == nullptr) return false;
    else {
        return del(delNode);
    }
}

std::string Tree::find(const int key) {
    Node *findNode = find(key, root);
    if (findNode == nullptr) return "";
    else return findNode->data;
}

Tree::~Tree() {
    del(this->root);
}

int main() {
    Tree *tree = new Tree();
    tree->add(24, "0 level");
    tree->add(12, "1 level, l");
    tree->add(36, "1 level, r");
    tree->add(18, "2 level, l-r");
    std::cout << tree->find(18) << std::endl;

    tree->del(18);
    std::cout << tree->find(18) << std::endl;
    std::cout << tree->find(12) << std::endl;
    std::cout << tree->find(36) << std::endl;

    std::cout << "The end." << std::endl;
}

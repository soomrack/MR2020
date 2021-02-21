#include "My_header.h"

Node::Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
Node::Node(const int key, const std::string data) {
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}
Node::Node(const int key, const std::string data, Node *parent, COLOR color) {
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
    this->color = color;
}
Node::~Node() {
    this->left = nullptr;
    this->right = nullptr;
}
Tree::Tree() {
    root = nullptr;
}
Tree::~Tree() {
    delete root;
}


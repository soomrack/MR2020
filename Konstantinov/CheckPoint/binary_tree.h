//
// Created by alex on 06.12.2020.
//

#ifndef CPP_CHECKPOINT_BINARY_TREE_H
#define CPP_CHECKPOINT_BINARY_TREE_H

class Node{
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
public:
    Node()= default;
    Node(int key, std::string data);
    Node(int key, std::string data, Node *left, Node *right);
    ~Node()= default;
};


class Tree {
private:
    Node *root;
    Node* findParent(int key);
    Node* findMin(Node* pivot);
public:
    bool add(int key, std::string data);  // false if key already exists
    bool del(int key);  // false if no key
    std::string find(int key);  // return '' if no key
public:
    Tree();
    ~Tree()= default;
};

#endif //CPP_CHECKPOINT_BINARY_TREE_H
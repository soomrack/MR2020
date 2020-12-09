//
// Created by alex on 06.12.2020.
//

#ifndef CPP_CHECKPOINT_BINARY_TREE_H
#define CPP_CHECKPOINT_BINARY_TREE_H
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
    Node* findParent(const int key);
    Node* findMin(Node* pivot);
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};




#endif //CPP_CHECKPOINT_BINARY_TREE_H

// Created by alena on 29.11.2020.

#ifndef UNTITLED_B_TREE_H
#define UNTITLED_B_TREE_H

#include <string>

class Node {
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
    //Node *parent;
public:
    Node();
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, const Node *left, const Node *right);
    ~Node();
};

class Tree {
private:
    Node *root;
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool insert(Node ** new_node,const int key, const std::string data);
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
    Node* search(Node * &new_node, const int key, Node * &parent);
    Node* search_min(Node* root);
    Node* get_root() {return root;}
    void Print_tree (Node* node, int h);
public:
    Tree();
    ~Tree();
};

#endif //UNTITLED_B_TREE_H

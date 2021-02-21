
#ifndef BLACK_RED_TREE_MY_HEADER_H
#define BLACK_RED_TREE_MY_HEADER_H

#include <iostream>
#include <string>
#include "termcolor.h"

enum class COLOR {
    RED,
    BLACK
};

class Node {
public:
    int key;
    std::string data;
    COLOR color;
public:
    Node *left;
    Node *right;
    Node *parent;
public:
    Node();
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, Node *parent, COLOR color);
    ~Node();
};

class Tree {
private:
    Node *root;
public:
    bool add(const int key, const std::string data);  // false if key already exists
    Node * insert(const int key, const std::string data, Node *& new_node, Node *& parent);
    void refactor(Node *& new_node);
    void rotateRight(Node *&node_parent);
    void rotateLeft(Node *&node_parent);
    
    std::string find(const int key);  // return '' if no key
    Node* search(const int key, Node *&search_node);

    bool del(const int key);  // false if no key
    
    Node* search_min(Node* root);
    Node* get_root() {return root;}
    void Print_tree (Node* node, int h = 0);
public:
    Tree();
    ~Tree();
};


#endif //BLACK_RED_TREE_MY_HEADER_H

// Created by alena on 22.03.2021.

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <iostream>

class B_Node {
    friend class BTree;
public:
    int *keys; // keys
    int n_keys; // number of Keys
    B_Node** Children; // array of pointers to children
    B_Node* Parent;
    int t; // parameter of B-tree
    bool leaf; // is true when node is leaf
public:
    B_Node();
    B_Node(int t, bool leaf);
    ~B_Node();
    void traverse();
    B_Node *search(int key);
    void insert_smart(int key);
    void split_Child(int i, B_Node *old_child);
    void del_from_leaf(int key_count);
    void del_from_nonleaf(int key_count);
    B_Node* get_succ(int key_count);
    B_Node* get_pred(int key_count);
    void borrow_from_left(int node_pos);
    void borrow_from_right(int node_pos);
    void merge(int node_pos); // with left sibling
};

class B_Tree {
    B_Node *root;
    int t;
public:
    B_Tree(int t) {
        root = nullptr;
        this->t = t;
    }
    void Print() {
        if (root != nullptr) {
            root->traverse();
        }
    }
    B_Node* search(int k) {
        if(root == nullptr) {
            return nullptr;
        } else {
            return root->search(k);
        }
    }
    void insert(int key);
    bool del(int key_to_del);
};

#endif //B_TREE_B_TREE_H

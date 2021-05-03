//
// Created by alex on 24.04.2021.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <string>

#define B 2

class BTree;

class Node{
private:
    int keys[B*2 - 1];
    Node *children[B*2];
    Node *parent;
    int count_of_keys;
    int count_of_sons;
    bool is_leaf;

    Node() = default;
    ~Node() = default;

    static void DeleteNode(Node *node);
    friend BTree;



};


class BTree{
public:
    bool Add(int key);
    bool Remove(const int key);
    bool Find(const int key);
    bool Get(const int key);

    BTree();
    ~BTree();
private:

    void Insert(int key, Node *node);
    Node * Split(Node *sub_root);
    Node *root;

};




#endif //B_TREE_B_TREE_H

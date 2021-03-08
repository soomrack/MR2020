#include <iostream>

#pragma once


class TreeStruct
{
public:
    int info;
    int key;
    bool black;
    TreeStruct* right;
    TreeStruct* left;
    TreeStruct* parent;
};

class RBTree
{
public:
    RBTree();
    ~RBTree();

    void insert(int key, int info);
    void erase(int key);
    bool exist(int key);
    TreeStruct * node;

private:
    TreeStruct * grandparent(TreeStruct* current);
    TreeStruct * uncle(TreeStruct* current);
    TreeStruct* newTree(int key,int info,TreeStruct* parent = nullptr);
    void insert1(TreeStruct* n);
    void insert2(TreeStruct* n);
    void insert3(TreeStruct* n);
    void insert4(TreeStruct* n);
    void insert5(TreeStruct* n);
    void delete1(TreeStruct* n);
    void delete2(TreeStruct* n);
    /*void delete3(TreeStruct* n);
    void delete4(TreeStruct* n);
    void delete5(TreeStruct* n);
    void delete6(TreeStruct* n);*/
    void rotateLeft(TreeStruct* curr);
    void rotateRight(TreeStruct* curr);
    void setRight(TreeStruct* curr,int key, int info);
    void setLeft(TreeStruct* curr, int key, int info);
};

RBTree::RBTree()
{
    node = nullptr;
}

RBTree::~RBTree()
{
    delete node;
}

TreeStruct* RBTree::newTree(int key, int info,TreeStruct* parent)
{
    TreeStruct *curr = new TreeStruct;
    curr->info = info;
    curr->key = key;
    curr->right = curr->left = nullptr;
    curr->parent = parent;
    curr->black = false;
    return curr;
}

void RBTree::setLeft(TreeStruct* curr, int key, int info)
{
    curr->left = newTree(key, info, curr);
}

void RBTree::setRight(TreeStruct* curr, int key, int info)
{
    curr->right = newTree(key, info, curr);
}

TreeStruct * RBTree::grandparent(TreeStruct* curr)
{
    if ((curr != nullptr) && (curr->parent != nullptr))
        return curr->parent->parent;
    else
        return nullptr;
}


TreeStruct * RBTree::uncle(TreeStruct* curr)
{
    TreeStruct *g = grandparent(curr);
    if (g == nullptr)
        return nullptr;
    if (curr->parent == g->left)
        return g->right;
    else
        return g->left;
}

void RBTree::insert1(TreeStruct* n)
{
    if (n->parent == nullptr)
        n->black = true;
    else
        insert2(n);
}

void RBTree::insert2(TreeStruct* n)
{
    if (n->parent->black)
        return;
    else
        insert3(n);
}

void RBTree::insert3(TreeStruct* n)
{
    TreeStruct *u = uncle(n), *g;

    if ((u != NULL) && (!u->black))
    {
        n->parent->black = true;
        u->black = true;
        g = grandparent(n);
        g->black = false;
        insert1(g);
    }
    else {
        insert4(n);
    }
}

void RBTree::insert4(TreeStruct* current)
{
    TreeStruct *g = grandparent(current);

    if ((current == current->parent->right) && (current->parent == g->left))
    {
        rotateLeft(current->parent);
        current = current->left;
    }
    else if ((current == current->parent->left) && (current->parent == g->right))
    {
        rotateRight(current->parent);
        current = current->right;
    }
    insert5(current);
}

void RBTree::insert5(TreeStruct* current)
{
    TreeStruct *g = grandparent(current);

    current->parent->black = true;
    g->black = false;
    if ((current == current->parent->left) && (current->parent == g->left))
        rotateRight(g);
    else {
        rotateLeft(g);
    }
}

bool RBTree::exist(int key)
{
    TreeStruct* curr, *next;
    curr = next = node;
    while (next != nullptr)
    {
        curr = next;
        if (key < curr->key)
            next = curr->left;
        if (key > curr->key)
            next = curr->right;
        if (key == curr->key)
            return true;
    }
    return false;
}

void RBTree::erase(int key)
{
    if (!exist(key))
        return;
    TreeStruct* current, *next;
    current = next = node;
    while (next != nullptr)
    {
        current = next;
        if (key < current->key)
            next = current->left;
        if (key > current->key)
            next = current->right;
        if (key == current->key)
        {
            delete1(current);
            return;
        }
    }
}

void RBTree::delete1(TreeStruct* current)
{
    if (current == node)
    {
        node = nullptr;
        return;
    }
    if (!current->right && !current->left)
    {
        if (current->parent->right == current)
            current->parent->right = nullptr;
        else
            current->parent->left = nullptr;
        return;
    }
    else {
        if ((current->left && current->right == nullptr) || (current->right && current->left == nullptr))
        {
            if (current->right)
                if (current->parent->right == current)
                    current->parent->right = current->right;
                else
                    current->parent->left = current->right;
            else
            if (current->parent->right == current)
                current->parent->right = current->left;
            else
                current->parent->left = current->left;
        }
        else
            delete2(current);
    }
}

void RBTree::delete2(TreeStruct* current)
{
}

void RBTree::insert(int key, int info)
{
    TreeStruct* curr,*next;
    if (node == nullptr)
    {
        node = newTree(key, info);
        node->black = true;
        node->key = key;
        node->info = info;
    }
    curr = next = node;
    while (next != nullptr)
    {
        curr = next;
        if (key < curr->key)
            next = curr->left;
        if (key > curr->key)
            next = curr->right;
        if (key == curr->key) {
            curr->info = info;
            return;
        }
    }
    if (key < curr->key)
    {
        setLeft(curr, key, info);
        next = curr->left;
    }
    else {
        setRight(curr, key, info);
        next = curr->right;
    }
    insert1(next);
}

void RBTree::rotateLeft(TreeStruct* current)
{
    TreeStruct *pivot = current->right;

    pivot->parent = current->parent;
    if (current->parent != nullptr)
    {
        if (current->parent->left == current)
            current->parent->left = pivot;
        else
            current->parent->right = pivot;
    }

    current->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = current;

    current->parent = pivot;
    pivot->left = current;
    if (current == node)
        node = pivot;
}

void RBTree::rotateRight(TreeStruct* current)
{
    TreeStruct *pivot = current->left;
    pivot->parent = current->parent;
    if (current->parent != nullptr) {
        if (current->parent->left == current)
            current->parent->left = pivot;
        else
            current->parent->right = pivot;
    }
    current->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = current;

    current->parent = pivot;
    pivot->right = current;
    if (current == node)
        node = pivot;
}



int main()
{
    return 0;
}

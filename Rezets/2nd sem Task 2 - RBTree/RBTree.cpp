#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>


class RBTree
{
    struct Node
    {
        Node *left;
        Node *right;
        int value;
        bool red;
    };
    Node *tree_root;
private:
    Node* new_node(int value);
    void del_node(Node* node);
    void clear(Node* node);
    Node* rotate_left(Node* node);
    Node* rotate_right(Node* node);
    void balance_insert(Node** root);
    bool balance_remove_left(Node** root);
    bool balance_remove_right(Node** root);
    bool insert(int value, Node** root);
    bool get_min(Node** root, Node** res);
    bool remove(Node** root, int value);
public:
    RBTree();
    ~RBTree();
    void clear();
    bool find(int);
    void insert(int);
    void remove(int);
};


RBTree::RBTree()
{
    tree_root = nullptr;
}

RBTree::~RBTree()
{
    clear(tree_root);
}

RBTree::Node *RBTree::new_node(int value)
{
    Node *node = new Node;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    node->red = true;
    return node;
}

void RBTree::del_node(Node *node)
{
    delete node;
}

void RBTree::clear(Node *node)
{
    if (!node)
        return;
    clear(node->left);
    clear(node->right);
    del_node(node);
}

RBTree::Node *RBTree::rotate_left(Node *node)
{
    Node *right_son = node->right;
    Node *left_grandson = right_son->left;
    right_son->left = node;
    node->right = left_grandson;
    return right_son;
}

RBTree::Node *RBTree::rotate_right(Node *node)
{
    Node *left_son = node->left;
    Node *right_grandson = left_son->right;
    left_son->right = node;
    node->left = right_grandson;
    return left_son;
}

void RBTree::balance_insert(Node **root)
{
    Node *left_son, *right_son, *left_grandsonl, *right_grandsonl;
    Node *node = *root;
    if (node->red)
        return;
    left_son = node->left;
    right_son = node->right;
    if (left_son && left_son->red)
    {
        right_grandsonl = left_son->right;
        if (right_grandsonl && right_grandsonl->red)
            left_son = node->left = rotate_left(left_son);
        left_grandsonl = left_son->left;
        if (left_grandsonl && left_grandsonl->red)
        {
            node->red = true;
            left_son->red = false;
            if (right_son && right_son->red)
            {
                left_grandsonl->red = true;
                right_son->red = false;
                return;
            }
            *root = rotate_right(node);
            return;
        }
    }
    
    if (right_son && right_son->red)
    {
        left_grandsonl = right_son->left;
        if (left_grandsonl && left_grandsonl->red)
            right_son = node->right = rotate_right(right_son);
        right_grandsonl = right_son->right;
        if (right_grandsonl && right_grandsonl->red)
        {
            node->red = true;
            right_son->red = false;
            if (left_son && left_son->red)
            {
                right_grandsonl->red = true;
                left_son->red = false;
                return;
            }
            *root = rotate_left(node);
            return;
        }
    }
}


bool RBTree::balance_remove_left(Node **root)
{
    Node *node = *root;
    Node *left_son = node->left;
    Node *right_son = node->right;
    if (left_son && left_son->red)
    {
        left_son->red = false;
        return false;
    }
    if (right_son && right_son->red)
    {
        node->red = true;
        right_son->red = false;
        node = *root = rotate_left(node);
        if (balance_remove_left(&node->left))
            node->left->red=false;
        return false;
    }
    unsigned int mask = 0;
    Node *left_grandsonr = right_son->left;
    Node *right_grandsonr = right_son->right;
    if (left_grandsonr && left_grandsonr->red)
        mask |= 1;
    if (right_grandsonr && right_grandsonr->red)
        mask |= 2;
    switch(mask)
    {
    case 0:
        right_son->red = true;
        return true;
    case 1:
    case 3:
        right_son->red = true;
        left_grandsonr->red = false;
        right_son = node->right = rotate_right(right_son);
        right_grandsonr = right_son->right;
    case 2:
        right_son->red = node->red;
        right_grandsonr->red = node->red = false;
        *root = rotate_left(node);
    }
    return false;
}

bool RBTree::balance_remove_right(Node **root)
{
    Node *node = *root;
    Node *left_son = node->left;
    Node *right_son = node->right;
    if (right_son && right_son->red)
    {
        right_son->red = false;
        return false;
    }
    if (left_son && left_son->red)
    {
        node->red = true;
        left_son->red = false;
        node = *root = rotate_right(node);
        if(balance_remove_right(&node->right))
            node->right->red = false;
        return false;
    }
    unsigned int mask = 0;
    Node *left_grandsonl = left_son->left;
    Node *right_grandsonl = left_son->right;
    if (left_grandsonl && left_grandsonl->red)
        mask |= 1;
    if (right_grandsonl && right_grandsonl->red)
        mask |= 2;
    switch(mask)
    {
    case 0:
        left_son->red = true;
        return true;
    case 2:
    case 3:
        left_son->red = true;
        right_grandsonl->red = false;
        left_son = node->left = rotate_left(left_son);
        left_grandsonl = left_son->left;
    case 1:
        left_son->red = node->red;
        left_grandsonl->red = node->red = false;
        *root = rotate_right(node);
    }
    return false;
}

bool RBTree::find(int value)
{
    Node *node = tree_root;
    while(node)
    {
        if (node->value == value)
            return true;
        node = node->value > value ? node->left : node->right;
    }
    return false;
}

bool RBTree::insert(int value, Node **root)
{
    Node *node = *root;
    if (!node)
        *root = new_node(value);
    else
    {
        if (value == node->value)
            return true;
        if (insert(value, value < node->value ? &node->left : &node->right))
            return true;
        balance_insert(root);
    }
    return false;
}



bool RBTree::get_min(Node **root,Node **res)
{
    Node *node = *root;
    if (node->left)
    {
        if (get_min(&node->left, res))
            return balance_remove_left(root);
    }
    else
    {
        *root = node->right;
        *res = node;
        return !node->red;
    }
    return false;
}

bool RBTree::remove(Node **root, int value)
{
    Node *t, *node;
    node = *root;
    if (!node)
        return false;
    if (node->value < value)
    {
        if(remove(&node->right, value))
            return balance_remove_right(root);
    }
    else if(node->value > value)
    {
        if (remove(&node->left, value))
            return balance_remove_left(root);
    }
    else
    {
        bool res;
        if (!node->right)
        {
            *root = node->left;
            res = !node->red;
        }
        else
        {
            res = get_min(&node->right, root);
            t = *root;
            t->red = node->red;
            t->left = node->left;
            t->right = node->right;
            if (res)
                res = balance_remove_right(root);
        }
        del_node(node);
        return res;
    }
    return 0;
}

void RBTree::insert(int value)
{
    insert(value, &tree_root);
    if (tree_root)
        tree_root->red = false;
}

void RBTree::remove(int value)
{
    remove(&tree_root, value);
}

void RBTree::clear()
{
    clear(tree_root);
    tree_root = 0;
}

int main()
{
    return 0;
}

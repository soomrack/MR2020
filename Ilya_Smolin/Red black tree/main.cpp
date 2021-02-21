#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>

class RBtree {
    struct Node {
        Node *left;
        Node *right;
        int value;
        bool red;
    };
    Node *tree_root;

private:
    Node *new_node(int value);

    void delete_node(Node *node);

    void clear(Node *node);

    Node *rotate_left(Node *node);

    Node *rotate_right(Node *node);

    void balance_insert(Node **root);

    bool balance_rm_left(Node **root);

    bool balance_rm_right(Node **root);

    bool insert(int value, Node **root);

    bool getMin(Node **root, Node **res);

    bool remove(Node **root, int value);

public:
    RBtree();

    ~RBtree();

    void clear();

    bool find(int);

    void insert(int);

    void remove(int);
};


RBtree::RBtree() {
    tree_root = nullptr;
}

RBtree::~RBtree() {
    clear(tree_root);
}

RBtree::Node *RBtree::new_node(int value) {
    Node *node = new Node;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    node->red = true;
    return node;
}


void RBtree::delete_node(Node *node) {
    delete node;
}


void RBtree::clear(Node *Node) {
    if (!Node)
        return;
    clear(Node->left);
    clear(Node->right);
    delete_node(Node);
}


RBtree::Node *RBtree::rotate_left(Node *node) {
    Node *right_child = node->right;
    Node *left_grandrightchild = right_child->left;
    right_child->left = node;
    node->right = left_grandrightchild;
    return right_child;
}

RBtree::Node *RBtree::rotate_right(Node *node) {
    Node *left_child = node->left;
    Node *right_grandleftchild = left_child->right;
    left_child->right = node;
    node->left = right_grandleftchild;
    return left_child;
}


void RBtree::balance_insert(Node **root) {
    Node *left_child, *right_child, *left_grandleftson, *right_grandleftson,
            *left_grandrightson, *right_grandrightson;
    Node *node = *root;
    if (node->red)
        return;
    left_child = node->left;
    right_child = node->right;
    if (left_child && left_child->red) {
        right_grandleftson = left_child->right;
        if (right_grandleftson && right_grandleftson->red)
            left_child = node->left = rotate_left(left_child);
        left_grandleftson = left_child->left;
        if (left_grandleftson && left_grandleftson->red) {
            node->red = true;
            left_child->red = false;
            if (right_child && right_child->red) {
                left_grandleftson->red = true;
                right_child->red = false;
                return;
            }
            *root = rotate_right(node);
            return;
        }
    }

    if (right_child && right_child->red) {
        left_grandrightson = right_child->left;
        if (left_grandrightson && left_grandrightson->red)
            right_child = node->right = rotate_right(right_child);
        right_grandrightson = right_child->right;
        if (right_grandrightson && right_grandrightson->red) {
            node->red = true;
            right_child->red = false;
            if (left_child && left_child->red) {
                right_grandrightson->red = true;
                right_child->red = false;
                return;
            }
            *root = rotate_left(node);
            return;
        }
    }
}


bool RBtree::balance_rm_left(Node **root) {
    Node *node = *root;
    Node *left_child = node->left;
    Node *right_child = node->right;
    if (left_child && left_child->red) { //Если убрана красная вершина - перекрашиваем в черную
        left_child->red = false;
        return false;
    }
    if (right_child && right_child->red) { //Удаленная вершина имеет крассного брата
        node->red = true;
        right_child->red = false;
        node = *root = rotate_left(node);
        if (balance_rm_left(&node->left))
            node->left->red = false;
        return false;
    }

    Node *left_grandrightson = right_child->left;
    Node *right_grandrightson = right_child->right;


    unsigned int mask = 0;
    if (left_grandrightson && left_grandrightson->red)
        mask |= 1;
    if (right_grandrightson && right_grandrightson->red)
        mask |= 2;

    switch (mask) {
        case 0: //Удаляемая вершина имеет черного брата с черными потомками
            right_child->red = true;
            return true;
            //Удаляемая вершина имеет черного брата, с красным правым потомком
        case 1:
            right_child->red = true;
            left_grandrightson->red = false;
            right_child = node->right = rotate_right(right_child);
            right_grandrightson = right_child->right;
        case 3:
            right_child->red = true;
            left_grandrightson->red = false;
            right_child = node->right = rotate_right(right_child);
            right_grandrightson = right_child->right;
        case 2: //Удаляемая вершина имеет черного брата с красным левым и черным правым
            right_child->red = node->red;
            right_grandrightson->red = node->red = false;
            *root = rotate_left(node);
    }
    return false;
}

bool RBtree::balance_rm_right(Node **root) {
    Node *node = *root;
    Node *left_child = node->left;
    Node *right_child = node->right;
    if (right_child && right_child->red) {
        right_child->red = false;
        return false;
    }
    if (left_child && left_child->red) {
        node->red = true;
        left_child->red = false;
        node = *root = rotate_right(node);
        if (balance_rm_right(&node->right))
            node->right->red = false;
        return false;
    }
    Node *left_grandleftson = left_child->left;
    Node *right_grandleftson = left_child->right;


    unsigned int mask = 0;
    if (left_grandleftson && left_grandleftson->red)
        mask |= 1;
    if (right_grandleftson && right_grandleftson->red)
        mask |= 2;
    switch (mask) {
        case 0:
            left_child->red = true;
            return true;
        case 2:
            left_child->red = true;
            right_grandleftson->red = false;
            left_child = node->left = rotate_left(left_child);
            left_grandleftson = left_child->left;
        case 3:
            left_child->red = true;
            right_grandleftson->red = false;
            left_child = node->left = rotate_left(left_child);
            left_grandleftson = left_child->left;
        case 1:
            left_child->red = node->red;
            left_grandleftson->red = node->red = false;
            *root = rotate_right(node);
    }
    return false;
}

bool RBtree::find(int value) {
    Node *node = tree_root;
    while (node) {
        if (node->value == value)
            return true;
        node = node->value > value ? node->left : node->right;
    }
    return false;
}


bool RBtree::insert(int value, Node **root) {
    Node *node = *root;
    if (!node)
        *root = new_node(value);
    else {
        if (value == node->value)
            return true;
        if (insert(value, value < node->value ? &node->left : &node->right))
            return true;
        balance_insert(root);
    }
    return false;
}


bool RBtree::getMin(Node **root, Node **res) {
    Node *node = *root;
    if (node->left) {
        if (getMin(&node->left, root)) return balance_rm_left(root);
    } else {
        *root = node->right;
        *root = node;
        return !node->red;
    }
    return false;
}


bool RBtree::remove(Node **root, int value) {
    Node *t, *node = *root;
    if (!node)
        return false;
    if (node->value < value) {
        if (remove(&node->right, value))
            return balance_rm_right(root);
    } else if (node->value > value) {
        if (remove(&node->left, value))
            return balance_rm_left(root);
    } else {
        bool res;
        if (!node->right) {
            *root = node->left;
            res = !node->red;
        } else {
            res = getMin(&node->right, root);
            t = *root;
            t->red = node->red;
            t->left = node->left;
            t->right = node->right;
            if (res) res = balance_rm_right(root);
        }
        delete_node(node);
        return true;
    }
    return false;
}


void RBtree::insert(int value) {
    insert(value, &tree_root);
    if (tree_root)
        tree_root->red = false;
}


void RBtree::remove(int value) {
    remove(&tree_root, value);
}


void RBtree::clear() {
    clear(tree_root);
    tree_root = nullptr;
}


int main() {
    return 0;
}



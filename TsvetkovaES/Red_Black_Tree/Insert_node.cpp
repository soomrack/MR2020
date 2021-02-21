#include "My_header.h"

Node* Tree::insert(const int key, const std::string data, Node *& new_node, Node *& parent) {
    if(new_node == nullptr) {
        new_node = new Node(key, data, parent, COLOR::RED); // нашли свободное местечко - создали node
        return new_node;
    }
    if(key > new_node->key) {
        parent = new_node;
        return insert(key,data,new_node->right,parent);
    }
    else if(key < new_node->key) {
        parent = new_node;
        return insert(key,data,new_node->left,parent);
    }
    else {  // equal
        std::cout << termcolor::reset << "The key " << key << " is already in the tree!\n";
        return nullptr;
    }
}

bool Tree::add(const int key, const std::string data) {
    if(root == nullptr) { // if tree is empty
        root = new Node (key, data, nullptr,COLOR::BLACK);
        return true;
    }
    Node* parent = nullptr;
    Node* new_node = insert(key, data, root, parent);
    if(!new_node) {
        return false;
    }
    refactor(new_node);
}

void Tree::refactor(Node *& new_node) {
    Node* node_parent = new_node->parent;
    if(new_node == root || node_parent->color == COLOR::BLACK) { // || new_node->color == COLOR::BLACK
        root->color = COLOR::BLACK;
        return;
    }
    
    Node* node_grandpa = node_parent->parent;
    Node* node_uncle;
    if(node_parent == node_grandpa->left) {
        node_uncle = node_grandpa->right;
    } else {
        node_uncle = node_grandpa->left;
    }
    
    if(node_uncle && node_uncle->color == COLOR::RED) {
        node_parent->color = COLOR::BLACK;
        node_uncle->color = COLOR::BLACK;
        node_grandpa->color = COLOR::RED;
        return refactor(node_grandpa);
    } else {
        if (node_grandpa->left == node_parent) { // parent is left child (of grandpa)
            // new_node is right child (of parent)
            if (new_node == node_parent->right) {
                rotateLeft(node_parent);
                new_node = node_parent;
                node_parent = new_node->parent;
            }
            // new_node is left child (of parent)
            rotateRight(node_grandpa);
            std::swap(node_parent->color,node_grandpa->color);
            new_node = node_parent;
        } else { // parent is right child (of grandpa)
            // new_node is left child (of parent)
            if (new_node == node_parent->left) {
                rotateRight(node_parent);
                new_node = node_parent;
                node_parent = new_node->parent;
            }
            // new_node is right child (of parent)
            rotateLeft(node_grandpa);
            std::swap(node_parent->color, node_grandpa->color);
            new_node = node_parent;
        }
        return refactor(new_node);
    }
}

void Tree::rotateRight(Node *&node_parent) { // (Node *&root, Node *&node_parent)
    Node * grandpa = node_parent->parent;
    Node * left_child = node_parent->left;
    node_parent->left = left_child->right;
    if (node_parent->left != nullptr) {
        node_parent->left->parent = node_parent;
    }
    left_child->parent = grandpa;
    if (grandpa == nullptr) {
        root = left_child;
    } else if (node_parent == grandpa->left) {
        grandpa->left = left_child;
    } else {
        grandpa->right = left_child;
    }
    left_child->right = node_parent;
    node_parent->parent = left_child;
}

void Tree::rotateLeft(Node *&node_parent) { // (Node *&root, Node *&node_parent)
    Node * grandpa = node_parent->parent;
    Node * right_child = node_parent->right;
    node_parent->right = right_child->left;
    if (node_parent->right != nullptr) {
        node_parent->right->parent = node_parent;
    }
    right_child->parent = grandpa;
    if (grandpa == nullptr) {
        root = right_child;
    } else if (node_parent == grandpa->left) {
        grandpa->left = right_child;
    } else {
        grandpa->right = right_child;
    }
    right_child->left = node_parent;
    node_parent->parent = right_child;
}


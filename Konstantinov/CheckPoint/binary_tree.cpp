//
// Created by alex on 06.12.2020.
//

#include <iostream>
#include <string>
#include "binary_tree.h"
// Binary search tree

using namespace std;

Tree::Tree() {
    this->root = nullptr;
}

Node::Node(const int key, const string data, Node *left, Node* right){
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

Node::Node(const int key, const string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

bool Tree::add(const int key, const string data){
    if(this->root == nullptr){
       this->root= new Node(key, data);
       if(this->root == nullptr){
           return false;
       }
       return true;
    }
    bool is_side_selected = false;
    bool side_choosing_flag = true;
    Node * pivot = this->root;
    while (!is_side_selected){

        if(pivot->key > key){

            if(pivot->left == nullptr){
                side_choosing_flag = false;
                is_side_selected = true;
                break;
            }

            pivot = pivot->left;
            continue;

        }

        if(pivot->key < key){

            if(pivot->right == nullptr){
                side_choosing_flag = true;
                is_side_selected = true;
                break;
            }

            pivot = pivot->right;
            continue;

        }

        if(pivot->key == key){
            return false;
        }

    }

    Node* new_node = new Node(key, data);
    if(new_node == nullptr){
        return false;
    }

    if(!side_choosing_flag){
        pivot->left = new_node;
    } else{
        pivot->right = new_node;
    }
    return true;
}

bool Tree::del(const int key) {
    Node* to_be_deleted = nullptr;
    Node *parent;
    Node** parent_ptr;
    if(this->root->key == key){
        to_be_deleted = this->root;

        if(!(to_be_deleted->left) && to_be_deleted->right) {
            this->root = to_be_deleted->right;
            delete to_be_deleted;
            return true;
        }

        if(!(to_be_deleted->left) && !(to_be_deleted->right)){
            delete to_be_deleted;
            return true;
        }
        if (to_be_deleted->left && !(to_be_deleted->right)) {
                this->root = to_be_deleted->left;
                delete to_be_deleted;
                return true;
            }

        Node * min_right = findMin(to_be_deleted->right);
        int min_key = min_right->key;
        string min_data = min_right->data;
        del(min_right->key);
        to_be_deleted->key = min_key;
        to_be_deleted->data = min_data;
        return true;
    }
    else {
        parent = findParent(key);

        if (parent == nullptr) {
            return false;
        }

        if (parent->key < key) {
            parent_ptr = &(parent->right);
            to_be_deleted = parent->right;
        } else {
            parent_ptr = &(parent->left);
            to_be_deleted = parent->left;
        }
    }

    if(to_be_deleted->right == nullptr && to_be_deleted->left == nullptr){
        *parent_ptr = nullptr;
        delete to_be_deleted;
    } else

        if(!to_be_deleted->right){
            *parent_ptr = to_be_deleted->left;
            delete to_be_deleted;
            return true;
        }

        if(!to_be_deleted->left){
            *parent_ptr = to_be_deleted->right;
            delete to_be_deleted;
            return true;
        }

        Node* min_right = findMin(to_be_deleted->right);

        if(min_right->right == nullptr){
            *parent_ptr = min_right;
            delete to_be_deleted;
        }
        else{
            int min_right_key = min_right->key;
            std::string min_right_data = min_right->data;

            del(min_right->key);

            to_be_deleted->key = min_right_key;
            to_be_deleted->data = min_right_data;

        }
    return true;
}


Node* Tree::findParent(const int key){
    Node* parent = this->root;

    while(true){
        if(parent->key > key){
            if(parent->left == nullptr){
                return nullptr;
            }
            if(parent->left->key != key){
                parent = parent->left;
                continue;
            } else {
                break;
            }
        } else
        if(parent->key < key){
            if(parent->right == nullptr){
                return nullptr;
            }
            if(parent->right->key != key){
                parent = parent->right;
                continue;
            } else {
                break;
            }
        } else
            return nullptr;
    }
    return parent;
}

Node* Tree::findMin(Node* pivot) {
    if(pivot->left == nullptr){
        return pivot;
    }
    else return findMin(pivot->left);
}


std::string Tree::find(const int key) {
    Node* parent = findParent(key);
    if(parent->left) {
        if (parent->left->key == key) {
            return parent->left->data;
        }
    }
    if(parent->right) {
        if (parent->right->key == key) {
            return parent->right->data;
        }
    }
    return "";
}
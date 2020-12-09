//
// Created by alex on 06.12.2020.
//

#include <iostream>
#include <string>
#include "binary_tree.h"
// Binary search tree

using namespace std;


Node::Node(){

}

Node::~Node(){

}

Tree::Tree() {
    this->root = NULL;
}

Tree::~Tree(){

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
    this->left = NULL;
    this->right = NULL;

}

bool Tree::add(const int key, const string data){
//    if(this->root->key == INT32_MIN && this->root->left == NULL && this->root->right == NULL){
//        this->root->key = key;
//        this->root->data = data;
//        return true;
//    }
    if(this->root == NULL){
       this->root= new Node(key, data);
       if(this->root == NULL){
           exit(-1);
       }
       return true;
    }

    bool side_choosing_flag = true;
    Node * pivot = this->root;
    while (side_choosing_flag){

        if(pivot->key > key){

            if(pivot->left == NULL){
                side_choosing_flag = false;
                break;
            }

            pivot = pivot->left;
            continue;

        }

        if(pivot->key < key){

            if(pivot->right == NULL){
                side_choosing_flag = true;
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

    if(new_node == NULL){
        exit(-1);
    }

    if(!side_choosing_flag){
        pivot->left = new_node;
    } else{
        pivot->right = new_node;
    }
    return true;
}

bool Tree::del(const int key) {

    Node* to_be_deleted = NULL;
    Node *parent;
    Node** parent_ptr;
    if(this->root->key == key){
        to_be_deleted = this->root;

        if(!(to_be_deleted->left)) {
            if (to_be_deleted->right) {
                this->root = to_be_deleted->right;
                delete to_be_deleted;
                return true;
            } else{
                delete to_be_deleted;
                return true;
            }

        } else {
            if (!(to_be_deleted->right)) {
                this->root = to_be_deleted->left;
                delete to_be_deleted;
                return true;
            } else{
                Node * min_right = findMin(to_be_deleted->right);
                int min_key = min_right->key;
                string min_data = min_right->data;
                del(min_right->key);
                to_be_deleted->key = min_key;
                to_be_deleted->data = min_data;
                return true;
            }

    }


    } else {
        parent = findParent(key);

        if (parent == NULL) {
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

    //to_be_deleted->data = "To Be Deleted";

    if(to_be_deleted->right == NULL && to_be_deleted->left == NULL){
        *parent_ptr = NULL;
        delete to_be_deleted;
    } else

        if(to_be_deleted->right == NULL){
            *parent_ptr = to_be_deleted->left;
            delete to_be_deleted;
            return true;
        }
        if(to_be_deleted->left == NULL){
            *parent_ptr = to_be_deleted->right;
            delete to_be_deleted;
            return true;
        }

        Node* min_right = findMin(to_be_deleted->right);
        min_right->data = "Min right";

        if(min_right->right == NULL){
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

    while(1){
        if(parent->key > key){
            if(parent->left == NULL){
                return NULL;
            }
            if(parent->left->key != key){
                parent = parent->left;
                continue;
            } else {
                break;
            }
        } else
        if(parent->key < key){
            if(parent->right == NULL){
                return NULL;
            }
            if(parent->right->key != key){
                parent = parent->right;
                continue;
            } else {
                break;
            }
        } else
            return NULL;
    }
    return parent;
}

Node* Tree::findMin(Node* pivot) {
    if(pivot->left == NULL){
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
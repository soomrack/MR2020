//
// Created by alex on 24.04.2021.
//

#include <cstring>
#include "b-tree.h"


BTree::BTree() {
    this->root = nullptr;
}

BTree::~BTree() {
    if(this->root != nullptr)
        Node::DeleteNode(root);
}

void Node::DeleteNode(Node *node) {
    if(node != nullptr) {
        for (int i = 0; i < B*2 - 1; i++) {
            if((node->children[i]) != nullptr)
                DeleteNode(node->children[i]);
            }
        delete(node);
        }
}

bool BTree::Add(int key){

    if (root == nullptr){
        Node *new_root = new Node;
        new_root->keys[0] = key;
        new_root->count_of_keys = 1;
        new_root->count_of_sons = 0;
        new_root->is_leaf       = true;
        new_root->parent        = nullptr;

        root = new_root;
        return true;
    }
    else {
        Node *sub_root = this->root;

        while(!sub_root->is_leaf){
            for(auto i = 0; i < sub_root->count_of_keys; i++){
                if(key == sub_root->keys[i]){
                    return false; // Such a key is already exist
                }
                if(key < sub_root->keys[i]) {
                    sub_root = sub_root->children[i];
                    break;
                }
            }
            sub_root = sub_root->children[sub_root->count_of_sons - 1];
        }

        Insert(key, sub_root);

        while(sub_root->count_of_keys == 2*B - 1){
            if(sub_root == root){
                Split(sub_root);
                break;
            } else {
                sub_root = Split(sub_root);
            }

        }
    }
    return true;
}

Node * BTree::Split(Node *sub_root) {

    if(sub_root->count_of_keys < 2*B - 1){
        return sub_root;
    }
    // B = 3 -> 4 as max, 2 as min
    // B = 4 -> 6 as max, 3 as min
    // B = B -> B*2 - 2 as max, B - 1 as min, B as median! // B-1 in 0+ notation
    Node *leftSon = new Node;
    memset(leftSon->keys, 0, sizeof(leftSon->keys));

    leftSon->count_of_keys = B - 1;
    for (int i = 0; i < B - 1; i ++){
        leftSon->keys[i] = sub_root->keys[i];
    }
    if(sub_root->count_of_sons != 0){
        for(int i = 0; i < B; i++){
            leftSon->children[i] = sub_root->children[i];
            leftSon->children[i]->parent = leftSon;
        }
        for(int i = B; i < 2*B + 1; i++){
            leftSon->children[i] = nullptr;
        }
        leftSon->is_leaf = false;
        leftSon->count_of_sons = B;
    } else {
        leftSon->is_leaf = true;
        leftSon->count_of_sons = 0;
        for(int i = 0; i < 2*B + 1; i ++){
            leftSon->children[i] = nullptr;
        }
    }

    Node *rightSon = new Node;

    memset(rightSon->keys, 0, sizeof(rightSon->keys));

    rightSon->count_of_keys = B - 1;
    for (int i = 0; i < B - 1; i ++){
        rightSon->keys[i] = sub_root->keys[i + B];
    }
    if(sub_root->count_of_sons != 0){
        for(int i = 0; i < B; i++){
            rightSon->children[i] = sub_root->children[i + B];
            rightSon->children[i]->parent = rightSon;
        }
        for(int i = B; i < 2*B + 1; i++){
            rightSon->children[i] = nullptr;
        }
        rightSon->is_leaf = false;
        rightSon->count_of_sons = B;
    } else {
        rightSon->is_leaf = true;
        rightSon->count_of_sons = 0;
        for(int i = 0; i < 2*B + 1; i ++){
            rightSon->children[i] = nullptr;
        }
    }

    if(sub_root->parent == nullptr){ //Sub root is an actual root

        sub_root->keys[0] = sub_root->keys[B - 1];

        for(int i = 1; i < 2*B; i++){
            sub_root->keys[i] = 0;
        }
        sub_root->children[0] = leftSon;
        sub_root->children[1] = rightSon;
        for(int i = 2; i < B*2 + 1; i++){
            sub_root->children[i] = nullptr;
        }

        sub_root->parent        = nullptr;
        sub_root->is_leaf       = false;
        sub_root->count_of_keys = 1;
        sub_root->count_of_sons = 2;

        leftSon ->parent = sub_root;
        rightSon->parent = sub_root;
    } else { //Sub root isn`t an actual root
        Insert(sub_root->keys[B - 1], sub_root->parent); // Insert median key into the parent of the node supposed to be
        int pivot = -1;

        for(int i = 0; i < 2*B - 1; i++){
            if(sub_root->parent->keys[i] == sub_root->keys[B - 1]){
                pivot = i;
                break;
            }
        }
        if(pivot == -1){
            return sub_root; // Means that something very bad happened...
        }

        leftSon->parent = sub_root->parent;
        rightSon->parent = sub_root->parent;

        sub_root->parent->children[pivot] = leftSon;
        sub_root->parent->children[pivot + 1] = rightSon;
        sub_root->parent->count_of_sons++;
        Node *parent = sub_root->parent;
        delete sub_root;
        return parent;
    }
}

void BTree::Insert(int key, Node *node) {

/**
 * Find a place to put a new key
 * Shift all the keys
 * And children too
 * Put a key
 * Congrats, you are awesome!
 **/
    int pivot = -1;
    for(int i = 0; i < node->count_of_keys; i++){
        if(key < node->keys[i]){
            pivot = i;                                      // Pivot is not the last element so we have to shift other elements
            for(int j = node->count_of_keys; j > pivot; j--){
                node->children[j + 1] = node->children[j];
                node->keys[j] = node->keys[j - 1];
            }
        }
    }

    if (pivot == -1){ // Pivot is our last element so we just add it
        pivot = node->count_of_keys;
    }

    node->keys[pivot] = key; // Because anyway we will add our new key here
    node->count_of_keys++;

    /// That seems fine, let`s try!

}
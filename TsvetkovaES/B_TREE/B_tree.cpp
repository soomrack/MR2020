// Created by alena on 22.03.2021.

#include "B_tree.h"

B_Node::B_Node(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;
    keys = new int[t*2-1];
    Children = new B_Node*[2*t];
    n_keys = 0;
}
void B_Node::traverse() {
    int i;
    for (i = 0; i < n_keys; i++) {
        if (leaf == false) {
            Children[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    if (leaf == false) {
        Children[i]->traverse();
    }
}

B_Node* B_Node::search(int key) {
    // Find the keys[i] greater than (or equal) to key
    int i = 0;
    while (i < n_keys && key > keys[i]) {
        i++;
    }
    // If the found the right key
    if (keys[i] == key) {
        return this;
    }
    // then, if this is a leaf node
    if (leaf == true) {
        return nullptr;
    }
    // Search at keys of i Child
    return Children[i]->search(key);
}
void B_Tree::insert(int key) {
    if (root == nullptr) { // First - if tree is empty
        root = new B_Node(t, true);
        root->keys[0] = key;
        root->n_keys = 1;
    } else { // Second - check the "full" of root
        if (root->n_keys == 2*t-1) { // Root is full
            B_Node *new_node = new B_Node(t, false);
            new_node->Children[0] = root;
            // Split the old root and move 1 key to the new root
            new_node->split_Child(0, root);
            // Insert to one of the splitted children the key
            int i = 0;
            if (new_node->keys[0] < key) {
                i++;
            }
            new_node->Children[i]->insert_smart(key);
            // Finally
            root = new_node;
        } else {  // Root is not full, we can insert key to root
            root->insert_smart(key);
        }
    }
}
void B_Node::insert_smart(int key) {
    // The greatest key
    int i = n_keys - 1;
    
    if (leaf == true) { // This child is a leaf node
        // Moves all greater keys (and, btw, find the location of new key to be inserted)
        while (i >= 0 && keys[i] > key) {
            keys[i+1] = keys[i];
            i--;
        }
        // Insert the right new key
        keys[i+1] = key;
        n_keys++;
    } else { // This child is not a leaf node
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        if (Children[i+1]->n_keys == 2*t-1) { // Child is full
            // Split the child and move 1 key up
            split_Child(i + 1, Children[i + 1]);
            // Insert to one of the splitted children the key
            if (keys[i+1] < key) {
                i++;
            }
        }
        // Child is not full
        Children[i + 1]->insert_smart(key);
    }
}

void B_Node::split_Child(int i, B_Node *old_child) {
    // Refactor the OLD child (split on two children)
    // new_child is going to store (t-1) keys of old_child
    B_Node *new_child = new B_Node(old_child->t, old_child->leaf);
    new_child->n_keys = t - 1;
    // Copy the last (t-1) keys of old_child to new_child
    for (int j = 0; j < t-1; j++) {
        new_child->keys[j] = old_child->keys[j + t];
    }
    // Copy the last t children of old_child to new_child
    if (old_child->leaf == false) {
        for (int j = 0; j < t; j++) {
            new_child->Children[j] = old_child->Children[j + t];
        }
    }
    old_child->n_keys = t - 1;
    
    // Refactor the PARENT node
    // Moves all children (and, btw, find the location of new child to be inserted)
    for (int j = n_keys; j >= i+1; j--) {
        Children[j+1] = Children[j];
    }
    Children[i+1] = new_child;
    // Moves all greater keys (and, btw, find the location of new  MIDDLE key to be inserted)
    for (int j = n_keys - 1; j >= i; j--) {
        keys[j+1] = keys[j];
    }
    keys[i] = old_child->keys[t - 1];
    n_keys++;
}
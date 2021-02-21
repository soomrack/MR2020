#include "My_header.h"

Node* Tree::search(const int key, Node *&search_node) {
    // We got to nullptr node: there is no node with this key. Return false
    if(search_node == nullptr) {
        return nullptr;
    }
    // We got to node with right key. The new_node contains address of this node,
    // the parent contains address of it's parent :)
    if(key == search_node->key) {
        return search_node;
    }
    else if(key > search_node->key) {
        return search(key, search_node->right);
    }
    else {
        return search(key, search_node->left); // ищем в сторону меньших
    }
}

std::string Tree::find(const int key) {
    if (!root) {
        std::cout << termcolor::reset << "The tree is empty!\n";
        return "";
    }
    Node* found_node = search(key, root);
    if(found_node) {
        //std::cout << termcolor::reset << found_node->data.c_str();
        return found_node->data;
    }
    else { // found_node is nullptr
        std::cout << termcolor::reset << "There is no key in the tree!\n";
        return "";
    }
}

void Tree::Print_tree (Node* node, int h) { // нач. усл.: node = root, h = 0
    if  (node) {
        Print_tree (node->right,h+1); // уходим в самое права
        for (int i=1; i<=h; i++) {
            std::cout << "     ";
        }
        if(node->color == COLOR::BLACK) {
            std::cout << termcolor::reset << node->key << " (" << node->data.c_str() << ")\n";
        } else {
            std::cout << termcolor::red << node->key << " (" << node->data.c_str() << ")\n";
        }
        Print_tree (node->left,h+1);
    }
}

Node * Tree::search_min(Node *root) {
    Node* current = root;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}
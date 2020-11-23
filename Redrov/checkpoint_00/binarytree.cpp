#include <iostream>
#include <string>


class Node {
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
public:
    Node(const int key, const std::string data);
    ~Node();
};


Node::Node(const int key, const std::string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::~Node(){
    left = nullptr;
    right = nullptr;
    this->key = NULL;
    this->data = "";
}


class Tree {
private:
    Node *root;
    Node* findNode(Node* root, int key);
    Node* findParent(Node* root, int key);
    Node* minNode(Node* root);
public:
    bool add(const int key, const std::string data);
    bool del(const int key); 
    std::string find(const int key);
public:
    Tree();
    ~Tree();
    
};


Tree::Tree(){
    root = nullptr;
}

Tree::~Tree(){
    while(root != nullptr){ del(root->key); }
}

bool Tree::add(const int key, const std::string data){
    if (root == nullptr){
        root = new Node(key, data);
    }
    else {
        Node* child = new Node(key, data);
        Node* parent = findNode(root, key);
        if (parent->key == key){
            return false;
        }
        if(parent->key > key){
            parent->left = child;
            return true;
        }
        else{
            parent->right = child;
            return true;
        }
    }

}

Node* Tree::findNode(Node * root, int key){
        if (root->key == key){
            return root;
        }
        else if (root->key < key) {
            if (root->right == nullptr)
                return root;
            return findNode(root->right, key);
        }
        else {
            if (root->left == nullptr)
                return root;
            return findNode(root->left, key);
        }
}

std::string Tree::find(const int key){
    if (root == nullptr)
        return "";
    Node* node = findNode(root, key);
    if (node->key == key){
        return node->data;
    }
    else{
        return "";
    }
}


bool Tree::del(const int key){
    if (find(key) == ""){
        return false;
    }
    Node* node = findNode(root, key);
    Node* parent = findParent(root, key);
    if ((node->left == nullptr) && (node->right == nullptr)){
        if (node == root){
            root = nullptr;
        }
        else if(parent->left == node){
            parent->left = nullptr;
        }
        else{
            parent->right = nullptr;
        }
        delete node;
        return true;
    }
    if ((node->left == nullptr)){
        if (node == root){
            root = node->right;
        }
        else if(parent->left == node){
            parent->left = node->right;
        }
        else{
            parent->right = node->right;
        }
        delete node;
        return true;
    }
    if ((node->right == nullptr)){
        if (node == root){
            root = node->left;
        }
        else if(parent->left == node){
            parent->left = node->left;
        }
        else{
            parent->right = node->left;
        }
        delete node;
        return true;
    }

    Node* right_child = node->right;
    Node* min_Node = minNode(right_child);
    Node* min_Parent = findParent(root, min_Node->key);
    int min_key = min_Node->key;
    std::string min_data = min_Node->data;
    del(min_Node->key);
    node->key = min_key;
    node->data = min_data;
    return true;
    
}

Node* Tree::findParent(Node * root, int key) {
    if (root->key < key) {
        if (root->right == nullptr)
            return nullptr;
        if (root->right->key == key){
            return root;
        }
        return findParent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->key == key){
            return root;
        }
        return findParent(root->left, key);
    }
    return nullptr;
}

Node* Tree::minNode(Node* node){
    if (node->left == nullptr){
        return node;
    }
    else{
        return minNode(node->left);
    }
}


int main() {
    return 0;
}
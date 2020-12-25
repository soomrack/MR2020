#include <iostream>
#include <algorithm>
#include <string>
const std::string  nothing = "";
class Node {
public:
    int key;
    std::string data;
public:
    Node* left;
    Node* right;
public:
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, Node *left, Node *right);
    Node();
    ~Node();
};

Node::Node (int key, std::string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
};



class Tree {
private:
    Node* root;
public:
    std::string find(const int key);
    Node* prepareNewNode(int key, Node* root);
    bool add(int key, std::string data);
    Node* search(int key, Node* root);
    bool del(int key);
    Node* searchParent(int key, Node* root);
    Node* findMin(Node* root);
public:
    Tree() {
        root = nullptr;
    };
    ~Tree();
};


Node* Tree::prepareNewNode(int key, Node* root) {
    if (key < root->key) {
        if (root->left == nullptr) return(root);
        return(prepareNewNode(key, root->left));
    }
    else {
        if (root->right == nullptr) return(root);
        return(prepareNewNode(key, root->right));
    }
}

bool Tree::add(int key, const std::string data) {
    Node* child = new Node(key, data);

    if (root == nullptr) {
        root = child;
        return true;
    }

    Node* parent = prepareNewNode(key, child);
    if (key < parent->key) parent->left = child;
    else parent->right = child;
}


Node* Tree::search(int key, Node* root) {
    if (key == root->key) return root;
    if (key < root->key) return search(key, root->left);
    else return search(key, root->right);
}

bool Tree::del(int key){
    Node* deleteData = search(key, root);
    if (deleteData == nullptr) return false;
    Node* parentDeleteData = searchParent(key, root);

    if ((deleteData->left == nullptr) && (deleteData->right != nullptr)) {
        if (parentDeleteData->left == deleteData) parentDeleteData->left= deleteData->right;
        else parentDeleteData->right = deleteData->right;
        return true;
    }
    if ((deleteData->left != nullptr) && (deleteData->right == nullptr)) {
        if (parentDeleteData->left == deleteData) parentDeleteData->left = deleteData->left;
        else parentDeleteData->right = deleteData->left;
        return true;
    }
    if ((deleteData->left== nullptr) && (deleteData->right == nullptr)) {
        if (parentDeleteData->left == deleteData) parentDeleteData->left = nullptr;
        else parentDeleteData->right = nullptr;
        return false;
    }
    Node* temp = findMin(deleteData->right);
    if (temp == deleteData->right) {
        deleteData->key = temp->key;
        deleteData->data = temp->data;
        deleteData->right = temp->right;
        return true;
    }
    else {
        deleteData->data = temp->data;
        deleteData->key = temp->key;
        del(temp->key);
        return true;
    }
}

Node* Tree::searchParent(int key, Node *root) {
    if ((key == root->left->key) || (key == root->right->key)) return root;
    if (key < root->key) searchParent(key, root->left);
    else searchParent(key, root->right);
}

Node* Tree::findMin(Node *root) {
    Node* min = root;
    while(min->left != nullptr) {
        min = min->left;
    }
    return min;
}

std::string Tree::find(const int key)
{
    Node *el = search(key);
    if (el == nullptr)
        return (nothing);
    return (el->data);
}

int main() {
    Tree test;
    test.add(1, nullptr);
    test.add(2, nullptr);
    test.add(1000, nullptr);
    return 0;
}
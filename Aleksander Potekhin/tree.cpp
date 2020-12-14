#include <iostream>
#include <string>


class Node {
public:
    int key;
    std::string data;
public:
    Node* left;
    Node* right;
public:
    Node();
    Node(const int key, const std::string data);
};


Node::Node() {
    this->key = 0;
    this->data = "";
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data) {
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}


class Tree {
private:
    Node* root;
    Node* find_Node(Node* root, int key);
    Node* find_Parent(Node* root, int key);
    Node* min_Node(Node* root);
public:
    bool add(const int key, const std::string data);  // false если ключ уже существует
    bool del(const int key);  // false если нет ключа
    std::string find(const int key);  // возвращает '' если нет ключа
public:
    Tree();
    ~Tree();

};


Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    while (root != nullptr) { del(root->key); }
}

bool Tree::add(const int key, const std::string data) {
    if (root == nullptr) {
        root = new Node(key, data);
        return true;
    }

    Node* child = new Node(key, data);
    Node* parent = find_Node(root, key);
    if (parent->key == key) {
        return false;
    }
    if (parent->key > key) {
        parent->left = child;
        return true;
    }

    parent->right = child;
    return true;

}


Node* Tree::find_Node(Node* root, int key) {
    if (root->key == key) {
        return root;
    }
    else if (root->key < key) {
        return (root->right == nullptr) ? root : find_Node(root->right, key);
    }
    return (root->left == nullptr) ? root : find_Node(root->left, key);
}

std::string Tree::find(const int key) {
    if (root == nullptr)
        return "";
    Node* node = find_Node(root, key);
    if (node->key == key) {
        return node->data;
    }
    else {
        return "";
    }
}


bool Tree::del(const int key) {
    if (find(key) == "") {
        return false;
    }
    Node* node = find_Node(root, key);
    Node* parent = find_Parent(root, key);
    if ((node->left == nullptr) && (node->right == nullptr)) {
        if (node == root) {
            root = nullptr;
        }
        else if (parent->left == node) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete node;
        return true;
    }
    if ((node->left == nullptr)) {
        if (node == root) {
            root = node->right;
        }
        else if (parent->left == node) {
            parent->left = node->right;
        }
        else {
            parent->right = node->right;
        }
        delete node;
        return true;
    }
    if ((node->right == nullptr)) {
        if (node == root) {
            root = node->left;
        }
        else if (parent->left == node) {
            parent->left = node->left;
        }
        else {
            parent->right = node->left;
        }
        delete node;
        return true;
    }
    Node* right_child = node->right;
    Node* minNode = min_Node(right_child);
    Node* minParent = find_Parent(root, minNode->key);
    int minkey = minNode->key;
    std::string mindata = minNode->data;
    del(minNode->key);
    node->key = minkey;
    node->data = mindata;
    return true;

}

Node* Tree::find_Parent(Node* root, int key) {
    if (root->key < key) {
        if (root->right == nullptr)
            return nullptr;
        if (root->right->key == key) {
            return root;
        }
        return find_Parent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->key == key) {
            return root;
        }
        return find_Parent(root->left, key);
    }
    return nullptr;
}

Node* Tree::min_Node(Node* node) {
    if (node->left == nullptr) {
        return node;
    }
    else {
        return min_Node(node->left);
    }
}


int main() {
    Tree tree;
    std::cout << "The end." << std::endl;
    return 0;
}
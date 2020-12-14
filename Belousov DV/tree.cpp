#include <iostream>
#include <string>

// Binary search tree

class Node {
public:
    int key;
    std::string data;
public:
    Node* left;
    Node* right;
public:
    Node();
    Node(int key, std::string data);
    Node(int key, std::string data, Node* left, Node* right);
    ~Node();
};


class Tree {
private:
    Node* root;
    Node* lookForNode(Node* root, int key);
    Node* findParent(Node* root, int key);
    Node* findMin(Node* root);
public:
    bool add(const int key, std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() {
    left = nullptr;
    right = nullptr;
}

Node::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
}

Node::Node(int key, std::string data, Node* left, Node* right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

Node::~Node() {
    delete left;
    delete right;
}


Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    delete root;
}

Node* Tree::lookForNode(Node* root, int key) {
    if (root == nullptr) return root;
    if (root->key == key) return root;
    if (root->key > key) return lookForNode(root->left, key);
    return lookForNode(root->right, key);
}

Node* Tree::findParent(Node* root, int key) {
    if (root->key <= key) {
        if (root->right == nullptr)
            return root;
        return findParent(root->right, key);
    }

    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        return findParent(root->left, key);
    }
    return nullptr;
}

Node* Tree::findMin(Node* root) {
    Node* min = root;
    while (min->left != nullptr) {
        min = min->right;
    }
    return min;
}

std::string Tree::find(const int key) {
    Node* temp = root;
    temp = lookForNode(temp, key);
    if (temp == nullptr)
        return "";
    return temp->data;
}

bool Tree::add(const int key, std::string data) {
    Node* child = new Node(key, data);
    if (lookForNode(root, key) != nullptr)
        return false;

    if (root == nullptr) {
        root = child;
        return true;
    }

    Node* parent = findParent(root, key);
    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;
    return true;
}

bool Tree::del(const int key) {
    Node* deletedNode = lookForNode(root, key);
    Node* parentOfDeletedNode = findParent(root, key);
    if (deletedNode == nullptr)
        return false;

    if (deletedNode->left == nullptr && deletedNode->right == nullptr)
    {
        if (parentOfDeletedNode->left == deletedNode)
        {
            parentOfDeletedNode->left = nullptr;
            delete deletedNode;
            return true;
        }
        parentOfDeletedNode->right = nullptr;
        delete deletedNode;
        return true;
    }

    if (deletedNode->left == nullptr && deletedNode->right != nullptr)
    {
        if (parentOfDeletedNode->left == deletedNode)
        {
            parentOfDeletedNode->left = deletedNode->right;
            delete deletedNode;
            return true;
        }
        parentOfDeletedNode->right = deletedNode->right;
        delete deletedNode;
        return true;
    }

    if (deletedNode->left != nullptr && deletedNode->right == nullptr)
    {
        if (parentOfDeletedNode->left == deletedNode)
        {
            parentOfDeletedNode->left = deletedNode->left;
            delete deletedNode;
            return true;
        }
        parentOfDeletedNode->right = deletedNode->left;
        delete deletedNode;
        return true;

    }

    if ((deletedNode->left != nullptr) && (deletedNode->right != nullptr))
    {
        Node* temp = findMin(deletedNode->right);
        if (temp == deletedNode->right)
        {
            deletedNode->key = temp->key;
            deletedNode->data = temp->data;
            deletedNode->right = temp->right;
            delete temp;
            return true;
        }
        deletedNode->data = temp->data;
        deletedNode->key = temp->key;
        del(temp->key);
        return true;
    }
    return true;
}


int main() {
  
    std::cout << "The end." << std::endl;
}
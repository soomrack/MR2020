#include <iostream>
#include <string>
std::string error = "\0";

class Node {
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
public:
    Node();
    Node(const int key, const std::string data);
    Node(int key, std::string data, Node *left, Node *right);
    ~Node();
};

class Tree {
private:
    Node *root;
    Node* findNode(Node* root, int key);
    Node* findParent(Node * root, int key);
    Node* min(Node* root);
public:
    bool add(const int key, std::string data);
    bool del(const int key);
    std::string find(const int key);
public:
    Tree();
    ~Tree();
};

Node::Node(){
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(int key,  std::string data,  Node *left,  Node *right)
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

Node* Tree::findNode(Node *root, int key) {
    if (root->key == key) {
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

Node* Tree::findParent(Node *root, int key){
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

Node* Tree::min(Node* root)
{
    if (root->left == nullptr)
        return root;
    else
        return min(root->left);
}

bool Tree::add(const int key, std::string data) {
    if (root == nullptr) {
        root = new Node(key, data);
    }
    else {
        Node* child = new Node(key, data);
        Node* parent = findNode(root, key);
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
}

bool Tree::del(const int key){
    Node* deleteNode = findNode(root,key);
    Node* ParentOfDeleteNode = findParent(root, key);
    if (deleteNode == nullptr)
        return false;
    if (deleteNode->left == nullptr && deleteNode->right == nullptr)
    {
        if (ParentOfDeleteNode ->left == deleteNode)
        {
            ParentOfDeleteNode ->left = nullptr;
        }
        else
        {
            ParentOfDeleteNode->right = nullptr;
        }
        return true;
    }
    if (deleteNode->left == nullptr && deleteNode->right != nullptr)
    {
        if (ParentOfDeleteNode->left == deleteNode)
        {
            ParentOfDeleteNode->left = deleteNode->right;
        }
        else
        {
            ParentOfDeleteNode->right = deleteNode->right;
        }
        return true;
    }
    if (deleteNode->left != nullptr && deleteNode->right == nullptr)
    {
        if (ParentOfDeleteNode->left == deleteNode)
        {
            ParentOfDeleteNode->left = deleteNode->left;
        }
        else
        {
            ParentOfDeleteNode->right = deleteNode->left;
        }
        return true;
    }
    if ((deleteNode->left != nullptr) && (deleteNode->right != nullptr))
    {
        Node* temp = min(deleteNode->right);
        if (temp == deleteNode->right)
        {
            deleteNode->key = temp->key;
            deleteNode->data = temp->data;
            deleteNode->right = temp->right;
            delete temp;
        }
        else
        {
            deleteNode->data = temp->data;
            deleteNode->key = temp->key;
            del(temp->key);
        }
        return true;
    }
}

std::string Tree::find(const int key) {
    Node* node = root;
    node = findNode(node,key);
    if (node == nullptr)
        return error;
    return node->data;
}

Tree::Tree(){
    root = nullptr;
}

Tree::~Tree() {
    while (root != nullptr) {del(root->key);}
}

int main() {
    Tree tree;
    tree.add(12, "HelloWorld!");
    tree.add(5, "1");
    tree.add(15, "2");

    std::cout<<tree.find(12)<<std::endl;
    std::cout<<tree.find(5)<<std::endl;
    tree.del(15);
    std::cout<<tree.find(15)<<std::endl;

    std::cout << "The end." << std::endl;
    return 0;
}
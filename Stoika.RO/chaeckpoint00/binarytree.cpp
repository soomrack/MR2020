#include <iostream>
#include <string>

std::string error = "\0";

// Binary search tree

class Node 
{
public:
    int key;
    std::string data;
public:
    Node* left;
    Node* right;
public:
    Node();
    Node(int key, std::string data);
    Node(const int key, const std::string data, Node* left, Node* right);
    ~Node();
};

Node::Node()
{
    left = nullptr;
    right = nullptr;
}

Node::Node(int key, std::string data)
{
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

Node ::~Node()
{
    delete left;
    delete right;
}

class Tree 
{
private:
    Node* root;
    Node* findmin(Node* p);
    Node* checkNode(Node* root, int key);
    Node* findParentWhenDeleting(Node* root, int key) ;
    public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node* Tree::findmin(Node* p)
{
    if (p->left)
        return findmin(p->left);
    else
        return p;
}

Node* Tree::findParentWhenDeleting(Node* root, int key)
{
    if (root->right->key == key) return root;
    if (root->left->key == key) return root;
    if (root->key <= key) return findParentWhenDeleting(root->right, key);
    return findParentWhenDeleting(root->left, key);
};

Node* Tree::checkNode(Node* root, int key)
{
    if (root == nullptr) return root;
    if (root->key == key) return root;
    else if (root->key > key) return checkNode(root->left, key);
    else return checkNode(root->right, key);
}

Tree::Tree() 
{
    root = nullptr;
}

Tree::~Tree() 
{
    delete root; 
}

std::string Tree::find(const int key) 
{
    Node* current = root;
    if (current == nullptr)
        return error;
    while (current->key != key)
    {
        if (key > current->key)
        {
            if (current->right == nullptr)
                return error;
            else
                current = current->right;
        }
        else if (key < current->key)
        {
            if (current->left == nullptr)
                return error;
            else
                current = current->left;
        }
    }
    return current->data;
}

bool Tree::add(const int key, const std::string data) 
{
    Node* current = root;
    if (current == nullptr) 
    {
        root = new Node;
        root->key = key;
        root->data = data;
        return true;
    }
    while (true)
    {
        if (current->key < key)
        {
            if (current->right == nullptr)
            {
                current->right = new Node;
                Node* newNode = current->right;
                newNode->key = key;
                newNode->data = data;
                return true;
            }
            else
                current = current->right;
        }
        else if (current->key > key)
        {
            if (current->left == nullptr)
            {
                current->left = new Node;
                Node* newNode = current->left;
                newNode->key = key;
                newNode->data = data;
                return true;
            }
            else current = current->left;
        }
        else return false;
    }
}

bool Tree::del(const int key)
{
    Node* deleteNode = checkNode(root, key);
    Node* ParentOfDeleteNode = findParentWhenDeleting(root, key);
    if (deleteNode == nullptr)
        return false;
    if (deleteNode->left == nullptr && deleteNode->right == nullptr)
    {
        if (ParentOfDeleteNode->left == deleteNode)
        {
            ParentOfDeleteNode->left = nullptr;
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
        Node* temp = findmin(deleteNode->right);
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
};


int main() 
{
    std::cout << "The end." << std::endl;
}
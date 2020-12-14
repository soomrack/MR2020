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
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, Node* left, Node* right);
    Node();
    ~Node();
};

class Tree {
private:
    Node* root;
    Node* findmin(Node* p) { return p->left ? findmin(p->left) : p; }
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    Node* search(int key);
    Node* searchprev(int key);
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() 
{
    left = nullptr; 
    right = nullptr;
}

Node::Node(const int key, const std::string data)
{
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data, Node* left, Node* right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

Node::~Node() 
{
    delete left; delete right; 
}

Tree::Tree() 
{ 
    root = nullptr; 
}

Tree::~Tree() 
{ 
    delete root;
}

Node* Tree::search(int key)
{
    Node* iterator = root;
    if (iterator == nullptr)
        return iterator;
    while (iterator->key != key)
    {
        if (iterator->key < key)
        {
            if (iterator->right == nullptr)
                return nullptr;
            iterator = iterator->right;
        }
        if (iterator->key > key)
        {
            if (iterator->left == nullptr)
                return nullptr;
            iterator = iterator->left;
        }
    }
    return iterator;
}

Node* Tree::searchprev(int key)
{
    if (root == nullptr)
        return nullptr;

    Node* iterator = root;
    Node* prev = nullptr;
    while (iterator->key != key)
    {
        if (iterator->key > key) {
            if (iterator->left != nullptr)
            {
                prev = iterator;
                iterator = iterator->left;
            }
            else
            {
                return nullptr;
            }
        }
        if (iterator->key < key)
        {
            if (iterator->right != nullptr)
            {
                prev = iterator;
                iterator = iterator->right;
            }
            else
                return nullptr;
        }
    }
    return prev;
}

bool Tree::add(const int key, const std::string data)
{
    if (root == nullptr)
    {
        root = new Node(key, data);
        return true;
    }
    Node* iterator = root;
    while (true)
    {
        if (iterator->key == key)
        {
            return false;
        }
        if (iterator->key > key)
        {
            if (iterator->left == nullptr)
            {
                iterator->left = new Node(key, data);
                return true;
            }
            iterator = iterator->left;
        }
        if (iterator->key < key)
        {
            if (iterator->right == nullptr)
            {
                iterator->right = new Node(key, data);
                return true;
            }
            iterator = iterator->right;
        }
    }
}

bool Tree::del(const int key)
{
    Node* todelete = search(key);
    if (todelete == nullptr)
        return false;
    Node* prev = searchprev(key);

    Node* todelete_left = todelete->left;
    Node* todelete_right = todelete->right;

    if (todelete == root)
    {
        if (todelete_right != nullptr)
        {
            findmin(todelete_right)->left = todelete_left;
            root = todelete_right;
        }
        else
        {
            root = todelete_left;
        }
        delete todelete;
        return true;
    }
    if (todelete_right != nullptr)
    {
        findmin(todelete_right)->left = todelete_left;
        Node* prevright = prev->right;
        if (prevright->key == todelete->key)
        {
            prev->right = todelete_right;
        }
        else
            prev->left = todelete_right;
    }
    else
    {
        if (prev->left == todelete)
        {
            prev->left = todelete_left;
        }
        else prev->right = todelete_left;
    }
    delete todelete;
    return true;
}

std::string Tree::find(const int key)
{
    Node* unit = search(key);
    if (unit == nullptr)
        return "";
    return (unit -> data);
}

int main()
{
    std::cout << "The end." << std::endl;
}
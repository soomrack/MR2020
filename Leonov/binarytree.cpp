#include <iostream>
#include <string>

using namespace std;
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
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, const Node* left, const Node* right);
    ~Node();
};


class Tree {
private:
    Node* root;
    Node* find_min(Node* tree) // поиск узла с минимальным ключом в дереве tree
    {
        return tree->left ? find_min(tree->left) : tree;
    }
public:
    bool add(const int key, const std::string data);  // false если ключ уже создан.
    bool del(const int key);  // false если нет ключа.
    std::string find(const int key);  // Возвращать '' если нет ключа.
public:
    Tree();
    ~Tree();
};

Node::Node()
{
    left = nullptr;
    right = nullptr;
}

Tree::Tree()
{
    root = nullptr;
}

bool Tree::add(const int key, const std::string data)
{
    Node* current = root;
    if (current == nullptr)
    {
        root = new Node;
        root->key = key;
        root->data = data;
    }
    else
    {
        while (true)
        {
            if (current->key < key)
            {
                if (current->right = nullptr)
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
                if (current->left = nullptr)
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
}

bool Tree::del(const int key)
{
    Node* current = root;
    Node* prev = nullptr;
    if (current = nullptr)
        return false;
    else 
    {
        while (current->key != key)
        {
            if (current->key < key)
            {
                if (current->right != nullptr)
                {
                    prev = current;
                    current = current->right;
                }
                else return false;   
            }
            else if (current->key > key)
            {
                if (current->left != nullptr)
                {
                    prev = current;
                    current = current->left;
                }
                else return false;
            }
        }
    }
    Node* l = current->left;
    Node* r = current->right;

    if (current != root)
    {
        if (r != nullptr)
        {
            find_min(r)->left = l;
            Node* prev_right = prev->right;
            if (prev_right->key = current->key)
            {
                prev->right = r;
            }
            else prev->left = r;
        }
        else
        {
            if (prev->left == current)
            {
                prev->left = l;
            }
            else prev->right = l;
        }
    }
    else
    {
        if (r != nullptr)
        {
            find_min(r)->left = l;
            root = r;
        }
        else root = l;
    }
    delete current;
    return true;
}

std::string Tree::find(const int key)
{
    Node* current = root;
    if (current == nullptr)
        return " ";
    else
    {
        while (true)
        {
            if (current->key < key)
            {
                if (current->right == nullptr)
                    return " ";
                else current = current->right;
            }
            else if (current->key > key)
            {
                if (current->left == nullptr)
                    return " ";
                else current = current->left;
            }
        }
        return (current->data);
    }
}

Tree::~Tree() { delete root; }
Node::~Node() { delete left; delete right; }

int main() {
    cout << "The end." << endl;
}
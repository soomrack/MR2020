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
//    Node(const int key, const std::string data, const Node* left, const Node* right);
//    ~Node();
};


class Tree {
private:
    Node* root;
    Node* find_min(Node* tree) // поиск узла с минимальным ключом в дереве tree
    {
        return tree->left ? find_min(tree->left) : tree;
    }
    Node* find_Node(Node* root, int key);
    Node* find_parent(Node* root, int key);
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
    this->key = 0;
    this->data = "";
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data) 
{
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

std::string Tree::find(const int key) 
{
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

Tree::Tree()
{
    root = nullptr;
}

bool Tree::add(const int key, const std::string data)
{
    if (root == nullptr)
    {
        root = new Node(key, data);
    }
    else
    {
        Node* chiled = new Node(key, data);
        Node parent = find_Node(root, key);
        if (parent->key = key)
        {
            return false;
        }
        if (parent->key > key)
        {
            parent->left = child;
            return true;
        }
        parent->right = child;
        return true;
    }
}

bool Tree::del(const int key)
{
    if (find(key) == "")
        return false;
    Node* parent = find_parent(root, key);
    Node* node = find_Node(root, key);
    if ((node->right == nullptr) && (node->left == nullptr))
    {
        if (node == root)
            root = nullptr;
        else if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete node;
        return true;
    }
    if (node->left == nullptr)
    {
        if (node == root)
            root = node->right;
        else if (parent->left == node)
            parent->left = node->right;
        else
            parent->right = node->right;
        delete node;
        return true;
    }
    if (node->right == nullptr)
    {
        if (node == root)
            root = node->left;
        else if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->left;
        delete node;
        return true;
    }
    Node* right_child = node->right;
    Node* minNode = min_Node(right_child);
    Node* minparent = min_parent(root, minNode->key);
    int minkey = minNode->key;
    std::string data = minNode->data;
    del(minNode->key);
    node->data = mindata;
    node->key = minkey;
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

Tree::~Tree() 
{ 
    while (root != nullptr)
    {
        del(root->key);
    };
}

Node* Tree::find_Node(Node* root, int key) {
    if (root->key == key) 
        return root;
    else if (root->key < key) 
    {
        if (root->right == nullptr)
            return root;
        return find_Node(root->right, key);
    }
    else {
        if (root->left == nullptr)
            return root;
        return find_Node(root->left, key);
    }
}

Node* Tree::find_Parent(Node* root, int key) 
{
    if (root->key < key) 
    {
        if (root->right == nullptr)
            return nullptr;
        if (root->right->key == key) 
            return root;
        return find_Parent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->key == key) 
            return root;
        return find_Parent(root->left, key);
    }
    return nullptr;
}

Node* Tree::min_Node(Node* node) 
{
    if (node->left == nullptr) 
        return node;
    else 
        return min_Node(node->left);
}

//Node::~Node() 
//{
//    left = nullptr;
//    right = nullptr;
//    this->key = NULL;
//    this->data = "";
//}

int main() {
    cout << "The end." << endl;
}
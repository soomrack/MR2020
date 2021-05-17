#include <iostream>
#include <string>

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
    Node(int key, std::string data, Node* left, Node* right);
    ~Node();
};

class Tree 
{
private:
    Node* root;
    Node* get_Node(Node* root, int key);
    Node* get_Parent(Node* root, int key);
    Node* get_Min(Node* root);
public:
    bool add(const int key, std::string data);  
    bool del(const int key); 
    std::string find(const int key);  
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

Node* Tree::get_Node(Node* root, int key) 
{
    if (root == nullptr) 
    { 
        return root; 
    }
    if (root-> key == key) 
    {
        return root;
    }
    if (root->key > key) 
    { 
        return getNode(root->left, key); 
    }
    return getNode(root->right, key);
}

Node* Tree::get_Parent(Node* root, int key) 
{
    if (root->key < key) 
    {
        if (root->right == nullptr)
        {
            return root;
        }
        if (root->right->key == key)
        {
            return root;
        }
        return getParent(root->right, key);
    }

    if (root->key > key) {
        if (root->left == nullptr)
        {
            return root;
        }
        if (root->left->key == key)
        {
            return root;
        }
        return getParent(root->left, key);
    }
    return nullptr;
}

Node* Tree::get_Min(Node* root) 
{
    Node* min = root;
    while (min->left != nullptr) 
    {
        min = min->left;
    }
    return min;
}

std::string Tree::find(const int key) 
{
    Node* temp = root;
    temp = get_Node(temp, key);
    if (temp == nullptr)
    {
        return "";
    }
    return temp->data;
}

bool Tree::add(const int key, std::string data) 
{
    Node* child = new Node(key, data);
    if (getNode(root, key) != nullptr)
    {
        return false;
    }

    if (root == nullptr) 
    {
        root = child;
        return true;
    }

    Node* parent = get_Parent(root, key);
    if (key <= parent->key)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
    return true;
}

bool Tree::del(const int key) {
    Node* deleted_node = get_Node(root, key);
    Node* parent_of_deleted_node = get_Parent(root, key);
    if (deleted_node == nullptr)
    {
        return false;
    }

    if (deleted_node->left == nullptr && deleted_node->right == nullptr)
    {
        if (parent_of_deleted_node->left == deleted_node)
        {
            parent_of_deleted_node->left = nullptr;
            delete deleted_node;
            return true;
        }
        parent_of_deleted_node->right = nullptr;
        delete deleted_node;
        return true;
    }

    if (deleted_node->left == nullptr && deleted_node->right != nullptr)
    {
        if (parent_of_deleted_node->left == deleted_node)
        {
            parent_of_deleted_node->left = deleted_node->right;
            delete deleted_node;
            return true;
        }
        parent_of_deleted_node->right = deleted_node->right;
        delete deleted_node;
        return true;
    }

    if (deleted_node->left != nullptr && deleted_node->right == nullptr)
    {
        if (parent_of_deleted_node->left == deleted_node)
        {
            parent_of_deleted_node->left = deleted_node->left;
            delete deleted_node;
            return true;
        }
        parent_of_deleted_node->right = deleted_node->left;
        delete deleted_node;
        return true;
    }

    if ((deleted_node->left != nullptr) && (deleted_node->right != nullptr))
    {
        Node* temp = get_Min(deleted_node->right);
        if (temp == deleted_node->right)
        {
            deleted_node->key = temp->key;
            deleted_node->data = temp->data;
            deleted_node->right = temp->right;
            delete temp;
            return true;
        }
        deleted_node->data = temp->data;
        deleted_node->key = temp->key;
        del(temp->key);
        return true;
    }
    return true;
}


int main() 
{

}

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
    Node();
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, Node *left, Node *right);
};


class Tree {
private:
    Node *root;
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
private:
    void insert(const int key, const std::string data);
    bool insert(const int key, const std::string data, Node* sub_tree);
    Node* search(int key, Node* sub_tree);
    Node* get_parent(const int key, Node* sub_tree);
    Node* get_max_node_in_sub_tree(Node *root);
    void remove(Node *target);
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

Node::Node(const int key, const std::string data, Node *left, Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    delete root;
}

void Tree::insert(const int key, const std::string data)
{
    if (root != nullptr)
        insert(key, data, root);
    else
        root = new Node(key, data);
}

bool Tree::insert(int key, const std::string data, Node* sub_tree)
{
    if (find(key) != "")
        return false;
    if (key < sub_tree->key)
    {
        if (sub_tree->left != nullptr)
        {
            insert(key, data, sub_tree->left);
            return true;
        }
        sub_tree->left = new Node(key, data);
        return true;
    }
    if (sub_tree->right != nullptr)
    {
        insert(key, data, sub_tree->right);
        return true;
    }
    sub_tree->right = new Node(key, data);
    return true;
}

bool Tree::add(const int key, const std::string data)
{
    if (find(key) != "")
        return false;
    insert(key, data);
    return true;
}

Node* Tree::search(const int key, Node* sub_tree)
{
    if (sub_tree == nullptr)
        return nullptr;
    if (key == sub_tree->key)
        return sub_tree;
    Node *result = (key < sub_tree->key) ? search(key, sub_tree->left) : search(key, sub_tree->right);
    return result;
}

Node* Tree::get_parent(const int key, Node* sub_tree)
{
    if (sub_tree == nullptr)
        return nullptr;
    if ((sub_tree->left == nullptr) && (sub_tree->right == nullptr))
        return nullptr;
    if (sub_tree->left != nullptr)
    {
        if (key == sub_tree->left->key)
            return sub_tree;
    }
    if (sub_tree->right != nullptr)
    {
        if (key == sub_tree->right->key)
            return sub_tree;
    }
    Node *result = (key < sub_tree->key) ? search(key, sub_tree->left) : search(key, sub_tree->right);
    return result;

}

std::string Tree::find(const int key)
{
    Node *result = search(key, root);
    if (result == nullptr)
        return "";
    return result->data;
}


Node* Tree::get_max_node_in_sub_tree(Node *root)
{
    while (root->right)
        root = root->right;
    return root;
}

void Tree::remove(Node *target)
{
    if (target == nullptr)
        return;
    if (target->left && target->right)
    {
        Node *localMax = get_max_node_in_sub_tree(target->left);
        target->key = localMax->key;
        target->data = localMax->data;
        remove(localMax);
        return;
    }
    Node *parent = get_parent(target->key, root);
    if (target->left)
    {
        if (target == parent->left)
            parent->left = target->left;
        else
            parent->right = target->left;
        delete target;
        return;
    }
    if (target->right)
    {
        if (target == parent->right)
            parent->right = target->right;
        else
            parent->left = target->right;
        delete target;
        return;
    }
    if (target == parent->left)
        parent->left = nullptr;
    else
        parent->right = nullptr;
}

bool Tree::del(const int key)
{
    Node *result = search(key, root);
    if (result == nullptr)
        return false;
    remove(result);
    return true;
}

int main()
{
    std::cout << "The end." << std::endl;
}
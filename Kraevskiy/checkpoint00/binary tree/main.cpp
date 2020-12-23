#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int key;
    string data;

    Node *left;
    Node *right;

    Node();
    Node(const int key, const string data);
    Node(const int key, const string data, Node *left, Node *right);
};

class Tree
{
private:
    Node* root;
public:

    bool add(const int key, const string data);             // false if key already exists
    void add(const int key, const string data, Node* leaf);
    bool del(const int key);                                // false if no key
    string find(const int key);                             // return "" if no key

    Tree();
    ~Tree();

private:

    bool del_find (Node* iterator, Node* previous, const int key);
    void del_tree(Node* leaf);

    Node* find(int key, Node* leaf);
    Node* find_min(Node* ptr);

};

Node::Node(const int key, const string data)
{
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const string data, Node *left, Node *right)
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
    del_tree(root);
}

Node* Tree::find_min(Node* ptr) //Поиск узла с минимальным ключом в дереве
{
    return ptr->left ? find_min(ptr->left) : ptr;
}

void Tree::del_tree(Node *node)
{
    if(node!=nullptr)
    {
        del_tree(node->left);
        del_tree(node->right);
        delete node;
    }
}

bool Tree::add(const int key, const string data)
{
    if (find(key) != "")
        return false;
    if (root != nullptr)
        add(key, data, root);
    else
        root = new Node(key, data);
    return true;


}

void Tree::add(const int key, const string data, Node *node)
{
    if (key < node->key && node->left != nullptr)
    {
        add(key, data, node->left);
        return;
    }
    if (key < node->key && node->left == nullptr)
    {
        node->left = new Node(key, data);
        return;
    }
    if (key > node->key && node->right != nullptr)
    {
        add(key, data, node->right);
        return;
    }
    if (key > node->key && node->right == nullptr)
    {
        node->right = new Node(key, data);
        return;
    }
}


string Tree::find(const int key)
{
    Node* temp = find(key, root);
    if (temp == nullptr)
        return "";
    return  temp->data;
}

Node* Tree::find(int key, Node* root)
{
    if (root != nullptr)
    {
        if (key == root->key)
            return root;
        if (key < root->key)
            return find(key, root->left);
        return find(key, root->right);
    }
    return nullptr;
}


bool Tree::del_find(Node* iterator, Node* previous, const int key)
{
    while (iterator->key != key)
    {
        if (iterator->key < key)
        {
            if (iterator->right != nullptr)
            {
                previous = iterator;
                iterator = iterator->right;
            } else
                return false;
        }
        if (iterator->key > key)
        {
            if (iterator->left != nullptr)
            {
                previous = iterator;
                iterator = iterator->left;
            } else
                return false;
        }
    }
    return true;
}

bool Tree::del(const int key)
{
    Node *iterator = root;
    Node *prev = nullptr;
    if (iterator == nullptr)
        return false;

    if (!del_find(iterator, prev, key))
    {
        return false;
    }

    Node *left = iterator->left;
    Node *right = iterator->right;

    if (iterator != root && right != nullptr)
    {
        find_min(right)->left = left;
        Node *prevright = prev->right;
        if (prevright->key == iterator->key)
        {
            prev->right = right;
        }
        else
            prev->left = right;
    }
    if (iterator != root && right == nullptr)
    {
        if (prev->left == iterator)
        {
            prev->left = left;
        } //Иначе он был справа
        else prev->right = left;
    }
    if (iterator == root && prev->left == iterator)
    {
        prev->left = left;
    }
    if (iterator == root && prev->left != iterator)
    {
        prev->right = left;
    }

    delete iterator;
    return true;
}



int main() {
    std::cout << "The end." << std::endl;
}
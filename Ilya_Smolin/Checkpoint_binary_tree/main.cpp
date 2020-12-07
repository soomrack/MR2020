#include <iostream>
#include <string>

// Binary search tree


class Node {
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
public:
    Node(const int key, const std::string data);
    Node(const int key, const std::string data, Node *left, Node *right);
    Node();
    ~Node();
};


class Tree {
private:
    Node *root;
    Node* findmin(Node* p) {return p->left ? findmin(p->left) : p;}
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    Node *search (int key);
    Node *searchprev (int key);
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};


Node::Node() {left = nullptr; right = nullptr;}


Tree::Tree() {root = nullptr;}



Node *Tree::search(int key)
{
    Node *iterator = root;
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


Node *Tree::searchprev(int key)
{
    if (root == nullptr)
        return nullptr;

    Node *iterator = root;
    Node *prev = nullptr;
    while (iterator->key != key)
    {
        if (iterator->key < key)
        {
            if (iterator->right != nullptr)
            {
                prev = iterator;
                iterator = iterator->right;
            } else
                return nullptr;
        }
        if (iterator->key > key) {
            if (iterator->left != nullptr)
            {
                prev = iterator;
                iterator = iterator->left;
            } else
                return nullptr;
        }
    }
    return prev;
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



bool Tree::add(const int key, const std::string data)
{
    if (root == nullptr)
    {
        root = new Node(key, data);
        return true;
    }
    Node *iterator = root;
    while (true)
    {
        if (iterator->key < key)
        {
            if (iterator->right == nullptr)
            {
                iterator->right = new Node (key, data);
                return true;
            }
            iterator = iterator->right;
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
        if (iterator->key == key)
            return false;
    }
}


bool Tree::del(const int key)
{
    Node *nodetodelete = search(key);
    if (nodetodelete == nullptr)
        return false;
    Node *prev = searchprev(key);

    Node *nodetodelete_left = nodetodelete->left;
    Node *nodetodelete_right = nodetodelete->right;

    if (nodetodelete == root)
    {
        if (nodetodelete_right != nullptr)
        {
            findmin(nodetodelete_right)->left = nodetodelete_left;
            root = nodetodelete_right;
        }
        else
        {
            root = nodetodelete_left;
        }
        delete nodetodelete;
        return true;
    }
    if (nodetodelete_right != nullptr)
    {
        findmin(nodetodelete_right)->left = nodetodelete_left;
        Node *prevright = prev->right;
        if (prevright->key == nodetodelete->key)
        {
            prev->right = nodetodelete_right;
        }
        else
            prev->left = nodetodelete_right;
    }
    else
    {
        if (prev->left == nodetodelete)
            prev->left = nodetodelete_left;
        else prev->right = nodetodelete_left;
    }
    delete nodetodelete;
    return true;
}


std::string Tree::find(const int key)
{
    Node *element = search(key);
    if (element == nullptr)
        return "";
    return (element->data);
}


Tree::~Tree() {delete root;}



Node::~Node() {delete left; delete right;}


int main()
{
    Tree mytree;
    mytree.add(10, "10");
    mytree.add(19,"19");
    mytree.add(21,"21");
    mytree.add(20,"20");
    mytree.add(15,"15");
    mytree.add(5,"5");
    std::cout<<mytree.find(19)<<std::endl;
    std::cout<<mytree.find(10)<<std::endl;
    std::cout<<mytree.find(15)<<std::endl;
    mytree.del(15);
    std::cout<<mytree.find(15)<<std::endl;
}
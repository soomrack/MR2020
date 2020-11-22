#include <iostream>
#include <string>


class Node {
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
    Node *parent;
public:
    Node(const int key, const std::string data, Node *parent);
    Node(const int key, const std::string data, Node *left, Node *right, Node *parent);
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
    void destroy_tree(Node *leaf);
    void insert(const int key, const std::string data, Node* leaf);
    Node* search(int key, Node* leaf);
    Node* getMaxNode(Node *root);
    void remove(Node *target);
public:
    Tree();
    ~Tree();
};

Node::Node(const int key, const std::string data, Node *parent)
{
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
}

Node::Node(const int key, const std::string data, Node *left, Node *right, Node *parent)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
    this->parent = parent;
}

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    destroy_tree(root);
}

void Tree::destroy_tree(Node *leaf)
{
      if (leaf != nullptr)
      {
          destroy_tree(leaf->left);
          destroy_tree(leaf->right);
          delete leaf;
      }
}

void Tree::insert(const int key, const std::string data)
{
  if (root != nullptr)
      insert(key, data, root);
  else
      root = new Node(key, data, nullptr);
}

void Tree::insert(int key, const std::string data, Node* leaf)
{
    if (key < leaf->key)
        {
            if (leaf->left != nullptr)
                insert(key, data, leaf->left);
            else
                leaf->left = new Node(key, data, leaf);
        }
    else if (key >= leaf->key)
        {
            if (leaf->right != nullptr)
                insert(key, data, leaf->right);
            else
                leaf->right = new Node(key, data, leaf);
        }
}

bool Tree::add(const int key, const std::string data)
{
    if (find(key) != "")
        return false;
    else
    {
        insert(key, data);
        return true;
    }
}

Node* Tree::search(const int key, Node* leaf)
{
    if (leaf != nullptr)
    {
        if (key == leaf->key)
            return leaf;
        if (key < leaf->key)
            return search(key, leaf->left);
        else
            return search(key, leaf->right);
    }
    else
        return nullptr;
}

std::string Tree::find(const int key)
{
    if (search(key, root) == nullptr)
        return "";
    else
        return search(key, root)->data;
}


Node* Tree::getMaxNode(Node *root)
{
    while (root->right)
        root = root->right;
    return root;
}

void Tree::remove(Node *target)
{
    if (target->left && target->right)
    {
        Node *localMax = getMaxNode(target->left);
        target->key = localMax->key;
        target->data = localMax->data;
        remove(localMax);
        return;
    }
    else if (target->left)
    {
        if (target == target->parent->left)
            target->parent->left = target->left;
        else
            target->parent->right = target->left;
    }
    else if (target->right)
    {
        if (target == target->parent->right)
            target->parent->right = target->right;
        else
            target->parent->left = target->right;
    }
    else
    {
        if (target == target->parent->left)
            target->parent->left = nullptr;
        else
            target->parent->right = nullptr;
    }
    delete target;
}

bool Tree::del(const int key)
{
    if (find(key) == "")
        return false;
    else
    {
        remove(search(key, root));
        return true;
    }
}

int main()
{
    std::cout << "The end." << std::endl;
}

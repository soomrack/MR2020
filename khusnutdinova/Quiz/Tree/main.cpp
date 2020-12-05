#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    void* data;
    Node* left_child;
    Node* right_child;

public:
    Node(int key, void* data)
    {
        this->data = data;
        this->key = key;
        left_child = nullptr;
        right_child = nullptr;
    }

    ~Node()
    {
        key = 0;
        data = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }
};

class Tree
{
public:
    Node* root;
    Tree()
    {
        root = nullptr;
    }

public:
    Node* parent_search_for_new_node(int key, Node* root);
    bool add(int key, void* data);
    Node* find(int key, Node* root);
    Node* parent_node_search(int key, Node* root);
    Node* min_left(Node* root);
    bool del(int key);
    void delete_root(void);
    void traverse(Node* root);
};

Node* Tree::parent_search_for_new_node(int key, Node* root)
{
    if (key < root->key)
    {
        if (root->left_child == nullptr) return(root);
        return(parent_search_for_new_node(key, root->left_child));
    }
    else
    {
        if (root->right_child == nullptr) return(root);
        return(parent_search_for_new_node(key, root->right_child));
    }
}

bool Tree::add(int key, void* data)
{
    Node* child = new Node(key, data);
    if (root == nullptr)
    {
        root = child;
        return false;
    }

    Node* parent = parent_search_for_new_node(key, root);

    if (key < parent->key) parent->left_child = child;
    else parent->right_child = child;
    return true;
}

Node* Tree::find(int key, Node* root)
{
    if (root == nullptr) return nullptr;
    if (key == root->key) return root;
    if (key < root->key) find(key, root->left_child);
    else find(key, root->right_child);
}

Node* Tree::parent_node_search(int key, Node* root)
{
    if (root->key == key) return nullptr;
    if (root->left_child != nullptr) if (key == root->left_child->key) return root;
    if (root->right_child != nullptr) if (key == root->right_child->key) return root;

    if (key < root->key) parent_node_search(key, root->left_child);
    else parent_node_search(key, root->right_child);
}

Node* Tree::min_left(Node* root)
{
    Node* find_min = root;
    while (find_min->left_child != nullptr)
    {
        find_min = find_min->left_child;
    }
    return find_min;
}

bool Tree::del(int key)
{

    Node* delete_node = find(key, root);
    if (delete_node == nullptr) return false;

    if ((delete_node->left_child != nullptr) && (delete_node->right_child != nullptr))
    {
        Node* temp = min_left(delete_node->right_child);
        if (temp == delete_node->right_child)
        {
            delete_node->key = temp->key;
            delete_node->data = temp->data;
            delete_node->right_child = temp->right_child;
            delete temp;
            return true;
        }
        else
        {
            delete_node->data = temp->data;
            delete_node->key = temp->key;
            del(temp->key);
            return true;
        }
    }

    Node* parent_delete_node = parent_node_search(key, root);
    if (parent_delete_node == nullptr)
    {
        delete_root();
        return true;
    }

    if ((delete_node->left_child == nullptr) && (delete_node->right_child == nullptr))
    {
        if (parent_delete_node->left_child == delete_node) parent_delete_node->left_child = nullptr;
        else parent_delete_node->right_child = nullptr;
        delete delete_node;
        return true;
    }


    if ((delete_node->left_child != nullptr) && (delete_node->right_child == nullptr))
    {
        if (parent_delete_node->left_child == delete_node) parent_delete_node->left_child = delete_node->left_child;
        else parent_delete_node->right_child = delete_node->left_child;
        delete delete_node;
        return true;
    }

    if ((delete_node->left_child == nullptr) && (delete_node->right_child != nullptr))
    {
        if (parent_delete_node->left_child == delete_node) parent_delete_node->left_child = delete_node->right_child;
        else parent_delete_node->right_child = delete_node->right_child;
        delete delete_node;
        return true;
    }
}

void Tree::delete_root(void)
{
    if ((root->left_child == nullptr) && (root->right_child == nullptr))
    {
        root = nullptr;
        return;
    }

    if ((root->left_child != nullptr) && (root->right_child == nullptr))
    {
        root = root->left_child;
        return;
    }

    if ((root->left_child == nullptr) && (root->right_child != nullptr))
    {
        root = root->right_child;
        return;
    }
}


int main() {

    std::cout << "The end." << std::endl;
}

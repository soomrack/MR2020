#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    std :: string data;
    Node* left;
    Node* right;

public:
    Node(int key, std :: string data);
    ~Node();
};

Node ::Node(int key, std :: string data){
    this->data = data;
    this->key = key;
    left = nullptr;
    right = nullptr;

}

Node ::~Node() {
    key = 0;
    data = nullptr;
    left = nullptr;
    right = nullptr;
}


class Tree
{
private:
    Node* parent_search(int key, Node* root);
    Node* find_element(int key, Node* root);
    Node* min_left(Node* root);
    Node* parent_node_search(int key, Node* root);
    void change_root_if_no_parent(void);
public:
    Node* root;
    Tree();
public:
    bool add(const int key, std :: string data);
    bool del(const int key);
    std :: string find(const int key);
};

Tree ::Tree() {
    root = nullptr;
}

Node* Tree::parent_search(int key, Node* root)
{
    if (root == nullptr)
        return root;
    if (key < root->key)
    {
        if (root->left == nullptr) return(root);
        return(parent_search(key, root->left));
    }
        if (root->right == nullptr) return(root);
        return(parent_search(key, root->right));
}

bool Tree::add(int key, std ::  string data)
{
    Node* child = new Node(key, data);
    if (root == nullptr)
    {
        root = child;
        return false;
    }

    Node* parent = parent_search(key, root);

    if (key < parent->key) parent->left = child;
    else parent->right = child;
    return true;
}

Node* Tree::find_element(int key, Node* root)
{
    if (root == nullptr) return nullptr;
    if (key == root->key) return root;
    if (key < root->key) return find_element(key, root->left);
    return find_element(key, root->right);
}

Node* Tree::parent_node_search(int key, Node* root)
{
    if (root == nullptr)
        return root;
    if (root->key == key) return nullptr;
    if ((root->left!= nullptr) && (key == root->left->key)) return root;
    if ((root->right!= nullptr) && (key == root->right->key)) return root;
    if (key < root->key) return parent_node_search(key, root->left);
    return parent_node_search(key, root->right);
}

Node* Tree::min_left(Node* root)
{
    Node* find_min = root;
    while (find_min->left != nullptr)
    {
        find_min = find_min->left;
    }
    return find_min;
}

bool Tree::del(int key)
{
    Node* delete_node = find_element(key, root);
    if (delete_node == nullptr) return false;

    if ((delete_node->left!= nullptr) && (delete_node->right!= nullptr))
    {
        Node* temp = min_left(delete_node->right);
        if (temp == delete_node->right)
        {
            delete_node->key = temp->key;
            delete_node->data = temp->data;
            delete_node->right = temp->right;
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
        change_root_if_no_parent();
        return true;
    }

    if ((delete_node->left == nullptr) && (delete_node->right == nullptr))
    {
        if (parent_delete_node->left == delete_node) parent_delete_node->left = nullptr;
        else parent_delete_node->right = nullptr;
        delete delete_node;
        return true;
    }


    if ((delete_node->left != nullptr) && (delete_node->right == nullptr))
    {
        if (parent_delete_node->left == delete_node) parent_delete_node->left = delete_node->left;
        else parent_delete_node->right = delete_node->left;
        delete delete_node;
        return true;
    }

    if ((delete_node->left == nullptr) && (delete_node->right != nullptr))
    {
        if (parent_delete_node->left == delete_node) parent_delete_node->left = delete_node->right;
        else parent_delete_node->right = delete_node->right;
        delete delete_node;
        return true;
    }
}

void Tree::change_root_if_no_parent(void)
{
    if ((root->left == nullptr) && (root->right == nullptr))
    {
        root = nullptr;
        return;
    }

    if ((root->left != nullptr) && (root->right == nullptr))
    {
        root = root->left;
        return;
    }

    if ((root->left == nullptr) && (root->right != nullptr))
    {
        root = root->right;
        return;
    }
}

std::string Tree::find(const int key) {
    Node* node = root;
    if (node == nullptr)
        return " ";
    while (node->key != key)
    {
        if (key > node->key)
        {
            if (node->right == nullptr)
                return "";
            node = node->right;
        }
        if (key < node->key)
        {
            if (node->left == nullptr)
                return "";
            node = node->left;
        }
    }
    return node->data;
}

int main() {
    std::cout << "The end." << std::endl;
}
#include <iostream>
#include <string>

using namespace std;
// red-black tree

class Node {
public:
    int key;
    std::string data;
    int8_t color;       // 1 == red
    Node* left;
    Node* right;
    Node* parent;
public:
    Node();
    Node(const int key, const std::string data);
    Node(int key,  std::string data,  Node *left,  Node *right);
    ~Node();
};


class Tree {
private:
    Node* root;
    void rotate_left();
    void rotate_right();
    bool Tree::fix_insert(Node* z_node);
    Node* min_Node(Node* root); 
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

Node::Node() {
    left = nullptr;
    right = nullptr;
    color = 1;
}

Node::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
    color = 1;
}

Node::Node(int key,  std::string data,  Node *left,  Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
    color = 1;
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


bool Tree::add(const int key, const std::string data)
{
    Node* z_node = new Node(key,data);

    Node* y_ptr = nullptr;
    Node* upper_ptr = this->root;

    while (upper_ptr != nullptr)    //looking for a place to attach new node
    {
        y_ptr = upper_ptr;          //saves previuos upper_ptr value (upper_ptr's parent)
        if (z_node->key < upper_ptr->key)
            upper_ptr = upper_ptr->left;
        else upper_ptr = upper_ptr;
    }
    z_node->parent = y_ptr;         //sets .parent to be either nullptr or actual parent
    if (y_ptr == nullptr)
        this->root = z_node;        //updates root for previously empty tree
    else if (z_node->key < y_ptr->key)
        y_ptr->left = z_node;       //actually attach the node
    else y_ptr->right = z_node;

    fix_insert(z_node);             //fix broken conventions
    return true;
}

bool Tree::fix_insert(Node* z_node)
{
    while (z_node->color == 1)
    {
        if (z_node->parent == z_node->parent->parent->left) {
            Node* y_ptr = z_node->parent->parent->right;
            if (y_ptr->color == 1) {
                z_node->parent->color = 0;
                y_ptr->color = 0;
                z_node->parent->parent->color = 1;
                z_node = z_node->parent->parent;
            }
            else if (z_node == z_node->parent->right)
        }
    }

}


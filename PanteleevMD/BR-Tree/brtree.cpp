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
    Node* nil;
    void rotate_left(Node* pivot);
    void rotate_right(Node* pivot);
    bool fix_insert(Node* z_node);
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
    root = this->nil;
    root->parent = this->nil;
}

Tree::~Tree() {
    delete root;
}

void Tree::rotate_left(Node* pivot)
{
    Node* buffer = pivot->right;    //set nuffer
    pivot->right = buffer->left;    //turn buf's left subtree into pivot's right
    if (buffer->left != this->nil)
        buffer->left->parent = pivot;

    buffer->parent = pivot->parent; //relink  
    if (pivot->parent == this->nil)
        this->root = buffer;
    else if (pivot == pivot->parent->left)
        pivot->parent->left = buffer;
    else pivot->parent->right = buffer;
    buffer->left = pivot;
    pivot->parent = buffer;
}

void Tree::rotate_right(Node* pivot)
{
    Node* buffer = pivot->left;    //set nuffer
    pivot->left = buffer->right;    //turn buf's left subtree into pivot's left
    if (buffer->right != this->nil)
        buffer->right->parent = pivot;

    buffer->parent = pivot->parent; //relink  
    if (pivot->parent == this->nil)
        this->root = buffer;
    else if (pivot == pivot->parent->right)
        pivot->parent->right = buffer;
    else pivot->parent->left = buffer;
    buffer->right = pivot;
    pivot->parent = buffer;
}


bool Tree::add(const int key, const std::string data)
{
    Node* z_node = new Node(key,data);

    Node* y_ptr = this->nil;
    Node* upper_ptr = this->root;

    while (upper_ptr != this->nil)    //looking for a place to attach new node
    {
        y_ptr = upper_ptr;          //saves previuos upper_ptr value (upper_ptr's parent)
        if (z_node->key < upper_ptr->key)
            upper_ptr = upper_ptr->left;
        else upper_ptr = upper_ptr;
    }
    z_node->parent = y_ptr;         //sets .parent to be either nullptr or actual parent
    if (y_ptr == this->nil)
        this->root = z_node;        //updates root for previously empty tree
    else if (z_node->key < y_ptr->key)
        y_ptr->left = z_node;       //actually attach the node
    else y_ptr->right = z_node;

    z_node->left = this->nil;
    z_node->right = this->nil;

    fix_insert(z_node);             //fix broken conventions
    return true;
}

bool Tree::fix_insert(Node* z_node)
{
    while (z_node->color == 1)
    {
        if (z_node->parent == z_node->parent->parent->left) {       //if z's parent is letf son
            Node* y_ptr = z_node->parent->parent->right;            //pick right uncle
            if (y_ptr->color == 1) {                                //uncle is RED
                z_node->parent->color = 0;                          //=>  recoloring case
                y_ptr->color = 0;
                z_node->parent->parent->color = 1;
                z_node = z_node->parent->parent;
            }
            else {
                if (z_node == z_node->parent->right) {             //right uncle is BLACK and z is the right son
                    z_node = z_node->parent;                       //=>  left triangle case
                    rotate_left(z_node);
                }

                z_node->parent->color = 0;                         //=>  left line case 
                z_node->parent->parent->color = 1;
                rotate_right(z_node->parent->parent);
            }
        }
        else {                                                      //if z's parent is right son
            Node* y_ptr = z_node->parent->parent->right;            //pick right uncle
            if (y_ptr->color == 1) {                                //uncle is RED
                z_node->parent->color = 0;                          //=>  recoloring case
                y_ptr->color = 0;
                z_node->parent->parent->color = 1;
                z_node = z_node->parent->parent;
            }
            else {
                if (z_node == z_node->parent->right) {             //right uncle is BLACK and z is the left son
                    z_node = z_node->parent;                       //=>  right triangle case
                    rotate_right(z_node);
                }

                z_node->parent->color = 0;                         //=>  right line case 
                z_node->parent->parent->color = 1;
                rotate_left(z_node->parent->parent);
            }
        
        }
    }
    this->root->color = 0;  // make black
}

int main()
{
    Tree test_tree;

    test_tree.add(15,"1");
    test_tree.add(19,"11");
    test_tree.add(21,"111");
    test_tree.add(20,"1111");
    test_tree.add(10,"11-1-11"); 

}
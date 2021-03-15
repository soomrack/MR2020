#include <iostream>
#include <string>

#include <sstream>

//using namespace std;
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
    // for Debug Visualizer ext
    std::string json_viz;
    std::string viz;
    std::string nodes;
    std::string edges;
    void visualize(Node* node);

    void rotate_left(Node* pivot);
    void rotate_right(Node* pivot);
    void fix_insert(Node* pivot);
    void transplant(Node* sbtee_one, Node* sbtree_two);
    void delete_node(Node* node_to_del);
    Node* find_node(Node* search_start, const int key);
    Node* tree_min(Node* start);
    Node* tree_max(Node* start);
    Node* find_node(const int key);
    void construct_nil();
public:
    void add(const int key, const std::string data);  // false если ключ уже создан.
    void del(const int key);  // false если нет ключа.
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
    construct_nil();
    root = this->nil;
}

Tree::~Tree() {
    delete root;
}

void Tree::visualize(Node* node)
{   
    // -exec set print elements 0        <- to debug console
    if (node != this->nil) {
        std::string color = "";
        if (node->color == 1)
            color = "red";
        else color = "black";

        this->nodes += "{\"id\":\"" + std::to_string(node->key) + "\", \"color\": \"" + color + "\"}, ";
        this->edges += "{\"from\":\"" + std::to_string(node->parent->key) + "\",\"to\":\"" + std::to_string(node->key) + "\"}, ";
        visualize(node->left);
        visualize(node->right);
    }
    if (node == this->root)
    {
        std::string nd_lst = this->nodes;
        std::string edg_lst = this->edges;
        nd_lst = nd_lst.substr(0, nd_lst.length()-2);
        edg_lst = edg_lst.substr(0, edg_lst.length()-2);
        this->json_viz = "{\"kind\":{\"graph\":true}, \"nodes\":[" + nd_lst + "],"
        "\"edges\":[" + edg_lst + "]}";

        //this->json_viz.clear();
        this->nodes.clear();
        this->edges.clear();
    }
}
void Tree::construct_nil()      // nil is universal node that replaces nullptr in this implementation
{
    this->nil = new Node();
    this->nil->color = 0;
    this->nil->parent = this->nil;
    this->nil->left = this->nil;
    this->nil->right = this->nil;
}

Node* Tree::tree_min(Node* start)
{
    while (start->left != this->nil)
        start = start->left;
    return start;
}

Node* Tree::tree_max(Node* start)
{
    while (start->right != this->nil)
        start = start->right;
    return start;
}

Node* Tree::find_node(Node* search_start, const int key)
{
    if (search_start == this->nil || key == search_start->key)
        return search_start;
        
    if (key < search_start->key)
        return find_node(search_start->left, key);
    return find_node(search_start->right, key);         //else
}

std::string Tree::find(const int key)
{
    return find_node(this->root, key)->data;
}

void Tree::rotate_left(Node* pivot)
{
    Node* buffer = pivot->right;        //set buffer
    pivot->right = buffer->left;        //turn buf's left subtree into pivot's right
    if (buffer->left != this->nil)
        buffer->left->parent = pivot;
    buffer->parent = pivot->parent;     //relink  parents

    if (pivot->parent == this->nil)
        this->root = buffer;
    else if (pivot == pivot->parent->left)
        pivot->parent->left = buffer;
    else pivot->parent->right = buffer;
    buffer->left = pivot;               //put pivot on the left
    pivot->parent = buffer;
}

void Tree::rotate_right(Node* pivot)
{
    Node* buffer = pivot->left;         //set buffer
    pivot->left = buffer->right;        //turn buf's left subtree into pivot's left
    if (buffer->right != this->nil)
        buffer->right->parent = pivot;

    buffer->parent = pivot->parent;     //relink  
    if (pivot->parent == this->nil)
        this->root = buffer;
    else if (pivot == pivot->parent->right)
        pivot->parent->right = buffer;
    else pivot->parent->left = buffer;
    buffer->right = pivot;
    pivot->parent = buffer;
}
// method to toss subtrees around
void Tree::transplant(Node* sbtree_one, Node* sbtree_two)
{
    if (sbtree_one->parent == this->nil)                    // tree_one is root
        this->root = sbtree_two;
    else if (sbtree_one == sbtree_one->parent->left)        // otherwise it's a either left or right child
        sbtree_one->parent->left = sbtree_two;              // left child
    else sbtree_one->parent->right = sbtree_two;            // right child

    if (sbtree_two != this->nil)
        sbtree_two->parent = sbtree_one->parent;            // exchange parents if not nil
}

void Tree::add(const int key, const std::string data)
{
    Node* new_node = new Node(key,data);

    Node* tailing_ptr = this->nil;
    Node* upper_ptr = this->root;

    while (upper_ptr != this->nil)              //looking for a place to attach new node
    {
        tailing_ptr = upper_ptr;                //saves previuos upper_ptr value (upper_ptr's parent)
        if (new_node->key < upper_ptr->key) 
            upper_ptr = upper_ptr->left; 
        else 
            upper_ptr = upper_ptr->right;
    }
    new_node->parent = tailing_ptr;               //sets .parent to be either nullptr or actual parent
    if (tailing_ptr == this->nil)
        this->root = new_node;                    //updates root for previously empty tree
    else if (new_node->key < tailing_ptr->key)
        tailing_ptr->left = new_node;             //actually attach the node
    else tailing_ptr->right = new_node;

    new_node->left = this->nil;
    new_node->right = this->nil;
    visualize(this->root);
    fix_insert(new_node);                     //fix broken conventions
    visualize(this->root);
}

void Tree::fix_insert(Node* pivot)
{
    while (pivot->parent->color == 1)      // while piv's parent is RED (both parent and z are red => rule broken)
    {
        if (pivot->parent == pivot->parent->parent->left) {       // if piv's parent is left son
            Node* uncle_node = pivot->parent->parent->right;      // pick right uncle
            if (uncle_node->color == 1) {                         // uncle is RED
                pivot->parent->color = 0;                         // =>  recoloring case
                uncle_node->color = 0;
                pivot->parent->parent->color = 1;
                pivot = pivot->parent->parent;
            }
            else {
                if (pivot == pivot->parent->right) {              // right uncle is BLACK and z is the right son
                    pivot = pivot->parent;                        // =>  left triangle case
                    rotate_left(pivot);
                }

                pivot->parent->color = 0;                         // =>  left line case 
                pivot->parent->parent->color = 1;
                rotate_right(pivot->parent->parent);
            }
        }
        else {                                                    // if z's parent is right son
            Node* uncle_node = pivot->parent->parent->left;       // pick left uncle
            if (uncle_node->color == 1) {                         // uncle is RED
                pivot->parent->color = 0;                         // =>  recoloring case
                uncle_node->color = 0;
                pivot->parent->parent->color = 1;
                pivot = pivot->parent->parent;
            }
            else {
                if (pivot == pivot->parent->left) {               // right uncle is BLACK and z is the left son
                    pivot = pivot->parent;                        // =>  right triangle case
                    rotate_right(pivot);
                }

                pivot->parent->color = 0;                         // =>  right line case 
                pivot->parent->parent->color = 1;
                rotate_left(pivot->parent->parent);
            }
        
        }
    }
    this->root->color = 0;  // make black
}



void Tree::delete_node(Node* node_to_del)
{
    if (node_to_del->left == this->nil)                             // node has no left child
        transplant(node_to_del, node_to_del->right);
    else if (node_to_del->right == this->nil)                       // node has left but not right child
        transplant(node_to_del, node_to_del->left);
    else {                                                          // node has both children
        Node* smallest_right = tree_min(node_to_del->right);        // next node numerically - 'successor'
        if (smallest_right->parent != node_to_del) {
            transplant(smallest_right, smallest_right->right);      // successor is now erased from thew right subtree
            smallest_right->right = node_to_del->right;             // reattach the whole right subtree 
            smallest_right->right->parent = smallest_right;         // to the new parent
        }
        transplant(node_to_del, smallest_right);                    // updates node_to_del's parents
        smallest_right->left = node_to_del->left;                   // reattach the whole right subtree 
        smallest_right->left->parent = smallest_right;              // to the new parent
    }
}

void Tree::del(const int key) 
{
    Node* node_to_del = find_node(this->root, key);
    if (node_to_del != this->nil)
        delete_node(node_to_del);
    visualize(this->root);
}

int main()
{
    Tree test_tree;

    test_tree.add(15,"1");
    test_tree.add(19,"11");
    test_tree.add(21,"111");
    test_tree.add(20,"1111");
    test_tree.add(22,"11-1-11"); 
    test_tree.add(25,"11-1-11"); 
    test_tree.add(30,"11-1-11"); 
    test_tree.add(27,"11-1-11"); 
    test_tree.del(25);
    //cout<<'wow';
    return 0;
}
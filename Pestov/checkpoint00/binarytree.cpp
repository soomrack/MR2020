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
    Node();
    Node(const int key, const std::string data);
    // Node(const int key, const std::string data, const Node *left, const Node *right);
    // ~Node();
};


Node::Node(){
    this->key = 0;
    this->data = "";
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

// Node::~Node(){
//     left = nullptr;
//     right = nullptr;
//     this->key = NULL;
//     this->data = "";
// }


class Tree {
private:
    Node *root;
    Node* find_Node(Node* root, int key);
    Node* find_Parent(Node* root, int key);
    Node* min_Node(Node* root);
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
    
};


Tree::Tree(){
    root = nullptr;
}

Tree::~Tree(){
    while(root != nullptr){ del(root->key); }
}

bool Tree::add(const int key, const std::string data){
    if (root == nullptr){
        root = new Node(key, data);
    }
    else {
        Node* child = new Node(key, data);
        Node* parent = find_Node(root, key);
        if (parent->key == key){
            return false;
        }
        if(parent->key > key){
            parent->left = child;
            return true;
        }
       
        parent->right = child;
        return true;
        
    }

}

Node* Tree::find_Node(Node * root, int key){
        if (root->key == key){
            return root;
        }
        else if (root->key < key) {
            if (root->right == nullptr)
                return root;
            return find_Node(root->right, key);
        }
        else {
            if (root->left == nullptr)
                return root;
            return find_Node(root->left, key);
        }
}

std::string Tree::find(const int key){
    if (root == nullptr)
        return "";
    Node* node = find_Node(root, key);
    if (node->key == key){
        return node->data;
    }
    else{
        return "";
    }
}


bool Tree::del(const int key){
    // алгоритм удаления узла из бинарного дерева я нашел туть https://www.youtube.com/watch?v=gcULXE7ViZw&ab_channel=mycodeschool
    if (find(key) == ""){
        return false;
    }
    Node* node = find_Node(root, key);
    Node* parent = find_Parent(root, key);
    // case 1: no child 
    if ((node->left == nullptr) && (node->right == nullptr)){
        if (node == root){
            root = nullptr;
        }
        else if(parent->left == node){
            parent->left = nullptr;
        }
        else{
            parent->right = nullptr;
        }
        delete node;
        return true;
    }
    // case 2: one child
    // case 2.1: right child
    if ((node->left == nullptr)){
        if (node == root){
            root = node->right;
        }
        else if(parent->left == node){
            parent->left = node->right;
        }
        else{
            parent->right = node->right;
        }
        delete node;
        return true;
    }
    // case 2.2: left child
    if ((node->right == nullptr)){
        if (node == root){
            root = node->left;
        }
        else if(parent->left == node){
            parent->left = node->left;
        }
        else{
            parent->right = node->left;
        }
        delete node;
        return true;
    }
    // case 3: 2 children
    // условия не нужны тк я все ост разобрал и вышел из функции
    // Реализация - найти минимальное справ, скопировать значение в удаляемое, удалить то от куда взяли минимальное

    Node* right_child = node->right;
    Node* minNode = min_Node(right_child);
    Node* minParent = find_Parent(root, minNode->key);
    int minkey = minNode->key;
    std::string mindata = minNode->data;
    // минимальная нода всегда имеет один или ноль детей (левых нет)
    del(minNode->key);
    node->key = minkey;
    node->data = mindata;
    return true;
    
}

Node* Tree::find_Parent(Node * root, int key) {
    // Возращает нулевой указатель, если ключа нет или ключ - корень дерева
    if (root->key < key) {
        if (root->right == nullptr)
            return nullptr;
        if (root->right->key == key){
            return root;
        }
        return find_Parent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->key == key){
            return root;
        }
        return find_Parent(root->left, key);
    }
    return nullptr;
}

Node* Tree::min_Node(Node* node){
    if (node->left == nullptr){
        return node;
    }
    else{
        return min_Node(node->left);
    }
}


int main() {
    Tree tree;
    tree.add(12, "HelloWorld!");
    tree.add(5, "Second str");
    tree.add(15, "3 str");
    tree.add(3, "4 str");
    tree.add(1, "5 str");
    tree.add(7, "str");
    tree.add(9, "str");
    tree.add(8, "str");
    tree.add(11, "str");
    tree.add(13, "str");
    tree.add(14, "str");
    tree.add(17, "str");
    tree.add(20, "str");
    tree.add(18, "str");
    
    std::string str = tree.find(11);
    std::cout << str << std::endl;
    str = tree.find(1);
    std::cout << str << std::endl;
    str = tree.find(6);
    std::cout << str << std::endl;

    tree.del(1);
    tree.del(17);
    tree.del(15);
    tree.del(12);

    std::cout << "The end." << std::endl;
    return 0;
}
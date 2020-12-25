#include <iostream>
#include <string>

std::string NO_KEY = "no_key";


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
    // ~Node();
};


Node::Node(){
    this->key = 0;
    this->data = NO_KEY;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data, Node *left, Node *right){
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}


class Tree { //binary key search tree
private:
    Node *root;
    Node* find_Node(Node* root, int key);
    Node* find_Parent(Node* root, int key);
    Node* min_Node(Node* root);
public:
    bool add(const int key, const std::string data);  // false если ключ уже существует
    bool del(const int key);  // false если нет ключа
    std::string find(const int key);  // возвращает 'no_key' если нет ключа
public:
    Tree();
    ~Tree();
    
};


Tree::Tree(){
    root = nullptr;
}

Tree::~Tree(){ while(root != nullptr){ del(root->key); } }

bool Tree::add(const int key, const std::string data){

    if (root == nullptr){   // if tree is empty
        root = new Node(key, data);
        return true;
    }

    Node* child = new Node(key, data);
    Node* parent = find_Node(root, key);

    if (parent->key == key){ 
        return false;
    }
    if (parent->key > key){
        parent->left = child;
        return true;
    }
    
    parent->right = child;
    return true;

}


Node* Tree::find_Node(Node * root, int key){  // find node by key recursively

        if (root->key == key){
            return root;
        }
        else if (root->key < key) {
            return (root->right == nullptr) ? root: find_Node(root->right, key);
        }
        return (root->left == nullptr) ? root:find_Node(root->left, key);

}

std::string Tree::find(const int key){   // returns data by key

    if (root == nullptr){ return NO_KEY; } // if tree is empty

    Node* node = find_Node(root, key);

    if (node->key == key){
        return node->data;
    }
    
    return NO_KEY;

}


bool Tree::del(const int key){
    if (find(key) == NO_KEY){
        return false;
    }
    Node* node = find_Node(root, key);
    Node* parent = find_Parent(root, key);
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
    Node* right_child = node->right;
    Node* minNode = min_Node(right_child);
    Node* minParent = find_Parent(root, minNode->key);
    int minkey = minNode->key;
    std::string mindata = minNode->data;
    del(minNode->key);
    node->key = minkey;
    node->data = mindata;
    return true;
    
}

Node* Tree::find_Parent(Node * root, int key) { // find parent of existing node
    
    if (root->key < key) {  // parent is to the right from root
        if (root->right == nullptr)
            return nullptr; // no parent
        if (root->right->key == key){
            return root;   
        }
        return find_Parent(root->right, key); // finding parent in the right side recursively
    }
    // same for left side
    if (root->key > key) {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->key == key){
            return root;
        }
        return find_Parent(root->left, key);
    }
    return nullptr; // function has got key of root or tree is empty

}

Node* Tree::min_Node(Node* node){ // find node with the least key
    
    if (node->left == nullptr){ 
        return node;
    }
    return min_Node(node->left);

}


int main() {
    Tree tree;
    
    //Потестим
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
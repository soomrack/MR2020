#include <iostream>
#include <string>


class Node {
public:
        int key;
        std:: string data;
public:
        Node *left;
        Node *right;
public:
        Node();
        Node(int key, std::string data);
        Node(int key, std::string data, Node* left, Node* right);
        ~Node();
};

Node::Node() {
    left = nullptr;
    right = nullptr;
}

Node::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
}

 Node::Node( int key, std::string data, Node* left, Node* right){
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
    }

 Node::~Node(){
    delete left;
    delete right;
 }


class Tree {
private:
   Node *root;
   Node* findNode(Node* root, int key);
   Node* findparent(Node* root, int key);
   Node* Min(Node* root);
public:
   bool add(const int key, std:: string data);
   bool del(const int key);
   std::string find(const int key);
public:
   Tree();
   ~Tree();
};

 Node* Tree::findNode(Node* root, int key)
 {
     if (root == nullptr) return root;
     if (root->key == key) return root;
     if (root->key > key) return findNode(root->left, key);
     else return findNode(root->right, key);
 }

 Node* Tree::findparent(Node* root, int key) {
     if (root->key <= key) {
         if (root->right == nullptr)
             return root;
         return findparent(root->right, key);
     }
     if (root->key > key) {
         if (root->left == nullptr)
             return root;
         return findparent(root->left, key);
     }
     return nullptr;
 }

 Node* Tree::Min(Node* root) {
     Node* min = root;
     while (min->left != nullptr) {
         min = min->right;
     }
     return min;
 }

 bool Tree::add(const int key, std::string data) {
     Node* child = new Node(key, data);
     if (findNode(root, key) != nullptr)
         return false;

     Node* parent = findparent(root, key);
     if (key <= parent->key)
         parent->left = child;
     else
         parent->right = child;
     return true;
 };

 bool Tree::del(const int key) {
     Node* del_node = findNode(root, key);
     Node* par_of_del_node = findparent(root, key);
     if (del_node == nullptr)
         return false;
     if (del_node->left == nullptr && del_node->right == nullptr)
     {
         if (par_of_del_node->left == del_node)
         {
             par_of_del_node->left = nullptr;
             delete del_node;
             return true;
         }
         par_of_del_node->right = nullptr;
         delete del_node;
         return true;
     }
     if (del_node->left == nullptr && del_node->right != nullptr)
     {
         if (par_of_del_node->left == del_node)
         {
             par_of_del_node->left = del_node->right;
             delete del_node;
             return true;
         }
         par_of_del_node->right = del_node->right;
         delete del_node;
         return true;
     }
     if (del_node->left != nullptr && del_node->right == nullptr)
     {
         if (par_of_del_node->left == del_node)
         {
             par_of_del_node->left = del_node->left;
             delete del_node;
             return true;
         }
         par_of_del_node->right = del_node->left;
         delete del_node;
         return true;
     }
     if ((del_node->left != nullptr) && (del_node->right != nullptr))
     {
         Node* temp = Min(del_node->right);
         if (temp == del_node->right)
         {
             del_node->key = temp->key;
             del_node->data = temp->data;
             del_node->right = temp->right;
             delete temp;
             return true;
         }
         del_node->data = temp->data;
         del_node->key = temp->key;
         del(temp->key);
         return true;
     }
     return true;
 }

 std::string Tree::find(const int key) {
     Node* temp = root;
     temp = findNode(temp, key);
     if (temp == nullptr)
         return "";
     return temp->data;
 }

 Tree::Tree() {
     root = nullptr;
 }

 Tree::~Tree() {
     delete root;
 }

int main() {
    Tree tree;
    tree.add(13, "HelloWorld!");
    tree.add(46, "Second str");
    tree.add(4, "5 str");
    tree.add(67, "87 str");
    tree.add(2, "1 str");
    tree.add(9, "str");
    tree.add(12, "str");
    tree.add(3, "str");
    tree.add(17, "str");
    tree.add(18, "str");
    tree.add(21, "str");
    tree.add(20, "str");
    tree.add(22, "str");
    tree.add(19, "str");

    std::string str = tree.find(17);
    std::cout << str << std::endl;
    str = tree.find(19);
    std::cout << str << std::endl;
    str = tree.find(14);
    std::cout << str << std::endl;

    tree.del(19);
    tree.del(17);
    tree.del(13);

    std::cout << "The end." << std::endl;
}
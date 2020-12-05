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
        Node(const int key, const std :: string data);
        ~Node();
};

 Node::Node( int key, const std::string data){
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    }

 Node::~Node(){
    left = nullptr;
    right = nullptr;
    this->key = NULL;
    this->data = "";
 }


class Tree {
private:
   Node *root;
   Node* findNode(Node* root, int key)
   {
       if (root == nullptr) return root;
       if (root->key == key) return root;
       else if (root->key > key) return findNode(root->left, key);
       else return findNode(root->right, key);
   }

   Node* findparent_add  (Node * root, int key) {
       if (root->key <= key) {
           if (root->right == nullptr)
               return root;
           return findparent_add(root->right, key);
       }
       if (root->key > key) {
           if (root->left == nullptr)
               return root;
           return findparent_add(root->left, key);
       }
       return nullptr;
   }

   Node* findparent_del(Node* root, int key){
       if (root->right->key == key) return root;
       if (root->left->key == key) return root;
       if (root->key<=key) return findparent_del(root->right,key);
       return findparent_del(root->left,key);
   };

   Node* min(Node* root)
   {
       if (root->left == nullptr)
           return root;
       else
           return min(root->left);
   }
   public:
   bool add(const int key, std:: string data) {
       Node* child = new Node (key,data);
       if (findNode(root,key)!= nullptr)
           return false;
       if (root == nullptr){
           root = child;
           return true;
       }
       Node* parent = findparent_add(root, key);
       if (key <= parent->key)
           parent->left = child;
       else
           parent->right = child;
       return true;
   };


   bool del(const int key){
       Node* del_node = findNode(root,key);
       Node* par_of_del_node = findparent_del(root, key);
       if (del_node == nullptr)
           return false;
       if (del_node->left == nullptr && del_node->right == nullptr)
       {
           if (par_of_del_node ->left == del_node)
           {
               par_of_del_node ->left = nullptr;
           }
           else
           {
               par_of_del_node->right = nullptr;
           }
           return true;
       }
       if (del_node->left == nullptr && del_node->right != nullptr)
       {
           if (par_of_del_node->left == del_node)
           {
               par_of_del_node->left = del_node->right;
           }
           else
           {
               par_of_del_node->right = del_node->right;
           }
           return true;
       }
       if (del_node->left != nullptr && del_node->right == nullptr)
       {
           if (par_of_del_node->left == del_node)
           {
               par_of_del_node->left = del_node->left;
           }
           else
           {
               par_of_del_node->right = del_node->left;
           }
           return true;
       }
       if ((del_node->left != nullptr) && (del_node->right != nullptr))
       {
           Node* temp = min(del_node->right);
           if (temp == del_node->right)
           {
               del_node->key = temp->key;
               del_node->data = temp->data;
               del_node->right = temp->right;
               delete temp;
           }
           else
           {
               del_node->data = temp->data;
               del_node->key = temp->key;
               del(temp->key);
           }
           return true;
       }
   };

   std::string find(const int key) {
       Node* node = root;
       if (node == nullptr)
           return "2";
       while (node->key != key)
       {
           if (key > node->key)
           {
               if (node->right == nullptr) return " ";
               else node = node->right;
           }
           else if (key < node->key)
           {
               if (node->left == nullptr) return " ";
               else node = node->left;
           }
       }
       return node->data;
   };

public:
        Tree(){
            root = nullptr;
        };
        ~Tree(){
            while(root != nullptr){ del(root->key); 
        }
};

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
    return 0;
}
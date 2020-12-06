#include <iostream>
#include <string>

// Binary search tree

class Node {
public:
    int key;
    std:: string data;
public:
    Node *left;
    Node *right;
public:
    Node();
    Node(int key, std :: string data);
    Node(int key, std :: string data, Node *left, Node *right);
    ~Node();
};


class Tree {
private:
    Node *root;
    Node *lookForNode(Node* root, int key);
    Node* findParent (Node * root, int key);
    Node* findMin(Node* root);
public:
    bool add(const int key, std:: string data);  // false if key already exists
    bool del(const int key);
    std::string find(const int key);  // return '' if no key
public:
    Tree();
};

Node:: Node() {
    left = nullptr;
    right = nullptr;
}

Node ::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
}

Node::Node( int key,  std::string data,  Node *left,  Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

Node ::~Node() {
    delete left;
    delete right;
}

Tree::Tree() {
    root = nullptr;
}


std::string Tree::find(const int key){
    Node* node = root;
    if (node == nullptr)
        return " ";
    while (node->key != key)
    {
        if (key > node->key)
        {
            if (node->right == nullptr)
                return " ";
            node = node->right;
        }
        if (key < node->key)
        {
            if (node->left == nullptr)
                return " ";
            node = node->left;
        }
    }
    return node->data;
}

Node* Tree:: lookForNode(Node *root, int key) {
    if (root == nullptr) return root;
    if (root->key == key) return root;
    else if (root->key > key) return lookForNode(root->left, key);
    return lookForNode(root->right, key);
}

Node* Tree :: findParent(Node *root, int key){
    if (root->key <= key) {
        if (root->right == nullptr)
            return root;
        return findParent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        return findParent(root->left, key);
    }
    return nullptr;
}

Node* Tree :: findMin (Node *root) {
    Node *min = root;
    while (min->left != nullptr){
        min = min->right;
    }
    return min;
}

bool Tree ::add(const int key, std::string data) {
    Node* child = new Node (key,data);
    if (lookForNode(root,key)!= nullptr)
        return false;
    if (root == nullptr){
        root = child;
        return true;
    }
    Node* parent = findParent(root, key);
    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;
    return true;
}

bool Tree::del(const int key){
    Node* deletedNode = lookForNode(root,key);
    Node* parentOfDeletedNode = findParent(root, key);
    if (deletedNode == nullptr)
        return false;
    if (deletedNode->left == nullptr && deletedNode->right == nullptr)
    {
        if (parentOfDeletedNode ->left == deletedNode)
        {
            parentOfDeletedNode ->left = nullptr;
            delete deletedNode;
            return true;
        }
        parentOfDeletedNode->right = nullptr;
        delete deletedNode;
        return true;
    }
    if (deletedNode->left == nullptr && deletedNode->right != nullptr)
    {
        if (parentOfDeletedNode->left == deletedNode)
        {
            parentOfDeletedNode->left = deletedNode->right;
            delete deletedNode;
            return true;
        }
        parentOfDeletedNode->right = deletedNode->right;
        delete deletedNode;
        return true;
    }
    if (deletedNode->left != nullptr && deletedNode->right == nullptr)
    {
        if (parentOfDeletedNode->left == deletedNode)
        {
            parentOfDeletedNode->left = deletedNode->left;
            delete deletedNode;
            return true;
        }
        parentOfDeletedNode->right = deletedNode->left;
        delete deletedNode;
        return true;

    }
    if ((deletedNode->left != nullptr) && (deletedNode->right != nullptr)) // у удаляемого узла два ребенка
    {
        Node* temp = findMin(deletedNode->right);
        if (temp == deletedNode->right)
        {
            deletedNode->key = temp->key;
            deletedNode->data = temp->data;
            deletedNode->right = temp->right;
            delete temp;
            return true;
        }
        deletedNode->data = temp->data;
        deletedNode->key = temp->key;
        del(temp->key);
        return true;
    }
}; // false if no key


int main() {
    Tree testTree;
    testTree.add(33, "3");
    testTree.add(31,"5");
    testTree.add(150,"/");
    testTree.add(6,"2");
    testTree.add (7,"3");
    testTree.add(44,"6");
    testTree.add(123,"/");
    testTree.add(5,"1");
    testTree.add (89,"10");
    std::cout<<testTree.find(33)<<std::endl;
    std::cout<<testTree.find(0)<<std::endl;
    std::cout<<testTree.find(8)<<std::endl;
    std::cout<<testTree.find(6)<<std::endl;
    std::cout<<testTree.find(89)<<std::endl;
    std::cout<<testTree.find(5)<<std::endl;
    std::cout<<testTree.find(44)<<std::endl;
    std::cout<<testTree.find(7)<<std::endl;
    testTree.del(31);
    testTree.del(89);
    testTree.del(5);
    std::cout<<testTree.find(31)<<std::endl;
    std::cout<<testTree.find(123)<<std::endl;
    std::cout<<testTree.find(5)<<std::endl;
    std::cout << "The end." << std::endl;
}

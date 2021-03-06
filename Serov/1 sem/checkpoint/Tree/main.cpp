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
    Node(int key, std::string data);
    Node(int key, std::string data, Node *left, Node *right);
    ~Node();
};


class Tree {
private:
    Node *root;
    Node *getNode(Node* root, int key);
    Node* getParent (Node * root, int key);
    Node* getMin(Node* root);
public:
    bool add(const int key, std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
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

Node::Node(int key,  std::string data,  Node *left,  Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
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

Node* Tree::getNode(Node *root, int key) {
    if (root == nullptr) return root;
    if (root->key == key) return root;
    if (root->key > key) return getNode(root->left, key);
    return getNode(root->right, key);
}

Node* Tree::getParent(Node *root, int key){
    if (root->key < key) {
        if (root->right == nullptr)
            return root;
        if (root->right->key == key)
            return root;
        return getParent(root->right, key);
    }

    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        if (root->left->key == key)
            return root;
        return getParent(root->left, key);
    }
    return nullptr;
}

Node* Tree::getMin (Node *root) {
    Node *min = root;
    while (min->left != nullptr){
        min = min->left;
    }
    return min;
}

std::string Tree::find(const int key){
    Node* temp = root;
    temp = getNode(temp,key);
    if (temp == nullptr)
        return "";
    return temp->data;
}

bool Tree::add(const int key, std::string data) {
    Node* child = new Node (key,data);
    if (getNode(root,key)!= nullptr)
        return false;

    if (root == nullptr){
        root = child;
        return true;
    }

    Node* parent = getParent(root, key);
    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;
    return true;
}

bool Tree::del(const int key){
    Node* deletedNode = getNode(root,key);
    Node* parentOfDeletedNode = getParent(root, key);
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

    if ((deletedNode->left != nullptr) && (deletedNode->right != nullptr))
    {
        Node* temp = getMin(deletedNode->right);
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
    return true;
}


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
    testTree.del(6);
    testTree.del(7);
    std::cout<<testTree.find(89)<<std::endl;
    std::cout<<testTree.find(6)<<std::endl;
    std::cout<<testTree.find(33)<<std::endl;
    std::cout<<testTree.find(123)<<std::endl;
    std::cout<<testTree.find(5)<<std::endl;
    std::cout << "The end." << std::endl;
}

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
    Node(int key,  std::string data);      //had to remove const
    Node(int key,  std::string data,  Node *left,  Node *right);
    ~Node();
};


class Tree 
{
public:
    bool add(const int key,  std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find( int key);  // return '' if no key
public:
    Tree();
    ~Tree();
private:
    Node* root;
    Node* findMin(Node* p);
    Node* findMax(Node* p);
};


Node::Node() 
{
    left = nullptr; 
    right = nullptr;
}
Node::Node( int key,  std::string data) 
{
    left = nullptr; 
    right = nullptr;
    this->key = key; 
    this->data = data;
}
Node::Node( int key,  std::string data,  Node *left,  Node *right) 
{
    this->key = key; 
    this->data = data;
    this->left = left; 
    this->right = right;
}
Node::~Node() 
{
    delete left; 
    delete right;
}

Tree::Tree()
{
    root = nullptr;
}

Node* Tree::findMin(Node* p) 
{
    return p->left ? findMin(p->left) : p;      
}

Node* Tree::findMax(Node* p) 
{
    return p->right ? findMax(p->right) : p;      
}

Tree::~Tree() 
{   
    delete root;        //will recursively destroy the tree
}

bool Tree::add(const int key, std::string data)       
{
    Node *activeNode = root;

    if (root == nullptr) {      //tree is empty
        root = new Node;
        root->key = key;
        root->data = data;
        return true;
    }

    while (true)     //iterate until the key is found or the Node added
    {
        if (key > activeNode->key) 
        {
            if (activeNode->right == nullptr)           //if nothing is there
            {                                           
                Node *newNode = new Node(key, data);
                activeNode->right = newNode;            //attach new node
                return true;
            } 
            activeNode = activeNode->right;
        } 
        else if (key < activeNode->key) 
        {
            if (activeNode->left == nullptr) 
            {
                Node *newNode = new Node(key, data);
                activeNode->left = newNode;  
                return true;
            } 
            activeNode = activeNode->left;
        } 
        else if (activeNode->key == key)            //duplicate was found
            return false;
    }
}

bool Tree::del(const int key)       
{
    Node *nodeToDelete = root;
    Node *previousNode = nullptr;

    if (nodeToDelete == nullptr)
        return false;

    while (nodeToDelete->key != key) //leaves iteration when the key is found
    {
        if (key > nodeToDelete->key) 
        {
            if (nodeToDelete->right == nullptr) return false;
            previousNode = nodeToDelete;
            nodeToDelete = nodeToDelete->right;

        }
        if (key < nodeToDelete->key) 
        {
            if (nodeToDelete->left == nullptr) return false;
            previousNode = nodeToDelete;
            nodeToDelete = nodeToDelete->left;
            
        }
    }  //proper key has been found

    Node *leftChild = nodeToDelete->left;     
    Node *rightChild = nodeToDelete->right;  

    if (rightChild != nullptr) 
    { 
        findMin(rightChild)->left = leftChild; //retrieve the smallest node from the right branch

        if (nodeToDelete==root){ //root is being deleted      
            delete nodeToDelete;
            root = rightChild; //the root is dead long live the root (rightChild)
            return true; }   

        Node *prevRight = previousNode->right;
        if (prevRight->key == nodeToDelete->key) 
        {
            previousNode->right = rightChild;       //swap right
        }
        else previousNode->left = rightChild; 
    }
    else 
    { 
        if (nodeToDelete==root){ //root is being deleted
            delete nodeToDelete;
            root = leftChild; //the root is dead long live the root (leftChild)
            return true; }   

        if (previousNode->left == nodeToDelete)  
        {
            previousNode->left = leftChild;     //swap left
        }
        else previousNode->right = leftChild;
    }
    
    delete nodeToDelete;
    return true;
}

std::string Tree::find(const int key) {
    Node *activeNode = root;
    std::string errMsg = "";

    if (activeNode == nullptr)
        return errMsg;

    while (activeNode->key != key) 
    {
        if (key > activeNode->key) 
        {
            if (activeNode->right == nullptr) return errMsg;   
            activeNode = activeNode->right;
        } 
        else if (key < activeNode->key) 
        {
            if (activeNode->left == nullptr) return errMsg;
            activeNode = activeNode->left;
        }
    }
    return activeNode->data;
}

int main() {
    Tree testTree;
    testTree.add(15, "1");
    testTree.add(19,"11");
    testTree.add(21,"111");
    testTree.add(20,"1111");
    testTree.add(10,"11-1-11"); 
    //testTree.add(15,"15");
    std::cout<<testTree.find(19)<<std::endl;
    std::cout<<testTree.find(10)<<std::endl;
    std::cout<<testTree.find(15)<<std::endl;
    testTree.del(15);
    std::cout<<testTree.find(15)<<std::endl;
    std::cout << "The end." << std::endl;

    return 0;
}
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


class Tree {
private:
    Node *root;
    Node* findMin(Node* p) 
    {
        return p->left ? findMin(p->left) : p;      //ternary recursive magic
    }
    Node* findMax(Node* p) 
    {
        return p->right ? findMax(p->right) : p;      
    }
public:
    bool add(int key,  std::string data);  // false if key already exists
    bool del(int key);  // false if no key
    std::string find( int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() 
{
    left = nullptr; 
    right = nullptr;
}
Node::Node( int key,  std::string data) 
{
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
    //delete data;
    //delete key;
}

Tree::Tree()
{
    root = nullptr;
}
Tree::~Tree() 
{   /*      It won't work
    Node* eraser = findMin(findMax(root));
    while(eraser != nullptr)        //slow as f*ck
    {
        del(eraser->key);
        //eraser->~Node();
        eraser = findMin(findMax(root));
    }*/
}


bool Tree::add(int key, std::string data)       //could have been recursive
{
    //std::cout<< "Add initiated" << '\n';
    Node *activeNode = root;

    if (root == nullptr) {      //tree is empty
        root = new Node;
        root->key = key;
        root->data = data;
        return true;
    }

    while (true)     //iterate until key is found or element added
    {
        if (key > activeNode->key) 
        {
            if (activeNode->right == nullptr) 
            {                                           //if nothing is there
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
        else if (activeNode->key == key)            //duplicate is found
            return false;
    }
}

bool Tree::del(const int key)       //could have been recursive
{
    Node *activeNode = root;
    Node *previousNode = nullptr;
    //std::cout<< "Del initiated" << '\n';
    if (activeNode == nullptr)
        return false;
    
    while (activeNode->key != key) //leaves itearation when the key is found
    {
        if (key > activeNode->key) 
        {
            if (activeNode->right != nullptr) 
            {
                previousNode = activeNode;
                activeNode = activeNode->right;
            } 
            else return false;
        }
        if (key < activeNode->key) 
        {
            if (activeNode->left != nullptr) 
            {
                previousNode = activeNode;
                activeNode = activeNode->left;
            } 
            else return false;
        }
    }  //at this point proper key has been found

    Node *leftChild = activeNode->left;     
    Node *rightChild = activeNode->right;  

    if (activeNode==root) //root is being deleted
    {   
        if (rightChild != nullptr) //right child is present
        { 
            findMin(rightChild)->left = leftChild; //retrieve the smallest node from right subbranch
            root = rightChild;                  //the root is dead long live the root (rightChild)
            return true;
        } 
        else //there is left branch only
        { 
            root = leftChild;
            return true;
        }
    }

    if (rightChild != nullptr) 
    { 
        findMin(rightChild)->left = leftChild; //retrieve the smallest node from right subbranch
        Node *prevRight = previousNode->right;

        if (prevRight->key == activeNode->key) 
        {
            previousNode->right = rightChild;
        }
        else previousNode->left = rightChild; 
    }
    else 
    { 
        if (previousNode->left == activeNode)  previousNode->left = leftChild;
        else previousNode->right = leftChild;
    }
    
    delete activeNode;
    return true;
}

std::string Tree::find(const int key) {
    Node *activeNode = root;
    std::string errMsg = " ";

    if (activeNode == nullptr)
        return errMsg;

    while (activeNode->key != key) 
    {
        if (key > activeNode->key) 
        {
            if (activeNode->right == nullptr) return errMsg;   
            else activeNode = activeNode->right;
        } 
        else if (key < activeNode->key) 
        {
            if (activeNode->left == nullptr) return errMsg;
            else activeNode = activeNode->left;
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
    std::cout<<testTree.find(20)<<std::endl;
    std::cout << "The end." << std::endl;

    return 0;
}
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
    Node* findmin(Node* p) 
    {
        return p->left?findmin(p->left):p;      //ternary shit
    }
    Node* findmax(Node* p) 
    {
        return p->right?findmin(p->right):p;      //magic shit
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
{
    Node* eraser = findmin(findmax(root));
    while(eraser != nullptr)        //slow as f*ck
    {
        del(eraser->key);
        //eraser->~Node();
        eraser = findmin(findmax(root));
    }
}


bool Tree::add(int key, std::string data)       //could have been recursive
{
    std::cout<< "Add initiated" << '\n';
    Node *activeNode = root;
    if (root == nullptr) {
        root = new Node;
        root->key = key;
        root->data = data;
    }
    else{
        while (activeNode->key != key)     //iterate until key is found
        {
            if (key > activeNode->key) 
            {
                if (activeNode->right == nullptr) 
                {                                           //if nothing is there
                    Node *newNode = new Node(key, data);
                    activeNode->right = newNode;            //attach new node
                    return true;
                } 
                else activeNode = activeNode->right;
            } 
            else if (key < activeNode->key) 
            {
                if (activeNode->left == nullptr) 
                {
                    Node *newNode = new Node(key, data);
                    activeNode->left = newNode;  
                    return true;
                } 
                else activeNode = activeNode->left;
            } 
            else if (activeNode->key == key)
                return false;
        }
    }
    return false;
}

bool Tree::del(const int key)       //could have been recursive
{
    Node *activeNode = root;
    Node *prev = nullptr;
    std::cout<< "Del initiated" << '\n';
    if (activeNode == nullptr)
        return false;
    else {
        while (activeNode->key != key) 
        {
            if (key > activeNode->key) 
            {
                if (activeNode->right != nullptr) 
                {
                    prev = activeNode;
                    activeNode = activeNode->right;
                } else return false;
            }
            if (key < activeNode->key) 
            {
                if (activeNode->left != nullptr) 
                {
                    prev = activeNode;
                    activeNode = activeNode->left;
                } else return false;
            }
        }  //at this point proper key has been found
    }
    std::cout<<"Erased data: " << activeNode->data << std::endl;

    Node *leftChild = activeNode->left;     //q
    Node *rightChild = activeNode->right;       //r

    if (activeNode!=root) 
    { 
        if (rightChild != nullptr) 
        { 
            findmin(rightChild)->left = leftChild; 
            Node *prevRight = prev->right;
            if (prevRight->key == activeNode->key) 
            {
                prev->right = rightChild;
            }
            else
                prev->left = rightChild; 
        }
        else 
        { 
            if (prev->left == activeNode)  prev->left = leftChild;
            else prev->right = leftChild;
        }
    }
    else
    {   //root is being deleted
        if (rightChild != nullptr) 
        { 
            findmin(rightChild)->left = leftChild; //retrieve the smallest right node
            root = rightChild; //Корнем становится правый элемент от от корня
        } 
        else //there is left branch only
        { 
            root = leftChild;
        }
    }
    delete activeNode;
    return true;
}

std::string Tree::find(const int key) {
    Node *activeNode = root;
    std::string errMsg = "These are not the droids you are looking for";
    if (activeNode == nullptr)
        return errMsg;
    else 
    {
        while (activeNode->key != key) 
        {
            if (key > activeNode->key) 
            {
                if (activeNode->right == nullptr) return errMsg;   
                else  activeNode = activeNode->right;
            } 
            else if (key < activeNode->key) 
            {
                if (activeNode->left == nullptr) return errMsg;
                else activeNode = activeNode->left;
            }
        }
        return "Retrieved data: " + (activeNode->data);
    }
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

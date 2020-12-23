#include <iostream>
#include <string>
using namespace std;

// Binary search tree


class Node {
public:
    int key;
    string data;
public:
    Node *left;
    Node *right;
public:
    Node();
    Node(const int key, const string data);
    Node(const int key, const string data, Node *left, Node *right);
    ~Node();
};


class Tree {
private:
    Node *root;
    Node *getMin(Node* min);
public:
    bool add(const int key, const string data);  // false if key already exists
    bool del(const int key);  // false if no key
    string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() 
{
    key = 0;
    data ="";
    left = nullptr; 
    right = nullptr;
}

Node::Node(const int key, const string data) 
{
    left = nullptr; 
    right = nullptr;
    this->key = key; 
    this->data = data;
}

Node::Node(const int key, const string data, Node *left, Node *right) 
{
    this->key = key; 
    this->data = data;
    this->left = left; 
    this->right = right;
}

Node::~Node() 
{

}

Tree::Tree()
{
    root = nullptr;
}

bool Tree::add(const int key, const string data){
    if (root == nullptr){
        root = new Node(key, data);
        return true;
    }
    Node *nowNode = root;
    while (true)
    {
        if (key == nowNode->key){
            return false;
        }
        if (key > nowNode->key) 
        {
            if (nowNode->right == nullptr)
            {                                           
                Node *newNode = new Node(key, data);
                nowNode->right = newNode;
                return true;
            } 
            nowNode = nowNode->right;
        } 
        else if (key < nowNode->key) 
        {
            if (nowNode->left == nullptr) 
            {
                Node *newNode = new Node(key, data);
                nowNode->left = newNode;  
                return true;
            } 
            nowNode = nowNode->left;
        } 
    }
}

Node* Tree::getMin(Node* min){
    if (min->left != nullptr){
        getMin(min->left);
    }
    else{
        return min;
    }
}

bool Tree::del(const int key)       
{
    Node *nowNode = root;
    Node *precNode = nullptr;

    if (nowNode == nullptr)
        return false;
       while (key != nowNode->key)
    {
        if (key > nowNode->key) 
        {
            if (nowNode->right == nullptr){
                return false;  //doesn't exist
            }
            precNode = nowNode;
            nowNode = nowNode->right;
        }
        if (key < nowNode->key) 
        {
            if (nowNode->left == nullptr){
                return false;
            }
            precNode = nowNode;
            nowNode = nowNode->left;
        }
    } 

    Node *leftScion = nowNode->left;     
    Node *rightScion = nowNode->right;  

    if (rightScion != nullptr) 
    { 
        if (nowNode==root){     
            delete nowNode;
            root = rightScion;
            return true; 
        } 
        else {
            precNode->right = rightScion;
            getMin(rightScion)->left = leftScion;
        }  
        Node *prevRight = precNode->right;
        if (prevRight->key == nowNode->key) 
        {
            precNode->right = rightScion;
        }
        else precNode->left = rightScion; 
    }
    else 
    { 
        if (nowNode==root){
            delete nowNode;
            root = leftScion;
            return true; }   

        if (precNode->left == nowNode)  
        {
            precNode->left = leftScion;
        }
        else precNode->right = leftScion;
    }
    delete nowNode;
    return true;
}

string Tree::find(const int key){
    Node *nowNode = root;
    string noKey = "";
    if (nowNode == nullptr){
        return noKey;
    }
    while (nowNode->key != key){
        if (nowNode->key < key) 
        {
            if (nowNode->right == nullptr){
                return noKey;
            }   
            nowNode = nowNode->right;
        } 
        else if (nowNode->key > key) 
        {
            if (nowNode->left == nullptr){
                return noKey;
            }
            nowNode = nowNode->left;
        }
    }
    return nowNode->data;
}

Tree::~Tree() 
{   
    
}

int main() {
    Tree test;
    test.add(15, "d15");
    test.add(9, "d9");
    test.add(23, "d23");
    test.add(20, "d20");
    test.add(25, "d25");
    test.add(10, "d10");
    test.add(7, "d7");
    test.add(6, "d6");
    test.add(8, "d8");
    cout<<test.find(9)<<endl;
    cout<<test.find(20)<<endl;
    cout<<test.find(6)<<endl;
    cout<<test.find(15)<<"\n\n\n"<<endl;
    test.del(6);
    cout<<"deleted 6"<<endl;
    cout<<test.find(6)<<"\n\n\n"<<endl;
    test.del(15);
    cout<<"deleted 15 root"<<endl;
    cout<<test.find(15)<<endl;
    cout << "The end." << endl;
    return 0;
}
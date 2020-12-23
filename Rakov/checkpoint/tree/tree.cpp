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
public:
    bool add(const int key, const string data);  // false if key already exists
    bool del(const int key);  // false if no key
    string find(const int key);  // return '' if no key
    Node *getMin(Node *currentMin);
public:
    Tree();
    ~Tree();
};

Node::Node(){

    this->key = NULL;
    this->data = "";
    this->left = nullptr;
    this->right = nullptr;

}

Node::Node(const int key, const string data){

    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;

}

Node::Node(const int key, const string data, Node *left, Node *right){

    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;

}

Node::~Node(){

}

Tree::Tree(){

    root = nullptr;

}

Tree::~Tree(){

    

}

bool Tree::add(const int key, const string data){

    if (root == nullptr){

        root = new Node(key, data);
        return true;

    }

    Node *currentNode = root;

    while (1){

        if (key == currentNode->key){          
            
            return false;

        }    

        if (key > currentNode->key){

            if (currentNode->right == nullptr){         

                Node *newNode = new Node(key, data);
                currentNode->right = newNode;       
                return true;

            } 

            currentNode = currentNode->right;

        } else if (key < currentNode->key){

            if (currentNode->left == nullptr){

                Node *newNode = new Node(key, data);
                currentNode->left = newNode;  
                return true;

            } 

            currentNode = currentNode->left;
        } 
        
    }

}

bool Tree::del(const int key){

    Node *currentNode = root;
    Node *previousNode = nullptr;

    if (currentNode == nullptr){
        
        return false;

    }

    while (key != currentNode->key){

        if (key > currentNode->key){

            if (currentNode->right == nullptr){return false;}
            
            previousNode = currentNode;
            currentNode = currentNode->right;

        }

        if (key < currentNode->key){

            if (currentNode->left == nullptr) {return false;}

            previousNode = currentNode;
            currentNode = currentNode->left;
            
        }

    } 

    if (currentNode->left == nullptr && currentNode->right == nullptr){

        if (currentNode == root){

            root = nullptr;
        
        }else if(previousNode->left == currentNode){

            previousNode->left = nullptr;
        
        }else{

            previousNode->right = nullptr;
        
        }

        delete currentNode;
        return true;
    }  

    if (currentNode->left == nullptr){

        if (currentNode == root){

            root = currentNode->right;

        }else if(previousNode->left == currentNode){

            previousNode->left = currentNode->right;
        
        }else{

            previousNode->right = currentNode->right;

        }

        delete currentNode;
        return true;
    
    }

    if (currentNode->right == nullptr){

        if (currentNode == root){
            root = currentNode->left;
        }
        else if(previousNode->left == currentNode){
            previousNode->left = currentNode->left;
        
        }else{

            previousNode->right = currentNode->left;
        
        }

        delete currentNode;
        return true;
    
    }

    //if there are two children

    if (currentNode == root){

        Node *minRightElement = getMin(currentNode->right);
        minRightElement->left = root->left;
        root = currentNode->right;

        delete currentNode;
        return true;
 
    }else{

        Node *minRightElement = getMin(currentNode->right);
        minRightElement->left = currentNode->left;
        previousNode = currentNode->right;

        delete currentNode;
        return true;    

    }

}

Node* Tree::getMin(Node* currentMin){

    if (currentMin->left != nullptr){

        getMin(currentMin->left);
    
    }else{

        return currentMin;
    
    }

}

string Tree::find(const int key){

    Node *currentNode = root;
    string error = "";

    if (currentNode == nullptr){return error;}

    while (currentNode->key != key){

        if (key > currentNode->key){

            if (currentNode->right == nullptr){return error;}  
            currentNode = currentNode->right;

        }else if (key < currentNode->key){

            if (currentNode->left == nullptr){return error;}
            currentNode = currentNode->left;
        }

    }

    return currentNode->data;

}


int main(){

    Tree testTree;
    testTree.add(100, "one hundred");
    testTree.add(40, "forty");
    testTree.add(110, "one hundred and ten");
    testTree.add(30, "thirty");

    testTree.del(40);
    cout << "The 40th element deleted" << endl << endl;

    cout << testTree.find(100) << endl;
    cout << testTree.find(40) << endl;
    cout << testTree.find(30) << endl;
    cout << testTree.find(110) << endl << endl;
    
    cout << "The end." << endl;

}
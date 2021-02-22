#include <iostream>
#include <iostream>
#include <string>

// Binary search tree

class Node {
public:
    int key;
    std::string data;
    std:: string color;
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
    Node *getUncle (Node* root, int parentKey);
    void changeColorWhileAdding (Node* child);
    void rotateTreeToRight (Node* grandpa);
    void rotateTreeToLeft (Node* grandpa);
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
    color = "read";
}

Node::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
    color = "read";
}

Node::Node(int key,  std::string data,  Node *left,  Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
    color = "read";
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


void Tree::rotateTreeToRight (Node *grandpa) {
    Node *grandgrandpa = getParent(root,grandpa->key);
    Node *oldParent = grandpa->left;
    if (grandgrandpa != nullptr){
        if (grandgrandpa->right == grandpa)
            grandgrandpa->right = oldParent;
        else
            grandgrandpa->left = oldParent;
    }
    grandpa->left = oldParent->right;
    oldParent->right = grandpa;
}

void Tree::rotateTreeToLeft(Node *grandpa) {
    Node *grandgrandpa = getParent(root,grandpa->key);
    Node *oldParent = grandpa->right;
    if (grandgrandpa != nullptr){
        if (grandgrandpa->right == grandpa)
            grandgrandpa->right = oldParent;
        else
            grandgrandpa->left = oldParent;
    }
    grandpa->right = oldParent->left;
    oldParent->left = grandpa;
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

Node* Tree::getUncle(Node *root, int childkey) {
    Node* parent = getParent(root, childkey);
    if (parent == nullptr)
        return nullptr;
    Node* grandpa = getParent(root, parent->key);
    if (grandpa == nullptr)
        return nullptr;
    if (grandpa->left == parent)
        return grandpa->right;
    else
        return grandpa->left;
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

void Tree::changeColorWhileAdding(Node* child) {
    child->color = "red";
    Node* parent = getParent(root, child->key);

    if (parent == nullptr){
        child->color = "black";
        return;
    }

    if (parent->color == "black") {
        return;
    }

    if (parent->color == "red") {
        Node* grandpa = getParent(root, parent->key);
        Node* uncle = getUncle(root, child->key);

        if ((uncle == nullptr)||(uncle->color == "black")) {
            if (grandpa->left == parent){
                if (parent->right == child){
                    Node *tempParent = grandpa->left;
                    Node *tempChildLeft = child->left;
                    grandpa->left = child;
                    child->left = tempParent;
                    tempParent->right = tempChildLeft;
                    child = grandpa->left->left;
                    parent = getParent(root,child->key);
                }
                parent->color = "red";
                grandpa->color = "black";
                rotateTreeToRight(grandpa);
                return;
            }

            if (grandpa->right == parent){
                if (parent->left == child){
                    Node *tempParent = grandpa->right;
                    Node *tempChildRight = child->right;
                    grandpa->right = child;
                    child->right = tempParent;
                    tempParent->left = tempChildRight;
                    child = grandpa->right->right;
                    parent = getParent(root,child->key);
                }
                parent->color = "red";
                grandpa->color = "black";
                rotateTreeToLeft(grandpa);
                return;
            }

            if (uncle->color == "red") {
                parent->color = "black";
                uncle->color = "black";
                grandpa->color = "red";
                return changeColorWhileAdding(grandpa);
            }
        }
    }
}

bool Tree::add(const int key, std::string data) {
    Node* child = new Node (key,data);

    if (getNode(root,key)!= nullptr)
        return false;

    if (root == nullptr){
        child->color = "black";
        root = child;
        return true;
    }

    Node* parent = getParent(root, key);

    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;

    changeColorWhileAdding(child);
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
    testTree.add(42, "5");
    testTree.add(31, "7");
    testTree.add(29, "6");
    testTree.add(44, "8");
    testTree.add(95, "9");
    std::cout<<testTree.find(42)<<std::endl;
    std::cout<<testTree.find(29)<<std::endl;
    std::cout<<testTree.find(95)<<std::endl;
    std::cout<<testTree.find(31)<<std::endl;
    std::cout<<testTree.find(44)<<std::endl;
    std::cout << "The end." << std::endl;
}

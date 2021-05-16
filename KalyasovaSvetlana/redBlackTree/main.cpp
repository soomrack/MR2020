#include <iostream>
#include <string>
#include <chrono>


class Node {
public:
    int key;
    std::string data;
    bool red;
public:
    Node *left;
    Node *right;
public:
    Node();
    Node(int key, std::string data);
    ~Node();
};


class Tree {
private:
    Node *root;
    Node *findMin(Node* root);
    Node *findNode(Node* root, int key);
    Node *findParent(Node * root, int key);
    Node *findUncle(Node *root, int childKey, Node* parent, Node* grParent);
    Node *findBrother(Node *root, Node* parent);
    void recurseAdding (Node* child, Node* root);
    void rotateRight (Node* node);
    void rotateLeft (Node* node);
    void rebalance (Node *parent);
    void outputTree (Node *root, int totalSpace);
public:
    void printTree();
    bool add(const int key, std::string data);
    bool del(const int key);
    std::string find(const int key);
public:
    Tree();
    ~Tree();
};

Node::Node() {
    left = nullptr;
    right = nullptr;
    red = true;
}

Node::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
    red = true;
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

void Tree::outputTree(Node *root, int level) {
    if(root)
    {
        outputTree(root->left,level + 1);
        for(int i = 0;i< level;i++) std::cout<<"   ";
        if (root->red == true)
            printf("r");
        if (root->red == false)
            printf("b");
        std::cout << root->key << std::endl;
        outputTree(root->right,level + 1);
    }
}


void Tree::printTree() {
    outputTree(root,0);
}

void Tree::rotateRight (Node *node) {
    Node *grgrParent = findParent(root, node->key);
    Node *parent = node->left;
    if (grgrParent != nullptr){
        if (grgrParent->right == node)
            grgrParent->right = parent;
        else
            grgrParent->left = parent;
    }
    node->left = parent->right;
    parent->right = node;
}

void Tree::rotateLeft(Node *node) {
    Node *grgrParent = findParent(root, node->key);
    Node *parent = node->right;
    if (grgrParent != nullptr){
        if (grgrParent->right == node)
            grgrParent->right = parent;
        else
            grgrParent->left = parent;
    }
    node->right = parent->left;
    parent->left = node;
}

Node* Tree::findNode(Node *root, int key) {
    if (root == nullptr) return root;
    if (root->key == key) return root;
    if (root->key > key) return findNode(root->left, key);
    return findNode(root->right, key);
}

Node* Tree::findParent(Node *root, int key){
    if (root->key < key) {
        if (root->right == nullptr)
            return root;
        if (root->right->key == key)
            return root;
        return findParent(root->right, key);
    }

    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        if (root->left->key == key)
            return root;
        return findParent(root->left, key);
    }
    return nullptr;
}

Node* Tree::findUncle(Node *root, int childKey, Node* parent, Node *grParent) {
    if (parent == nullptr)
        return nullptr;
    if (grParent == nullptr)
        return nullptr;
    if (grParent->left == parent)
        return grParent->right;
    else
        return grParent->left;
}

std::string Tree::find(const int key){
    Node* temp = root;
    temp = findNode(temp, key);
    if (temp == nullptr)
        return "nothing find";
    return temp->data;
}

void Tree::recurseAdding(Node* child, Node* root) {
    root->red = false;
    child->red = true;
    Node* parent = findParent(root, child->key);

    if (parent == nullptr){
        child->red = false;
        return;
    }

    if (!(parent->red)) {
        return;
    }

    Node* grParent = findParent(root, parent->key);
    Node* uncle = findUncle(root, child->key, parent, grParent);

    if (parent->red) {
        if ((uncle != nullptr) && uncle->red) {
            parent->red = false;
            uncle->red = false;
            grParent->red = true;
            return recurseAdding(grParent, root);
        }

        if ((uncle == nullptr) || !(uncle->red)) {
            if (grParent->left == parent){
                if (parent->right == child){
                    rotateLeft(parent);
                    child = grParent->left->left;
                    parent = findParent(root, child->key);
                    grParent = findParent(root, parent->key);
                }
                parent->red = false;
                grParent->red = true;
                rotateRight(grParent);
                root->red = false;
                return;
            }

            if (grParent->right == parent){
                if (parent->left == child){
                    rotateRight(parent);
                    child = grParent->right->right;
                    parent = findParent(root, child->key);
                    grParent = findParent(root, parent->key);
                }
                parent->red = false;
                grParent->red = true;
                rotateLeft(grParent);
                root->red = false;
                return;
            }
        }
    }
}

bool Tree::add(const int key, std::string data) {
    Node* child = new Node (key,data);

    if (findNode(root, key) != nullptr)
        return false;

    if (root == nullptr){
        child->red = false;
        root = child;
        return true;
    }

    Node* parent = findParent(root, key);

    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;

    recurseAdding(child, root);
    return true;
}

Node* Tree::findBrother (Node *root, Node* parent){
    if (parent->left == nullptr)
        return parent->right;
    else
        return parent->left;
}

Node* Tree::findMin (Node *root) {
    Node *min = root;
    while (min->left != nullptr){
        min = min->left;
    }
    return min;
}

void Tree::rebalance(Node *parent) {
    if (parent == root)
        return;

    Node *child = findBrother(root, parent);
    Node *grandpa = findParent(root,parent->key);

    if (child->red == true){
        parent->red = true;
        child->red = false;
        if (child == parent->left)
            rotateLeft(parent);
        else
            rotateRight(parent);
    }

    if (child->red == false && parent->red == false){
        if (child->left == nullptr || child->left->red == false){
            if (child->right == nullptr || child->right->red == false){
                child = findBrother(root, parent);
                child->red = true;
                return rebalance(grandpa);
            }
        }
    }


    if (child->red == false && parent->red == true){
        if (child->left == nullptr || child->left->red == false){
            if (child->right == nullptr || child->right->red == false){
                child = findBrother(root, parent);
                child->red = true;
                parent->red = false;
                return;
            }
        }
    }

    if (child->red == false){
        if (child == parent->left && child->right->red == true){
            if (child->left->red == false || child->left == nullptr){
                child = findBrother(root, parent);
                child->red = true;
                child->right->red = false;
                rotateLeft(child);
            }
        }

        else if (child == parent->right && child->left->red == true){
            if (child->right->red == false || child->right == nullptr){
                child = findBrother(root, parent);
                child->red = true;
                child->left->red = false;
                rotateRight(child);
            }
        }

        child = findBrother(root, parent);
        child->red = parent->red;
        parent->red = false;
        if (child == parent->right){
            child->right->red = false;
            rotateLeft(parent);
            return;
        }
        child->left->red = false;
        rotateRight(parent);
        return;
    }
}

bool Tree::del(const int key) {
    Node *delNode = findNode(root, key);
    Node *delParent = findParent(root, key);
    if (delNode == nullptr)
        return false;

    if (delNode->left != nullptr && delNode->right != nullptr) {
        Node *min = findMin(delNode->right);
        delNode->key = min->key;
        delNode->data = min->data;
        min->key = key;
        del(min->key);
    }

    if (delNode->red == true) {
        if (delNode->left == nullptr && delNode->right == nullptr) {
            if (delParent->left == delNode) {
                delParent->left = nullptr;
                delete delNode;
                return true;
            }
            delParent->right = nullptr;
            delete delNode;
            return true;
        }
    }

    if (delNode->right == nullptr && delNode->left != nullptr) {
        if (delParent->left == delNode) {
            delParent->left = delNode->left;
            delete delNode;
            delParent->left->red = false;
            return true;
        }
        delParent->right = delNode->left;
        delete delNode;
        delParent->right->red = false;
        return true;
    }

    if (delNode->left == nullptr && delNode->right != nullptr) {
        if (delParent->left == delNode) {
            delParent->left = delNode->right;
            delete delNode;
            delParent->left->red = false;
            return true;
        }
        delParent->right = delNode->right;
        delete delNode;
        delParent->right->red = false;
        return true;
    }

    if (delNode->red = false){
        if (delParent->left == delNode)
            delParent->left = nullptr;
        else
            delParent->right = nullptr;
        delete delNode;
        rebalance(delParent);
        return true;
    }
}


int main() {
    Tree testTree;
    testTree.add(20, "1");
    testTree.add(86, "2");
    testTree.add(35, "3");
    testTree.add(13, "4");
    testTree.add(62, "5");
    testTree.add(100, "6");
    testTree.add(48, "7");
    testTree.add(-15, "8");
    testTree.add(0, "9");
    testTree.add(5, "10");
    testTree.del(5);
    testTree.printTree();
}
#include <iostream>
#include <iostream>
#include <string>

// Binary search tree

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
    Node(int key, std::string data, Node *left, Node *right);
    ~Node();
};


class Tree {
private:
    Node *root;
    Node *getNode(Node* root, int key);
    Node* getParent (Node * root, int key);
    Node* getMin(Node* root);
    Node *getUncle (Node *root, int childKey);
    Node *getSon(Node *root, Node* parent);
    void changeColorWhileAdding (Node* child, Node* root);
    void rotateTreeToRight (Node* grandpa);
    void rotateTreeToLeft (Node* grandpa);
    void blackNodeBalance (Node *parent);
    void outputTree (Node *root, int totalSpace);
public:
    void printTree();
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
    red = true;
}

Node::Node(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
    red = true;
}

Node::Node(int key,  std::string data,  Node *left,  Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
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

//случай для нахождения брата удаляемого корня
Node* Tree::getSon (Node *root, Node* parent){
    if (parent->left == nullptr)
        return parent->right;
    else
        return parent->left;
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

void Tree::changeColorWhileAdding(Node* child, Node* root) {
    root->red = false;
    child->red = true;
    Node* parent = getParent(root, child->key);
    Node* uncle = getUncle(root, child->key);

    if (parent == nullptr){
        child->red = false;
        return;
    }

    Node* grandpa = getParent(root, parent->key);
    if (parent->red == false) {
        return;
    }

    if (parent->red == true) {
        if ((uncle != nullptr) && (uncle->red == true)) {
            parent->red = false;
            uncle->red = false;
            grandpa->red = true;
            return changeColorWhileAdding(grandpa, root);
        }

        if ((uncle == nullptr)||(uncle->red == false)) {
            if (grandpa->left == parent){
                if (parent->right == child){
                    rotateTreeToLeft(parent);
                    child = grandpa->left->left;
                    parent = getParent(root,child->key);
                    grandpa = getParent(root,parent->key);
                }
                parent->red = false;
                grandpa->red = true;
                rotateTreeToRight(grandpa);
                root->red = false;
                return;
            }

            if (grandpa->right == parent){
                if (parent->left == child){
                    rotateTreeToRight(parent);
                    child = grandpa->right->right;
                    parent = getParent(root,child->key);
                    grandpa = getParent(root,parent->key);
                }
                parent->red = false;
                grandpa->red = true;
                rotateTreeToLeft(grandpa);
                root->red = false;
                return;
            }
        }
    }
}

bool Tree::add(const int key, std::string data) {
    Node* child = new Node (key,data);

    if (getNode(root,key)!= nullptr)
        return false;

    if (root == nullptr){
        child->red = false;
        root = child;
        return true;
    }

    Node* parent = getParent(root, key);

    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;

    changeColorWhileAdding(child, root);
    return true;
}

void Tree::blackNodeBalance(Node *parent) {
    if (parent == root)
        return;

    Node *child = getSon(root, parent);
    Node *grandpa = getParent(root,parent->key);
    //меняем цвет родителя и ребенка и делаем поворот дерева
    //это позволяет привести данный случай к последующим
    if (child->red == true){
        parent->red = true;
        child->red = false;
        if (child == parent->left)
            rotateTreeToLeft(parent);
        else
            rotateTreeToRight(parent);
    }

    //если все черные, то делаем ребенка красным и рекурсивно запускаем функцию
    if (child->red == false && parent->red == false){
        if (child->left == nullptr || child->left->red == false){
            if (child->right == nullptr || child->right->red == false){
                //родитель удаляемого узла не меняется, а вот брат может запросто
                child = getSon(root, parent);
                child->red = true;
                return blackNodeBalance(grandpa);
            }
        }
    }

    //если ребенок черный, а родитель красный, то меняем их цвета местами
    if (child->red == false && parent->red == true){
        if (child->left == nullptr || child->left->red == false){
            if (child->right == nullptr || child->right->red == false){
                child = getSon(root, parent);
                child->red = true;
                parent->red = false;
                return;
            }
        }
    }

    //если ребенок правый(левый) и у него левый(правый) красный сын, то поворачиваем дерево
    //и меняем цвета, чтобы привести ситуацию к реализуемой ниже
    if (child->red == false){
        if (child == parent->left && child->right->red == true){
            if (child->left->red == false || child->left == nullptr){
                child = getSon (root, parent);
                child->red = true;
                child->right->red = false;
                rotateTreeToLeft(child);
            }
        }

        else if (child == parent->right && child->left->red == true){
            if (child->right->red == false || child->right == nullptr){
                child = getSon (root, parent);
                child->red = true;
                child->left->red = false;
                rotateTreeToRight(child);
            }
        }

        //тут может быть только правый(левый) черный ребенок с правым(левым) красным сыном
        //поэтому мы просто меняем цветами родителя и ребенка и поворачиваем дерево
        child = getSon (root, parent);
        child->red = parent->red;
        parent->red = false;
        if (child == parent->right){
            child->right->red = false;
            rotateTreeToLeft(parent);
            return;
        }
        child->left->red = false;
        rotateTreeToRight(parent);
        return;
    }
}


bool Tree::del(const int key) {
    Node *delNode = getNode(root, key);
    Node *delParent = getParent(root, key);
    if (delNode == nullptr)
        return false;

    if (delNode->left != nullptr && delNode->right != nullptr) {
        //если 2 потомка, то сводим к случаю с 1 или 0 потомками, не меняя цвета
        Node *min = getMin(delNode->right);
        delNode->key = min->key;
        delNode->data = min->data;
        min->key = key;
        del(min->key);
    }

    if (delNode->red == true) {
        // если узел красный, то у него либо 0 потомков, либо 2
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

    // это возможно только для черного узла и красного потомка
    // тогда мы присоединяем потомка к родителю и меняем его цвет на черный
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

    // аналогично предыдущему случаю
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

    //тут остается только вариант с черным узлом и 0 потомков
    if (delNode->red = false){
        if (delParent->left == delNode)
            delParent->left = nullptr;
        else
            delParent->right = nullptr;
        delete delNode;
        blackNodeBalance(delParent);
        return true;
    }
}


int main() {
    Tree testTree;
    testTree.add(33, "3");
    testTree.add(42, "5");
    testTree.add(31, "7");
    testTree.add(29, "6");
    testTree.add(44, "8");
    testTree.add(95, "9");
    testTree.add(88, "11");
    testTree.add(-5, "13");
    testTree.add(1, "3");
    testTree.add(2, "5");
    testTree.add(3, "7");
    testTree.add(4, "6");
    testTree.add(5, "8");
    testTree.add(6, "9");
    testTree.add(7, "11");
    testTree.add(8, "13");
    testTree.add(10, "3");
    testTree.add(11, "5");
    testTree.add(12, "7");
    testTree.add(13, "6");
    std::cout<<testTree.find(42)<<std::endl;
    std::cout<<testTree.find(29)<<std::endl;
    std::cout<<testTree.find(95)<<std::endl;
    std::cout<<testTree.find(31)<<std::endl;
    std::cout<<testTree.find(44)<<std::endl;
    std::cout<<testTree.find(33)<<std::endl;
    testTree.printTree();
    testTree.del(6);
    testTree.del(7);
    testTree.del(12);
    testTree.del(88);
    testTree.del(33);
    std::cout<<testTree.find(88)<<std::endl;
    std::cout<<testTree.find(7)<<std::endl;
    testTree.printTree();
    std::cout << "The end." << std::endl;
}


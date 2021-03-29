#include <iostream>
#include <string>

// Binary search tree

const int numberOfPointers = 4;
const int emptyKey = 2147483647;


class Node {
public:
    int arrOfKeys[numberOfPointers-1];
    std::string arrOfData[numberOfPointers-1];
public:
    Node *arrOfPointers[numberOfPointers];
public:
    Node();
    ~Node();
};


class Tree {
private:
    Node *root;
    bool isNodeFull(Node *root);
    int getChildIndex (Node *root, int key);
    void adding(Node *root, int key, std::string data);
    bool isNodeALief (Node *root);
    int getAmountOfKeys (Node *currentNode);
    void split (Node *parent, Node *child);
    std::string getNodeData(Node* currentNode, int key);
    Node* getParent (Node * currentNode, int key, Node* parent);
    Node* getNodeByKey (Node *root, int key);
    void deleteKeyFromNode (Node *currentNode, int key);
    void merge(Node *leftNode, Node *rightNode, Node *parent, int index);
    void rebalanceLief(Node *currentNode, int keysNum, int index, Node *parent);
    //эту функцию как раз и осталось допилить
    void rebalanceNotALief(Node *currentNode, int keysNum, int index, Node *parent);
public:
    bool add(const int key, std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() {
    for (int i = 0; i<=(numberOfPointers-2); i++){
        arrOfKeys[i] = emptyKey;
        arrOfData[i] = "";
        arrOfPointers[i] = nullptr;
    }
    arrOfPointers[numberOfPointers-1] = nullptr;
}

Node::~Node() {
    delete arrOfPointers[numberOfPointers-1];
}

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    delete root;
}

bool Tree::isNodeFull(Node *root) {
    for (int i = 0; i<=(numberOfPointers-2); i++){
        if (root->arrOfKeys[i] == emptyKey) {
            return false;
        }
    }
    return true;
}

bool Tree::isNodeALief(Node *root) {
    for (int i = 0; i<=numberOfPointers-1; i++){
        if (root->arrOfPointers[i] != nullptr)
            return false;
    }
    return true;
}

int Tree::getChildIndex(Node *root, int key) {
    int index = 0;
    for (int i = 0; i<=(numberOfPointers-2); i++) {
        if (root->arrOfKeys[i] <= key)
            index = i + 1;
        if (root->arrOfKeys[i] > key)
            break;
    }
    return index;
}


void Tree::split(Node *parent, Node *child) {
    int index = getChildIndex(parent, child->arrOfKeys[0]);
    if (isNodeFull(parent) == false){
        parent->arrOfKeys[numberOfPointers-2] = child->arrOfKeys[0];
        parent->arrOfData[numberOfPointers-2] = child->arrOfData[0];
        parent->arrOfPointers[index] = child->arrOfPointers[0];
        parent->arrOfPointers[numberOfPointers-1] = child->arrOfPointers[1];
        for (int i = index; i<=(numberOfPointers-3); i++) {
            std::swap(parent->arrOfKeys[i], parent->arrOfKeys[numberOfPointers - 2]);
            std::swap(parent->arrOfData[i], parent->arrOfData[numberOfPointers - 2]);
            std::swap(parent->arrOfPointers[i+1], parent->arrOfPointers[numberOfPointers-1]);
        }
        delete child;
        return;
    }

    int tempArr[numberOfPointers];
    std::string tempArrData[numberOfPointers];
    Node* tempArrOfPointers[numberOfPointers+1];
    for (int i = 0; i<= (numberOfPointers-2); i++){
        tempArr[i] = parent->arrOfKeys[i];
        tempArrData[i] = parent->arrOfData[i];
        tempArrOfPointers[i] = parent->arrOfPointers[i];
    }

    tempArrOfPointers[numberOfPointers-1] = parent->arrOfPointers[numberOfPointers-1];
    tempArrOfPointers[index] = child->arrOfPointers[0];
    tempArr[numberOfPointers-1] = child->arrOfKeys[0];
    tempArrData[numberOfPointers-1] = child->arrOfData[0];
    tempArrOfPointers[numberOfPointers] = tempArrOfPointers[1];

    for (int i = index; i<=(numberOfPointers-2); i++) {
        std::swap(tempArr[i], tempArr[numberOfPointers - 1]);
        std::swap(tempArrData[i], tempArrData[numberOfPointers - 1]);
        std::swap(tempArrOfPointers[i+1], tempArrOfPointers[numberOfPointers]);
    }

    Node *left = new Node();
    Node *right = new Node();
    int mid;
    if (numberOfPointers % 2 == 1)
        mid = (numberOfPointers-1)/2;
    else{
        if (index < (numberOfPointers/2))
            mid = numberOfPointers/2;
        else
            mid = ((numberOfPointers/2)-1);
    }

    for (int i = 0; i<=(mid-1); i++){
        left->arrOfKeys[i] = tempArr[i];
        left->arrOfData[i] = tempArrData[i];
        left->arrOfPointers[i] = tempArrOfPointers[i];
    }

    left->arrOfPointers[mid] = tempArrOfPointers[mid];
    for (int i = mid+1; i<=(numberOfPointers-1); i++){
        right->arrOfKeys[i-(mid+1)] = tempArr[i];
        right->arrOfData[i-(mid+1)] = tempArrData[i];
        right->arrOfPointers[i-(mid+1)] = tempArrOfPointers[i];
    }

    right->arrOfPointers[numberOfPointers-(mid+1)] = tempArrOfPointers[numberOfPointers];
    int tempMid = tempArr[mid];
    std::string tempMidData = tempArrData[mid];
    for (int i = 0; i<=(numberOfPointers-2); i++) {
        parent->arrOfKeys[i] = emptyKey;
        parent->arrOfData[i] = "";
        parent->arrOfPointers[i] = nullptr;
    }

    parent->arrOfPointers[numberOfPointers-1] = nullptr;
    parent->arrOfKeys[0] = tempMid;
    parent->arrOfData[0] = tempMidData;
    parent->arrOfPointers[0] = left;
    parent->arrOfPointers[1] = right;
    Node* grandpa = getParent(root,parent->arrOfKeys[0],root);
    delete child;
    if (parent == root)
        return;
    return split(grandpa, parent);
}

void Tree::adding(Node *node, int key, std::string data) {
    int index = getChildIndex(node,key);
    if (isNodeALief(node) == true){
        Node* child = new Node ();
        node->arrOfPointers[index] = child;
        child->arrOfData[0] = data;
        child->arrOfKeys[0] = key;
        split(node,child);
        return;
    }
    return adding(node->arrOfPointers[index], key, data);
}

std::string Tree::getNodeData(Node *currentNode, int key) {
    int index = getChildIndex(currentNode,key);
    if (currentNode->arrOfKeys[index-1] == key)
        return currentNode->arrOfData[index-1];
    if (isNodeALief(currentNode) == true)
        return "";
    return getNodeData(currentNode->arrOfPointers[index],key);
}



Node* Tree::getParent(Node *currentNode, int key, Node* parent){
    Node *father = parent;
    if (currentNode == root)
        father = nullptr;
    int index = getChildIndex(currentNode, key);
    if (currentNode->arrOfKeys[index-1] == key)
        return father;
    return getParent(currentNode->arrOfPointers[index],key,currentNode);
}


std::string Tree::find(const int key){
    std::string data = getNodeData(root, key);
    return data;
}

Node* Tree::getNodeByKey(Node *root, int key) {
    Node *currentNode = root;
    int index = getChildIndex(root, key);
    if (currentNode->arrOfKeys[index-1] == key)
        return currentNode;
    return getNodeByKey(currentNode->arrOfPointers[index], key);
}

int Tree::getAmountOfKeys(Node *currentNode) {
    int num = 0;
    for (int i = 0; i<=(numberOfPointers-2); i++){
        if (currentNode->arrOfKeys[i] != emptyKey) {
            num++;
        }
    }
    return num;
}

bool Tree::add(const int key, std::string data) {
    if (root == nullptr){
        root = new Node ();
        root->arrOfKeys[0] = key;
        root->arrOfData[0] = data;
        return true;
    }

    if (getNodeData(root,key) != "")
        return false;
    adding(root,key,data);
    return true;
}

void Tree::deleteKeyFromNode(Node *currentNode, int key) {
    int index = 0;
    for (int i = 0; i<=(numberOfPointers-2);i++){
        if (currentNode->arrOfKeys[i] == key){
            currentNode->arrOfKeys[i] = emptyKey;
            currentNode->arrOfData[i] = "";
            currentNode->arrOfPointers[i+1] = nullptr;
            break;
        }
        index++;
    }
    for (int j = index; j<=(numberOfPointers-3);j++){
        std::swap(currentNode->arrOfKeys[j],currentNode->arrOfKeys[j+1]);
        std::swap(currentNode->arrOfData[j],currentNode->arrOfData[j+1]);
        std::swap(currentNode->arrOfPointers[j+1],currentNode->arrOfPointers[j+2]);
    }
}

void Tree:: merge (Node *leftNode, Node *rightNode, Node *parent, int index){
    int keysNum = getAmountOfKeys(leftNode);
    leftNode->arrOfKeys[keysNum] = parent->arrOfKeys[index-1];
    leftNode->arrOfData[keysNum] = parent->arrOfData[index-1];
    leftNode->arrOfPointers[keysNum+1] = rightNode->arrOfPointers[0];
    int rightKeysNum = getAmountOfKeys(rightNode);
    int j = 0;
    for (int i = keysNum+1; i<=(keysNum+rightKeysNum);i++){
        leftNode->arrOfKeys[i] = rightNode->arrOfKeys[j];
        leftNode->arrOfData[i] = rightNode->arrOfData[j];
        leftNode->arrOfPointers[i+1] = rightNode->arrOfPointers[j+1];
        j++;
    }
    deleteKeyFromNode(parent,parent->arrOfKeys[index-1]);
}

void Tree::rebalanceLief(Node *currentNode, int keysNum, int index, Node *parent) {
    Node *leftBrother = root;
    Node *rightBrother = root;
    if (index != 0){
        leftBrother = parent->arrOfPointers[index-1];
        int leftKeysNum = getAmountOfKeys(leftBrother);
        if (leftKeysNum >= (numberOfPointers/2)){
            int tempKey = leftBrother->arrOfKeys[leftKeysNum-1];
            std::string tempData = leftBrother->arrOfData[leftKeysNum-1];
            currentNode->arrOfKeys[keysNum] = parent->arrOfKeys[index-1];
            currentNode->arrOfData[keysNum] = parent->arrOfData[index-1];
            for (int i = keysNum; i>0; i++){
                std::swap(currentNode->arrOfKeys[keysNum], currentNode->arrOfKeys[keysNum-1]);
                std::swap(currentNode->arrOfData[keysNum],currentNode->arrOfData[keysNum-1]);
            }
            parent->arrOfKeys[index-1] = tempKey;
            parent->arrOfData[index-1] = tempData;
            leftBrother->arrOfKeys[leftKeysNum-1] = emptyKey;
            leftBrother->arrOfData[leftKeysNum-1] = "";
            return;
        }
    }

    if (index != numberOfPointers-1){
        rightBrother = parent->arrOfPointers[index+1];
        int rightKeysNum = getAmountOfKeys(rightBrother);
        if (rightKeysNum >= (numberOfPointers/2)){
            int tempKey = rightBrother->arrOfKeys[0];
            std::string tempData = leftBrother->arrOfData[0];
            currentNode->arrOfKeys[keysNum] = parent->arrOfKeys[index+1];
            currentNode->arrOfData[keysNum] = parent->arrOfData[index+1];
            parent->arrOfKeys[index+1] = tempKey;
            parent->arrOfData[index+1] = tempData;
            deleteKeyFromNode(rightBrother,rightBrother->arrOfKeys[0]);
            return;
        }
        Node *grandpa = getParent(root,parent->arrOfKeys[0],root);
        int parIndex = getChildIndex(grandpa,parent->arrOfKeys[0]);
        if (index != 0)
            merge(leftBrother,currentNode,parent,index);
        else
            merge(currentNode,rightBrother,parent,index+1);
        int parKeysNum = getAmountOfKeys(parent);
        if (parKeysNum < (numberOfPointers/2))
            return rebalanceNotALief(parent,keysNum,index,grandpa);
    }
}

bool Tree::del(const int key){
    Node *NodeWithDeletedKey = getNodeByKey(root,key);
    if (isNodeALief(NodeWithDeletedKey) == true){
        int keysNum = getAmountOfKeys(NodeWithDeletedKey);

        if (keysNum >= (numberOfPointers/2)){
            deleteKeyFromNode(NodeWithDeletedKey,key);
            return true;
        }

        else {
            Node *parent = getParent(root,key,root);
            int index = getChildIndex(parent,key);
            deleteKeyFromNode(NodeWithDeletedKey,key);
            rebalanceLief(NodeWithDeletedKey,keysNum,index,parent);
        }
    }

}


int main() {
    Tree testTree;
    testTree.add(1, "3");
    testTree.add(15, "4");
    testTree.add(7,"5");
    testTree.add(9, "6");
    testTree.add(0, "7");
    testTree.add(16,"8");
    testTree.add(17, "9");
    testTree.add(-5, "10");
    testTree.add(-12,"11");
    testTree.add(-15, "12");
    testTree.add(11, "13");
    testTree.add(33,"14");
    std::cout<<testTree.find(15)<<std::endl;
    std::cout<<testTree.find(7)<<std::endl;
    std::cout<<testTree.find(9)<<std::endl;
    std::cout<<testTree.find(0)<<std::endl;
    std::cout<<testTree.find(16)<<std::endl;
    std::cout<<testTree.find(17)<<std::endl;
    std::cout<<testTree.find(-5)<<std::endl;
    std::cout<<testTree.find(-12)<<std::endl;
    std::cout<<testTree.find(-15)<<std::endl;
    std::cout<<testTree.find(11)<<std::endl;
    std::cout<<testTree.find(33)<<std::endl;
    std::cout << "The end." << std::endl;
}

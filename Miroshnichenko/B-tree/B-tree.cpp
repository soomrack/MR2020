#include <iostream>

#include <string>

using namespace std;

const int elementNumber = 3; // Number of minimun children of node
const int emptyKey = -313131;


class Node {
public:
  int arrOfKeys[elementNumber - 1];
  string arrOfData[elementNumber - 1];
public:
  Node* childrenPointers[elementNumber];
public:
  Node();
  ~Node();
};


class Tree {
private:
  Node* root;
  bool isNodeFull(Node* root);
  int getChildIndex(Node* root, int key);
  void adding(Node* root, int key, string data);
  bool isNodeALief(Node* root);
  void split(Node* parent, Node* child);
  string getNodeData(Node* currentNode, int key);
  Node* getParent(Node* currentNode, int key, Node* parent);
public:
  bool add(const int key, string data);  // false if key already exists
  bool del(const int key);  // false if no key
  string find(const int key);  // return '' if no key
public:
  Tree();
  ~Tree();
};

Node::Node() {
  for (int i = 0; i <= (elementNumber - 2); i++) {
    arrOfKeys[i] = emptyKey;
    arrOfData[i] = "";
    childrenPointers[i] = nullptr;
  }
  childrenPointers[elementNumber - 1] = nullptr;
}

Node::~Node() {
  delete childrenPointers[elementNumber - 1];
}

Tree::Tree() {
  root = nullptr;
}

Tree::~Tree() {
  delete root;
}

bool Tree::isNodeFull(Node* root) {
  for (int i = 0; i <= (elementNumber - 2); i++) {
    if (root->arrOfKeys[i] == emptyKey) {
      return false;
    }
  }
  return true;
}

bool Tree::isNodeALief(Node* root) {
  for (int i = 0; i <= elementNumber - 1; i++) {
    if (root->childrenPointers[i] != nullptr)
      return false;
  }
  return true;
}

int Tree::getChildIndex(Node* root, int key) {
  int index = 0;
  for (int i = 0; i <= (elementNumber - 2); i++) {
    if (root->arrOfKeys[i] <= key)
      index = i + 1;
    if (root->arrOfKeys[i] > key)
      break;
  }
  return index;
}


void Tree::split(Node* parent, Node* child) {
  int index = getChildIndex(parent, child->arrOfKeys[0]);
  if (isNodeFull(parent) == false) {
    parent->arrOfKeys[elementNumber - 2] = child->arrOfKeys[0];
    parent->arrOfData[elementNumber - 2] = child->arrOfData[0];
    parent->childrenPointers[index] = child->childrenPointers[0];
    parent->childrenPointers[elementNumber - 1] = child->childrenPointers[1];
    for (int i = index; i <= (elementNumber - 3); i++) {
      swap(parent->arrOfKeys[i], parent->arrOfKeys[elementNumber - 2]);
      swap(parent->arrOfData[i], parent->arrOfData[elementNumber - 2]);
      swap(parent->childrenPointers[i + 1], parent->childrenPointers[elementNumber - 1]);
    }
    delete child;
    return;
  }

  int tempArr[elementNumber];
  string tempArrData[elementNumber];
  Node* tempArrOfPointers[elementNumber + 1];
  for (int i = 0; i <= (elementNumber - 2); i++) {
    tempArr[i] = parent->arrOfKeys[i];
    tempArrData[i] = parent->arrOfData[i];
    tempArrOfPointers[i] = parent->childrenPointers[i];
  }

  tempArrOfPointers[elementNumber - 1] = parent->childrenPointers[elementNumber - 1];
  tempArrOfPointers[index] = child->childrenPointers[0];
  tempArr[elementNumber - 1] = child->arrOfKeys[0];
  tempArrData[elementNumber - 1] = child->arrOfData[0];
  tempArrOfPointers[elementNumber] = tempArrOfPointers[1];

  for (int i = index; i <= (elementNumber - 2); i++) {
    swap(tempArr[i], tempArr[elementNumber - 1]);
    swap(tempArrData[i], tempArrData[elementNumber - 1]);
    swap(tempArrOfPointers[i + 1], tempArrOfPointers[elementNumber]);
  }

  Node* left = new Node();
  Node* right = new Node();
  int mid;

  if (elementNumber % 2 == 1)
    mid = (elementNumber - 1) / 2;
  else {
    if (index < (elementNumber / 2))
      mid = elementNumber / 2;
    else
      mid = ((elementNumber / 2) - 1);
  }

  for (int i = 0; i <= (mid - 1); i++) {
    left->arrOfKeys[i] = tempArr[i];
    left->arrOfData[i] = tempArrData[i];
    left->childrenPointers[i] = tempArrOfPointers[i];
  }

  left->childrenPointers[mid] = tempArrOfPointers[mid];
  for (int i = mid + 1; i <= (elementNumber - 1); i++) {
    right->arrOfKeys[i - (mid + 1)] = tempArr[i];
    right->arrOfData[i - (mid + 1)] = tempArrData[i];
    right->childrenPointers[i - (mid + 1)] = tempArrOfPointers[i];
  }

  right->childrenPointers[elementNumber - (mid + 1)] = tempArrOfPointers[elementNumber];
  int tempMid = tempArr[mid];
  string tempMidData = tempArrData[mid];
  for (int i = 0; i <= (elementNumber - 2); i++) {
    parent->arrOfKeys[i] = emptyKey;
    parent->arrOfData[i] = "";
    parent->childrenPointers[i] = nullptr;
  }

  parent->childrenPointers[elementNumber - 1] = nullptr;
  parent->arrOfKeys[0] = tempMid;
  parent->arrOfData[0] = tempMidData;
  parent->childrenPointers[0] = left;
  parent->childrenPointers[1] = right;
  Node* grandpa = getParent(root, parent->arrOfKeys[0], root);
  delete child;
  if (parent == root)
    return;
  return split(grandpa, parent);
}

void Tree::adding(Node* node, int key, string data) {
  int index = getChildIndex(node, key);

  if (isNodeALief(node) == true) {
    Node* child = new Node();
    node->childrenPointers[index] = child;
    child->arrOfData[0] = data;
    child->arrOfKeys[0] = key;
    split(node, child);
    return;
  }
  return adding(node->childrenPointers[index], key, data);
}

string Tree::getNodeData(Node* currentNode, int key) {
  int index = getChildIndex(currentNode, key);
  if (currentNode->arrOfKeys[index - 1] == key)
    return currentNode->arrOfData[index - 1];
  if (isNodeALief(currentNode) == true)
    return "";
  return getNodeData(currentNode->childrenPointers[index], key);
}

string Tree::getNodeData(Node* currentNode, int key) {
  int index = getChildIndex(currentNode, key);
  if (currentNode->arrOfKeys[index - 1] == key)
    return currentNode->arrOfData[index - 1];
  if (isNodeALief(currentNode) == true)
    return "";
  return getNodeData(currentNode->childrenPointers[index], key);
}

Node* Tree::getParent(Node* currentNode, int key, Node* parent) {
  Node* father = parent;
  if (currentNode == root)
    father = nullptr;
  int index = getChildIndex(currentNode, key);
  if (currentNode->arrOfKeys[index - 1] == key)
    return father;
  return getParent(currentNode->childrenPointers[index], key, currentNode);
}


string Tree::find(const int key) {
  string data = getNodeData(root, key);
  return data;
}

bool Tree::add(const int key, string data) {
  if (root == nullptr) {
    root = new Node();
    root->arrOfKeys[0] = key;
    root->arrOfData[0] = data;
    return true;
  }
  if (getNodeData(root, key) != "")
    return false;
  adding(root, key, data);
  return true;
}

bool Tree::del(const int key) { 
  if (root == nullptr) return false;
  Node* currentNode = root;
  int currentKey = currentNode->arrOfKeys[0];
  for (int i = 0; key < currentNode->arrOfKeys[i] && i < elementNumber - 1; i++) {
    currentKey = currentNode->arrOfKeys[i];
    
  }
}

int main() {
  
}
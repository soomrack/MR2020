#include <iostream>
#include <string>
#include <cstring>

// Ukkonen's algorithm
static volatile int arrLength = 0;

char input[10000] = {"1231245123412"};

class Node {
public:
    int start;
    int end;
    Node *children[127] = {nullptr};
    Node *suffixLink;
public:
    Node();
    Node(int start, int end);
    ~Node();
};

class Tree {
private:
    Node *root;
    Node *current;
    Node *lastSplit;
    int counter;
    int remainder;
    int activeLength;
    bool isCntInc;
private:
    void split(Node* temp);
    void add(Node *temp);
public:
    void makeTree ();
public:
    Tree();
    ~Tree();
};

Node::Node() {
    start = 0;
    end = arrLength+1;
    suffixLink = nullptr;
}

Node::Node(int start, int end) {
    this->start = start;
    this->end = end;
    suffixLink = nullptr;
}


Node::~Node() {
}

Tree::Tree() {
    root = nullptr;
    current = nullptr;
    lastSplit = nullptr;
    activeLength = 0;
    counter = 0;
    isCntInc = false;
}

Tree::~Tree() {
    delete root;
    delete current;
}

void Tree:: split(Node* temp) {
    int start = temp->start;
    temp->start = start + activeLength;
    Node *parent = new Node(start,start+activeLength-1);
    current->children[input[start]] = parent;
    parent->children[input[temp->start]] = temp;
    parent->children[input[counter]] = new Node (counter, arrLength+1);
    remainder --;
    activeLength --;
    if (lastSplit != nullptr)
        lastSplit->suffixLink = parent;
    lastSplit = parent;
    if (current == root)
        return;
    if (current->suffixLink == nullptr) {
        current = root;
        return;
    }
    current = current->suffixLink;
    return;
}

void Tree::add(Node* temp) {
    if ((counter == arrLength+2) && (remainder == 0))
        return;
    if (isCntInc == false) {
        if (activeLength == 0){
            if (current->children[input[counter]] == nullptr) {
                current->children[input[counter]] = new Node(counter, arrLength+1);
                if (remainder == 0) {
                    counter++;
                    return add(current);
                }
                remainder--;
                if (temp->suffixLink == nullptr)
                    current = root;
                else
                    current = temp->suffixLink;
                return add(current);
            }
            else {
                isCntInc = true;
                remainder ++;
                activeLength ++;
                counter ++;
                lastSplit = nullptr;
                return add(current->children[input[counter-1]]);
            }
        }

        if (activeLength != 0) {
            Node *child = current->children[input[counter-activeLength]];
            int length = child->end - child->start;
            if (length <= activeLength) {
                current = child;
                activeLength = 0;
                return add(current);
            }
            if (input[child->start+activeLength]!=input[counter]){
                split(child);
                return add(current);
            }
            else {
                isCntInc = true;
                remainder ++;
                activeLength ++;
                counter ++;
                lastSplit = nullptr;
                return add(child);
            }
        }
    }

    if (isCntInc == true) {
        int index = temp->start+activeLength;
        int length = temp->end - temp->start;
        if (length < index){
            current = temp;
            activeLength = 0;
            if (current->children[input[counter]] == nullptr){
                isCntInc = false;
                return add(current);
            }
            lastSplit = nullptr;
            counter ++;
            remainder ++;
            activeLength++;
            return add(current->children[input[counter-1]]);
        }

        if (input[index] == input[counter]){
            lastSplit = nullptr;
            counter ++;
            remainder ++;
            activeLength ++;
            return add(temp);
        }

        isCntInc = false;
        split(temp);
        return add(current);
    }
}



void Tree::makeTree() {
    arrLength = strlen(input)-1;
    Node *head = new Node();
    root = head;
    current = head;
    input[arrLength+1] = '$';
    add(current);
}



int main() {
    Tree testTree;
    testTree.makeTree();
}

#include <iostream>

using namespace std;

const int BTreeRank = 4;
const int NoKey = 123456789;
const int NoData = 123456789;

class Node {
public:
    int key[BTreeRank-1]{};
    int data[BTreeRank-1]{};
    Node *pointer[BTreeRank]{};
    Node();
    ~Node();
};

class BTree {
public:
    bool add(int key, int data);
    int find(int key);
    BTree();
    ~BTree();
private:
    Node *root;
    Node* getParent (Node * current, int key, Node* parent);
    int getData(Node* current, int key);
    static int getChildNumber(Node *node, int key);
    static bool isNodeFull(Node *root);
    static bool isLief (Node *node);
    void adding(Node *node, int key, int data);
    void split (Node *parent, Node *child);
};

Node* BTree::getParent(Node *current, int key, Node* parent)
{
    Node *father = parent;
    if (current == root)
        father = nullptr;
    int number = getChildNumber(current, key);
    if (current->key[number-1] == key)
        return father;
    return getParent(current->pointer[number],key,current);
}

bool BTree::isNodeFull(Node *root)
{
    for (int i = 0; i<=(BTreeRank-2); i++)
    {
        if (root->key[i] == NoKey)
            return false;
    }
    return true;
}

int BTree::getChildNumber(Node *node, int key)
{
    int number = 0;
    for (int i = 0; i<=(BTreeRank-2); i++)
    {
        if (node->key[i] <= key)
            number = i + 1;
        if (node->key[i] > key)
            break;
    }
    return number;
}

bool BTree::isLief(Node *node)
{
    for (int i = 0; i<=BTreeRank-1; i++)
    {
        if (node->pointer[i] != nullptr)
            return false;
    }
    return true;
}

bool BTree::add(int key, int data)
{
    if (root == nullptr)
    {
        root = new Node ();
        root->key[0] = key;
        root->data[0] = data;
        return true;
    }
    if (getData(root,key) != NoData)
        return false;
    adding(root,key,data);
    return true;
}

void BTree::adding(Node *node, int key, int data)
{
    int number = getChildNumber(node, key);
    if (isLief(node))
    {
        Node* child = new Node ();
        node->pointer[number] = child;
        child->data[0] = data;
        child->key[0] = key;
        split(node,child);
        return;
    }
    return adding(node->pointer[number], key, data);
}

int BTree::getData(Node *current, int key)
{
    int number = getChildNumber(current,key);
    if (current->key[number-1] == key)
        return current->data[number-1];
    if (isLief(current))
        return NoData;
    return getData(current->pointer[number],key);
}

int BTree::find(int key)
{
    return getData(root, key);
}

void BTree::split(Node *parent, Node *child)
{
    int number = getChildNumber(parent, child->key[0]);
    if (!isNodeFull(parent))
    {
        parent->key[BTreeRank-2] = child->key[0];
        parent->data[BTreeRank-2] = child->data[0];
        parent->pointer[number] = child->pointer[0];
        parent->pointer[BTreeRank-1] = child->pointer[1];
        for (int i = number; i<=(BTreeRank-3); i++)
        {
            swap(parent->key[i], parent->key[BTreeRank - 2]);
            swap(parent->data[i], parent->data[BTreeRank - 2]);
            swap(parent->pointer[i+1], parent->pointer[BTreeRank-1]);
        }
        delete child;
        return;
    }
    int tempKey[BTreeRank];
    int tempData[BTreeRank];
    Node* tempPointer[BTreeRank+1];
    for (int i = 0; i<= (BTreeRank-2); i++)
    {
        tempKey[i] = parent->key[i];
        tempData[i] = parent->data[i];
        tempPointer[i] = parent->pointer[i];
    }
    tempPointer[BTreeRank-1] = parent->pointer[BTreeRank-1];
    tempPointer[number] = child->pointer[0];
    tempKey[BTreeRank-1] = child->key[0];
    tempData[BTreeRank-1] = child->data[0];
    tempPointer[BTreeRank] = tempPointer[1];
    for (int i = number; i<=(BTreeRank-2); i++)
    {
        swap(tempKey[i], tempKey[BTreeRank - 1]);
        swap(tempData[i], tempData[BTreeRank - 1]);
        swap(tempPointer[i+1], tempPointer[BTreeRank]);
    }
    Node *left = new Node();
    Node *right = new Node();
    int middle;
    if (BTreeRank % 2 == 1)
        middle = (BTreeRank-1)/2;
    else
        {
        if (number < (BTreeRank/2))
            middle = BTreeRank/2;
        else
            middle = ((BTreeRank/2)-1);
    }
    for (int i = 0; i<=(middle-1); i++)
    {
        left->key[i] = tempKey[i];
        left->data[i] = tempData[i];
        left->pointer[i] = tempPointer[i];
    }
    left->pointer[middle] = tempPointer[middle];
    for (int i = middle+1; i<=(BTreeRank-1); i++)
    {
        right->key[i-(middle+1)] = tempKey[i];
        right->data[i-(middle+1)] = tempData[i];
        right->pointer[i-(middle+1)] = tempPointer[i];
    }
    right->pointer[BTreeRank-(middle+1)] = tempPointer[BTreeRank];
    int tempMidKey = tempKey[middle];
    int tempMiddleData = tempData[middle];
    for (int i = 0; i<=(BTreeRank-2); i++)
    {
        parent->key[i] = NoKey;
        parent->data[i] = 0;
        parent->pointer[i] = nullptr;
    }
    parent->pointer[BTreeRank-1] = nullptr;
    parent->key[0] = tempMidKey;
    parent->data[0] = tempMiddleData;
    parent->pointer[0] = left;
    parent->pointer[1] = right;
    Node* grandfather = getParent(root,parent->key[0],root);
    delete child;
    if (parent == root)
        return;
    return split(grandfather, parent);
}

Node::Node()
{
    for (int i = 0; i<=(BTreeRank-2); i++)
    {
        key[i] = NoKey;
        data[i] = NoData;
        pointer[i] = nullptr;
    }
    pointer[BTreeRank-1] = nullptr;
}

Node::~Node()
{
    delete pointer[BTreeRank-1];
}

BTree::BTree()
{
    root = nullptr;
}

BTree::~BTree()
{
    delete root;
}

int main()
{

}

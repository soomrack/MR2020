#include <iostream>
#include <algorithm>

using namespace std;

class BTree;

class BNode
{
    friend class BTree;
private:
    int *key;
    int t;
    std::string *data;
    BNode **child;
    int currentKeys;
    bool is_leaf;
public:
    BNode(const int t, const bool is_leaf);
    ~BNode() {};
    void insertNode(const int key, std::string data);
    void splitChild(const int border, BNode *node);
    BNode *searchForNode(const int key);
    int findKey(const int key);
    std::string getDataByKey(const int key);
};

class BTree
{
    friend class BNode;
private:
    BNode *root;
    int t;
public:
    BTree(int t);
    ~BTree() {};
    void addData(const int key, std:: string data);
    std::string find(const int key);
};


BNode::BNode(const int t, const bool is_leaf)
{
    this->t = t;
    this->is_leaf = is_leaf;
    this->key = new int[this->t - 1];
    this->data = new std::string [this->t - 1];
    this->child = new BNode *[this->t];
    this->currentKeys = 0;
}

BTree::BTree(int t)
{
    this->root = nullptr;
    this->t = t;
}


BNode *BNode::searchForNode(const int key)
{
    int index = 0;
    while (index < this->currentKeys && key > this->key[index])
    {
        index++;
    }
    if (this->key[index] == key)
    {
        return this;
    }
    if (this->is_leaf == true)
    {
        return nullptr;
    }
    return child[index]->searchForNode(key);
}

void BTree::addData(const int key, std::string data)
{
    if (root == nullptr)
    {
        root = new BNode(t, true);
        root->key[0] = key;
        root->data[0] = data;
        root->currentKeys = 1;
    }
    else
    {
        if (root->currentKeys == t - 1)
        {
            BNode *node = new BNode(t, false);
            node->child[0] = root;
            node->splitChild(0, root);
            int index = 0;
            if (node->key[0] < key)
            {
                index++;
            }
            node->child[index]->insertNode(key, data);
            root = node;
        }
        else
        {
            root->insertNode(key, data);
        }
    }
}

void BNode::insertNode(const int key, std::string data)
{
    int index = currentKeys - 1;
    if (is_leaf == true)
    {
        while (index >= 0 && this->key[index] > key)
        {
            this->key[index + 1] = this->key[index];
            this->data[index + 1] = this->data[index];
            index--;
        }
        this->key[index + 1] = key;
        this->data[index + 1] = data;
        this->currentKeys++;
    }
    else
    {
        while (index >= 0 && this->key[index] > key)
        {
            index--;
        }
        if (child[index + 1]->currentKeys == t - 1)
        {
            splitChild(index + 1, child[index + 1]);
            if (this->key[index + 1] < key)
            {
                index++;
            }
        }
        child[index + 1]->insertNode(key, data);
    }
}

void BNode::splitChild(const int border, BNode *node)
{
    BNode *newNode = new BNode(node->t, node->is_leaf);
    newNode->currentKeys = t / 2 - 1;
    for (int index = 0; index < t / 2 - 1; index++)
    {
        newNode->key[index] = node->key[index + t / 2];
        newNode->data[index] = node->data[index + t / 2];
    }
    if (node->is_leaf == false)
    {
        for (int index = 0; index < t / 2; index++)
        {
            newNode->child[index] = node->child[index + t / 2];
        }
    }
    node->currentKeys = t / 2 - 1;
    for (int index = currentKeys; index >= border + 1; index--)
    {
        child[index + 1] = child[index];
    }
    child[border + 1] = newNode;
    for (int index = currentKeys - 1; index >= border; index--)
    {
        key[index + 1] = node->key[index];
        data[index + 1] = node->data[index];
    }
    key[border] = node->key[t / 2 - 1];
    data[border] = node->data[t / 2 - 1];
    currentKeys++;
}

int BNode::findKey(const int key)
{
    int index = 0;
    while (index < this->currentKeys && this->key[index] < key)
    {
        index++;
    }
    return index;
}

std::string BNode::getDataByKey(const int key)
{
    int index = findKey(key);
    if (index < this->currentKeys && this->key[index] == key)
    {
        return this->data[index];
    }
    else
    {
        return child[index]->getDataByKey(key);
    }
}

std::string BTree::find(const int key){
    std::string data = root->getDataByKey(key);
    return data;
}

int main()
{
    BTree tree = BTree(6);
    tree.addData(1, "2");
    tree.addData(3, "3");
    tree.addData(5, "4");
    tree.addData(6, "8");
    tree.addData(1, "2");
    tree.addData(10, "11");
    tree.addData(11, "7");
    tree.addData(-1, "-5");
    std::cout << tree.find(1) << std::endl;
    std::cout << tree.find(3) << std::endl;
    std::cout << tree.find(6) << std::endl;
    return 0;
}

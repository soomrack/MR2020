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
    bool isLeaf;
public:
    BNode(const int t, const bool is_leaf);
    ~BNode() {};
    void insertNode(const int key, std::string data);
    void splitChild(const int border, BNode *node);
    void traverse();
    BNode *searchForNode(const int key);
    int findKey(const int key);
    std::string getDataByKey(const int key);
    void remove(const int key);
    void removeFromLeaf(const int index);
    void removeFromNonLeaf(const int index);
    int getPrevKey(const int index);
    int getNextKey(const int index);
    void fill(const int index);
    void borrowFromPrev(const int border);
    void borrowFromNext(const int border);
    void merge(const int index);
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
    void del(const int key);
};


BNode::BNode(const int t, const bool isLeaf)
{
    this->t = t;
    this->isLeaf = isLeaf;
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
    if (this->isLeaf == true)
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
    if (isLeaf == true)
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
    BNode *newNode = new BNode(node->t, node->isLeaf);
    newNode->currentKeys = t / 2 - 1;
    for (int index = 0; index < t / 2 - 1; index++)
    {
        newNode->key[index] = node->key[index + t / 2];
        newNode->data[index] = node->data[index + t / 2];
    }
    if (node->isLeaf == false)
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

void BNode::remove(const int key)
{
    int index = findKey(key);
    if (index < this->currentKeys && this->key[index] == key)
    {
        if (this->isLeaf == true)
        {
            removeFromLeaf(index);
        }
        else
        {
            removeFromNonLeaf(index);
        }
    }
    else
    {
        if (this->isLeaf == true)
        {
            cout << "There is no data with the key " << key << " in the tree!" << endl;
        }
        else
        {
            bool isNodeFilled = (index == this->currentKeys) ? true : false;
            if (child[index]->currentKeys < t / 2)
            {
                fill(index);
            }
            if (isNodeFilled == true && index > this->currentKeys)
            {
                child[index - 1]->remove(key);
            }
            else
            {
                child[index]->remove(key);
            }
        }
    }
}

void BNode::removeFromLeaf(const int border)
{
    for (int index = border + 1; index < this->currentKeys; index++)
    {
        this->key[index - 1] = this->key[index];
        this->data[index - 1] = this->data[index];
    }
    currentKeys--;
}

void BNode::removeFromNonLeaf(const int index)
{
    int key = this->key[index];
    if (child[index]->currentKeys >= t / 2)
    {
        int prevKey = getPrevKey(index);
        this->key[index] = prevKey;
        this->data[index] = getDataByKey(prevKey);
        child[index]->remove(prevKey);
    }
    else if (child[index + 1]->currentKeys >= t / 2)
    {
        int nextKey = getNextKey(index);
        this->key[index] = nextKey;
        this->data[index] = getDataByKey(nextKey);
        child[index + 1]->remove(nextKey);
    }
    else
    {
        merge(index);
        child[index]->remove(key);
    }
}

int BNode::getPrevKey(const int index)
{
    BNode *currentNode = child[index];
    while (currentNode->isLeaf == false)
    {
        currentNode = currentNode->child[currentNode->currentKeys];
    }
    return currentNode->key[currentNode->currentKeys - 1];
}

int BNode::getNextKey(const int index)
{
    BNode *currentNode = child[index + 1];
    while (currentNode->isLeaf == false)
    {
        currentNode = currentNode->child[0];
    }
    return currentNode->key[0];
}

void BNode::fill(const int index)
{
    if (index != 0 && child[index - 1]->currentKeys >= t / 2)
    {
        borrowFromPrev(index);
    }
    else if (index != currentKeys && child[index + 1]->currentKeys >= t / 2)
    {
        borrowFromNext(index);
    }
    else
    {
        if (index != currentKeys)
        {
            merge(index);
        }
        else
        {
            merge(index - 1);
        }
    }
}

void BNode::borrowFromPrev(const int border)
{
    BNode *childNode = child[border];
    BNode *siblingNode = child[border - 1];
    for (int index = childNode->currentKeys - 1; index >= 0; index--)
    {
        childNode->key[index + 1] = childNode->key[index];
        childNode->data[index + 1] = childNode->data[index];
    }
    if (childNode->isLeaf == false)
    {
        for (int index = childNode->currentKeys; index >= 0; index--)
        {
            childNode->child[index + 1] = childNode->child[index];
        }
    }
    childNode->key[0] = key[border - 1];
    if (childNode->isLeaf == false)
    {
        childNode->child[0] = siblingNode->child[siblingNode->currentKeys];
    }
    key[border - 1] = siblingNode->key[siblingNode->currentKeys - 1];
    data[border - 1] = siblingNode->data[siblingNode->currentKeys - 1];
    childNode->currentKeys++;
    siblingNode->currentKeys--;
}

void BNode::borrowFromNext(const int border)
{
    BNode *childNode = child[border];
    BNode *siblingNode = child[border + 1];
    childNode->key[childNode->currentKeys] = key[border];
    childNode->data[childNode->currentKeys] = data[border];
    if (childNode->isLeaf == false)
    {
        childNode->child[childNode->currentKeys + 1] = siblingNode->child[0];
    }
    key[border] = siblingNode->key[0];
    data[border] = siblingNode->data[0];
    for (int index = 1; index < siblingNode->currentKeys; index++)
    {
        siblingNode->key[index - 1] = siblingNode->key[index];
        siblingNode->data[index - 1] = siblingNode->data[index];
    }
    if (siblingNode->isLeaf == false)
    {
        for (int index = 1; index < siblingNode->currentKeys; index++)
        {
            siblingNode->child[index - 1] = siblingNode->child[index];
        }
    }
    childNode->currentKeys++;
    siblingNode->currentKeys--;
}

void BNode::merge(const int border)
{
    BNode *childNode = child[border];
    BNode *siblingNode = child[border + 1];
    childNode->key[t / 2 - 1] = key[border];
    childNode->data[t / 2 - 1] = data[border];
    for (int index = 0; index < siblingNode->currentKeys; index++)
    {
        childNode->key[index + t / 2] = siblingNode->key[index];
        childNode->data[index + t / 2] = siblingNode->data[index];
    }
    if (childNode->isLeaf == false)
    {
        for (int index = 0; index < siblingNode->currentKeys; index++)
        {
            childNode->child[index + t / 2] = siblingNode->child[index];
        }
    }
    for (int index = border + 1; index < currentKeys; index++)
    {
        key[index - 1] = key[index];
        data[index - 1] = data[index];
    }
    for (int index = border + 2; index <= currentKeys; index++)
    {
        child[index - 1] = child[index];
    }
    childNode->currentKeys += siblingNode->currentKeys + 1;
    currentKeys--;
    delete(siblingNode);
}

void BTree::del(const int key)
{
    if (root == nullptr)
    {
        cout << "The tree is empty!" << endl;
    }
    else
    {
        root->remove(key);
        if (root->currentKeys == 0)
        {
            BNode *temp = root;
            if (root->isLeaf == true)
            {
                root = nullptr;
            }
            else
            {
                root = root->child[0];
            }
            delete temp;
        }
    }
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
    tree.del(5);
    tree.del(11);
    std::cout << tree.find(1) << std::endl;
    std::cout << tree.find(3) << std::endl;
    std::cout << tree.find(6) << std::endl;
    std::cout << tree.find(11) << std::endl;
    return 0;
}
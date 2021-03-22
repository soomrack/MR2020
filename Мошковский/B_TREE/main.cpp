#include <iostream>
using namespace std;

class Node
{
    int* keys;
    Node** children;
    int curr_num;
    int t;
    bool leaf;
public:
    Node(int t, bool leaf);

    void Bypass();

    Node* Search(int key);
    int FindKey(int key);
    void InsertPartial(int key);
    void splitChild(int i, Node* y);
    void Filling(int index);
    void TakePrevious(int index);
    void TakeFollowing(int index);
    void Merge(int index);
    friend class BTree;
};

class BTree
{
    Node* root;
    int t;

public:
    BTree(int t)
    {
        root = nullptr;
        this->t = t;
    }

    void Bypass()
    {
        if (root != nullptr)
        {
            root->Bypass();
        }
    }

    Node* Search(int key)
    {
        return (root == nullptr) ? nullptr : root->Search(key);
    }
};

Node::Node(int t, bool leaf)
{
    this->t = t;
    this->leaf = leaf;

    keys = new int[2 * t - 1];
    children = new Node * [2 * t];

    curr_num = 0;
}

Node* Node::Search(int key)
{
    int i = 0;
    while (i < curr_num && key > keys[i])
        i++;

    if (keys[i] == key)
    {
        return this;
    }

    if (leaf == true)
    {
        return nullptr;
    }

    return children[i]->Search(key);
}

void Node::InsertPartial(int key)
{
    int i = curr_num - 1;

    if (leaf == true)
    {
        while (i >= 0 && keys[i] > key)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = key;
        curr_num = curr_num + 1;
    }
    else
    {
        while (i >= 0 && keys[i] > key)
            i--;

        if (children[i + 1]->curr_num == 2 * t - 1)
        {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < key)
            {
                i++;
            }
        }
        children[i + 1]->InsertPartial(key);
    }
}

void Node::Bypass()
{
    int i;
    for (i = 0; i < curr_num; i++)
    {
        if (leaf == false)
        {
            children[i]->Bypass();
        }
        cout << " " << keys[i];
    }

    if (leaf == false)
    {
        children[i]->Bypass();
    }
}

int Node::FindKey(int key)
{
    int index = 0;
    while (index < curr_num && keys[index] < key)
        ++index;
    return index;
}

void Node::Filling(int index)
{
    if (index != 0 && children[index - 1]->curr_num >= t)
    {
        TakePrevious(index);
    }

    else if (index != curr_num && children[index + 1]->curr_num >= t)
    {
        TakeFollowing(index);
    }

    else
    {
        if (index != curr_num)
        {
            Merge(index);
        }
        else
            Merge(index - 1);
    }
    return;
}

void Node::TakePrevious(int index)
{
    Node* child = children[index];
    Node* neighbor = children[index - 1];

    for (int i = child->curr_num - 1; i >= 0; --i)
    {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->leaf)
    {
        for (int i = child->curr_num; i >= 0; --i)
        {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = keys[index - 1];

    if (!child->leaf)
    {
        child->children[0] = neighbor->children[neighbor->curr_num];
    }

    keys[index - 1] = neighbor->keys[neighbor->curr_num - 1];

    child->curr_num += 1;
    neighbor->curr_num -= 1;

    return;
}

void Node::TakeFollowing(int index)
{
    Node* child = children[index];
    Node* neighbor = children[index + 1];

    child->keys[(child->curr_num)] = keys[index];

    if (!(child->leaf))
    {
        child->children[(child->curr_num) + 1] = neighbor->children[0];
    }

    keys[index] = neighbor->keys[0];

    for (int i = 1; i < neighbor->curr_num; ++i)
    {
        neighbor->keys[i - 1] = neighbor->keys[i];
    }

    if (!neighbor->leaf)
    {
        for (int i = 1; i <= neighbor->curr_num; ++i)
        {
            neighbor->children[i - 1] = neighbor->children[i];
        }
    }

    child->curr_num += 1;
    neighbor->curr_num -= 1;

    return;
}

int main() {
    return 0;
}
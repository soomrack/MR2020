#include <iostream>
using namespace std;

const int t = 2;
const int order = (2 * t - 1);

struct Node
{
    int keys[order];
    Node* child[order + 1];
    Node(int key);
    int number_of_keys;
};

Node::Node(int key)
{
    this->keys[0] = key;
    for (int i = 1; i < (order); i++)
    {
        this->keys[i] = 0;
    }
    for (int i = 0; i < (order + 1); i++)
    {
        this->child[i] = nullptr;
    }
    this->number_of_keys = 1;
}

class Tree
{
private:
    void insert(const int key, Node* node);
    void sort(Node* node);
    Node* search_leaf(int key);
    Node* search_parent(Node* node, Node* root);
    void restruct(Node* node);
    void setup_child(Node* new_child1, Node* new_child2, Node* node);
public:
    Tree()
    {
        root = nullptr;
    }
    Node* root;
    void add_key(int key);
    Node* search_node(int key, Node* root);
    void print_tree(Node* root);

};

void Tree::insert(int key, Node* node)
{
    node->keys[node->number_of_keys] = key;
    node->number_of_keys = node->number_of_keys + 1;
    sort(node);
}

Node* Tree::search_node(int key, Node* root)
{
    {
        for (int i = 0; i < (root->number_of_keys); i++)
        {
            if (root->keys[i] == key)
            {
                return root;
            }
        }
        for (int i = 0; i < (root->number_of_keys); i++)
        {
            if (key < root->keys[i])
            {
                return search_node(key, root->child[i]);
            }
            if ((key > root->keys[i]) && (root->number_of_keys == (i + 1)))
            {
                return search_node(key, root->child[i + 1]);
            }
        }

    }
}

Node* Tree::search_parent(Node* node, Node* root)
{
    for (int i = 0; i < (2 * t); i++)
    {
        if (root->child[i] == node)
        {
            return root;
        }
        if (root->child[i] != nullptr)
        {
            search_parent(node, root->child[i]);
        }
    }
}

Node* Tree::search_leaf(int key)
{
    Node* temp = root;
    while (temp->child[0] != nullptr)
    {
        for (int i = 0; i < (order); i++)
        {
            if (temp->keys[i] != 0)
            {
                if (key < temp->keys[i])
                {
                    temp = temp->child[i];
                    break;
                }
                if ((temp->keys[i + 1] == 0) && (key > temp->keys[i]))
                {
                    temp = temp->child[i + 1];
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    return temp;
}

void Tree::sort(Node* node) {
    int m;
    for (int i = 0; i < (order); i++)
    {
        for (int j = i + 1; j <= (order); j++)
        {
            if ((node->keys[i] != 0) && (node->keys[j] != 0))
            {
                if ((node->keys[i]) > (node->keys[j]))
                {
                    m = node->keys[i];
                    node->keys[i] = node->keys[j];
                    node->keys[j] = m;
                }
            }
            else break;
        }
    }
}

void Tree::setup_child(Node* new_child1, Node* new_child2, Node* node)
{
    for (int i = 0; i < (t - 1); i++)
    {
        new_child1->keys[i] = node->keys[i];
        new_child2->keys[i] = node->keys[i + t];
    }
    new_child1->number_of_keys = t - 1;
    new_child2->number_of_keys = t - 1;

    if (node->child[0] != nullptr)
    {
        for (int i = 0; i <= (t - 1); i++)
        {
            new_child1->child[i] = node->child[i];
            new_child2->child[i] = node->child[i + t];
        }
    }
}

void Tree::add_key(const int key)
{
    if (root == nullptr)
    {
        root = new Node(key);
        return;
    }

    Node* temp = search_leaf(key);

    insert(key, temp);

    Node* temp_parent = search_parent(temp, root);

    while (temp->number_of_keys >= (order))
    {
        if (temp == root)
        {
            restruct(temp);
        }
        else
        {
            restruct(temp);
            temp = temp_parent;
        }
    }
}

void Tree::print_tree(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    for (int i = 0; i < (order); i++)
    {
        if (root->number_of_keys >= i)
        {
            cout << root->keys[i] << ",";
        }
    }
    cout << '\n';
    for (int i = 0; i < (order + 1); i++)
    {
        if (root->child[i] != nullptr)
        {
            print_tree(root->child[i]);
        }
    }
}

int main()
{
    return 0;
}
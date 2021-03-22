#include <iostream>
using namespace std;

const int t = 2;

class Node
{
public:
    int keys[(2 * t - 1)];
    Node* children[(2 * t)];
    int count;
    bool leaf;
    Node(int key);
};

Node::Node(int key)
{
    this->keys[0] = key;
    for (int i = 1; i < (2 * t - 1); i++)
    {
        this->keys[i] = 0;
    }
    for (int i = 0; i < (2 * t); i++)
    {
        this->children[i] = nullptr;
    }
    this->count = 1;
    this->leaf = true;
}



class Tree
{
public:
    Node* root;
    Tree()
    {
        root = nullptr;
    }
    void add_data(int key);
    void print_tree(Node* root);
    void delete_key(int key);
    Node* find_node(int key, Node* root); // returns node that contains key, but key MUST be in tree otherwise case is not handled
private:
    void insert(int key, Node* node);
    void sort_node(Node* node);
    Node* find_leaf_for_insert(int key);
    void restruct(Node* node);
    Node* find_parent(Node* node, Node* root);
    void set_new_chldren_for_node(Node* new_child1, Node* new_child2, Node* node);

};

void Tree::add_data(int key)
{
    if (root == nullptr)
    {
        root = new Node(key);
        return;
    }

    Node* temp = find_leaf_for_insert(key);

    insert(key, temp);

    Node* temp_parent = find_parent(temp, root);

    while (temp->count >= (2 * t - 1))
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

void Tree::insert(int key, Node* node)
{
    node->keys[node->count] = key;
    node->count = node->count + 1;
    sort_node(node);
}

void Tree::sort_node(Node* node)
{
    int temp;
    for (int i = 0; i < (node->count); i++)
    {
        for (int j = i + 1; j < (node->count); j++)
        {
            if (node->keys[i] > node->keys[j])
            {
                temp = node->keys[i];
                node->keys[i] = node->keys[j];
                node->keys[j] = temp;
            }
        }
    }
}

Node* Tree::find_leaf_for_insert(int key)
{
    Node* temp = root;

    while (temp->leaf == false)
    {
        for (int i = 0; i < (2 * t - 1); i++)
        {
            if (temp->keys[i] != 0)
            {
                if (key < temp->keys[i])
                {
                    temp = temp->children[i];
                    break;
                }
                if ((temp->keys[i + 1] == 0) && (key > temp->keys[i]))
                {
                    temp = temp->children[i + 1];
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

void Tree::restruct(Node* node)
{
    Node* new_child1 = new Node(0);
    new_child1->count = 0;

    Node* new_child2 = new Node(0);
    new_child2->count = 0;

    set_new_chldren_for_node(new_child1, new_child2, node);

    if (node == root)
    {
        node->keys[0] = node->keys[t - 1];
        for (int i = 1; i < (2 * t - 1); i++)
        {
            node->keys[i] = 0;
        }
        node->count = 1;
        node->children[0] = new_child1;
        node->children[1] = new_child2;
        for (int i = 2; i < (2 * t); i++)
        {
            node->children[i] = nullptr;
        }
        node->leaf = false;

    }
    else
    {
        Node* parent_node = find_parent(node, root);
        insert(node->keys[t - 1], parent_node);

        for (int i = 0; i < (2 * t); i++)
        {
            if (parent_node->children[i] == node)
            {
                parent_node->children[i] = nullptr;
            }
        }
        for (int i = 0; i < (2 * t); i++)
        {
            if (parent_node->children[i] == nullptr)
            {
                for (int j = (2 * t - 1); j > (i + 1); j--)
                {
                    parent_node->children[j] = parent_node->children[j - 1];
                }
                parent_node->children[i + 1] = new_child2;
                parent_node->children[i] = new_child1;
                break;
            }
        }
        parent_node->leaf = false;
    }
}

Node* Tree::find_parent(Node* node, Node* root)
{

    for (int i = 0; i < (2 * t); i++)
    {
        if (root->children[i] == node)
        {
            return root;
        }
    }

    for (int i = 0; i < (2 * t); i++)
    {
        if (root->children[i] != nullptr)
        {
            find_parent(node, root->children[i]);
        }
    }

}

void Tree::set_new_chldren_for_node(Node* new_child1, Node* new_child2, Node* node)
{
    for (int i = 0; i < (t - 1); i++)
    {
        new_child1->keys[i] = node->keys[i];
        new_child2->keys[i] = node->keys[i + t];
    }
    new_child1->count = t - 1;
    new_child2->count = t - 1;

    if (node->children[0] != nullptr)
    {
        for (int i = 0; i <= (t - 1); i++)
        {
            new_child1->children[i] = node->children[i];
            new_child2->children[i] = node->children[i + t];
        }
        new_child1->leaf = false;
        new_child2->leaf = false;
    }

}

void Tree::print_tree(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    for (int i = 0; i < (2 * t - 1); i++)
    {
        if (root->count > i)
        {
            cout << root->keys[i] << ",";
        }
    }
    cout << '\n';
    for (int i = 0; i < (2 * t); i++)
    {
        if (root->children[i] != nullptr)
        {
            print_tree(root->children[i]);
        }
    }
}

Node* Tree::find_node(int key, Node* root)
{


    for (int i = 0; i < (root->count); i++)
    {
        if (root->keys[i] == key)
        {
            return root;
        }
    }

    for (int i = 0; i < (root->count); i++)
    {
        if (key < root->keys[i])
        {
            return find_node(key, root->children[i]);
        }
        if ((key > root->keys[i]) && (root->count = (i + 1)))
        {
            return find_node(key, root->children[i + 1]);
        }
    }

}

void Tree::delete_key(int key)
{
    Node* node_for_delete = find_node(key, root);

    if ((node_for_delete->leaf == true) && (node_for_delete->count == t)) // если узел был листом и при удалении у него останется t-1 ключей
    {
        for (int i = 0; i < (node_for_delete->count); i++)
        {
            if (node_for_delete->keys[i] == key)
            {
                for (int j = i; j < (node_for_delete->count); j++)
                {
                    node_for_delete->keys[j] = node_for_delete->keys[j + 1];
                }
                node_for_delete->count = node_for_delete->count - 1;
            }
        }
    }
}

int main()
{
    Tree mytree = Tree();
    mytree.add_data(6);
    mytree.add_data(8);
    mytree.print_tree(mytree.root);
    cout << '\n';
    mytree.add_data(10);
    mytree.print_tree(mytree.root);
    cout << '\n';
    mytree.add_data(4);
    mytree.print_tree(mytree.root);
    cout << '\n';
    mytree.add_data(12);
    mytree.print_tree(mytree.root);
    cout << '\n';
    mytree.add_data(14);
    mytree.print_tree(mytree.root);
    cout << '\n';
    mytree.add_data(2);
    mytree.print_tree(mytree.root);
}
#include <iostream>


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
    Node* search_node(int key, Node* root); // возвращает ссылку на узел, который содержит данный ключ
private:
    void insert(int key, Node* node);
    void sort_node(Node* node);
    Node* search_leaf_for_insert(int key);
    void restruct(Node* node);
    Node* search_parent(Node* node, Node* root);
    void setting_new_chldren_for_node(Node* new_child1, Node* new_child2, Node* node);

};

void Tree::add_data(int key)
{
    if (root == nullptr)
    {
        root = new Node(key);
        return;
    }

    Node* temp = search_leaf_for_insert(key);

    insert(key, temp);

    Node* temp_parent = search_parent(temp, root);

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

Node* Tree::search_leaf_for_insert(int key)
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

    setting_new_chldren_for_node(new_child1, new_child2, node);

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
        Node* parent_node = search_parent(node, root);
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

Node* Tree::search_parent(Node* node, Node* root)
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
            search_parent(node, root->children[i]);
        }
    }

}

void Tree::setting_new_chldren_for_node(Node* new_child1, Node* new_child2, Node* node)
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






int main()
{
    Tree test_tree;

    test_tree.add_data(15);
    test_tree.add_data(19);
    test_tree.add_data(21);
    test_tree.add_data(20);
    test_tree.add_data(22); 
    test_tree.add_data(25); 
    test_tree.add_data(30); 
    test_tree.add_data(27); 
    test_tree.add_data(2); 
    return 0;
}
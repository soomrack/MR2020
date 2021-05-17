#include <iostream>

using namespace std;

const auto btree_degree = 2;

class BNode
{
public:
    int keys[2 * btree_degree - 1];
    BNode *child[2 * btree_degree];
    int keys_counter;
public:
    BNode(int key);
    ~BNode();
};

BNode::BNode(int key)
{
    this->keys[0] = key;
    for (int i = 1; i < (2 * btree_degree-1); i++)
    {
        this->keys[i] = 0;
    }
    for (int i = 0; i < (2 * btree_degree); i++)
    {
        this->child[i] = nullptr;
    }
    this->keys_counter = 1;
}

class BTree
{
public:
    BNode *root;
    void add_data(int key);
    void delete_data(int key);
    void print_tree(BNode *root);
    BNode *search_node(BNode *root, int key);
    BTree();
private:
    void insert_to_node(BNode *node, int key);
    void sort(BNode *node);
    void rebuild_node(BNode *node);
    void setting_new_children_for_node(BNode *first_child, BNode *second_child, BNode *node);
    BNode *search_leaf(int key);
    BNode *search_parent(BNode *node, BNode *root);
};

BTree::BTree()
{
    root = nullptr;
}

void BTree::add_data(const int key)
{
    if (root != nullptr)
    {
        BNode *temp = search_leaf(key);
        insert_to_node(temp, key);
        BNode *temp_parent = search_parent(temp, root);
        while (temp->keys_counter >= (2 * btree_degree - 1))
        {
            if (temp == root)
            {
                rebuild_node(temp);
            }
            else
            {
                rebuild_node(temp);
                temp = temp_parent;
            }
        }
    }
    else
    {
        root = new BNode(key);
        return;
    }
}

void BTree::delete_data(int key)
{
    BNode *deletedNode = search_node(root, key);
    if ((deletedNode->child[0] == nullptr) && (deletedNode->keys_counter == btree_degree))
    {
        for (int i = 0; i < (deletedNode->keys_counter); i++)
        {
            if (deletedNode->keys[i] == key)
            {
                for (int j = i; j < (deletedNode->keys_counter); j++)
                {
                    deletedNode->keys[j] = deletedNode->keys[j + 1];
                }
                deletedNode->keys_counter = deletedNode->keys_counter - 1;
            }
        }
    }
}

void BTree::print_tree(BNode* root)
{
    if (root != nullptr)
    {
        for (int i = 0; i < (2 * btree_degree - 1); i++)
        {
            if (root->keys_counter >= i)
            {
                cout << root->keys[i] << " ";
            }
        }
        cout << '\n';
        for (int i = 0; i < (2 * btree_degree); i++)
        {
            if (root->child[i] != nullptr)
            {
                print_tree(root->child[i]);
            }
        }
        cout << '\n';
    }
}

BNode *BTree::search_node(BNode *root, int key)
{
    if (root != nullptr)
    {
        for (int i = 0; i < (root->keys_counter); i++)
        {
            if (root->keys[i] == key)
            {
                return root;
            }
            if (key < root->keys[i])
            {
                return search_node(root->child[i], key);
            }
            if ((key > root->keys[i]) && (root->keys_counter == (i + 1)))
            {
                return search_node(root->child[i + 1], key);
            }
        }
    }
}

void BTree::insert_to_node(BNode *node, int key)
{
    node->keys[node->keys_counter] = key;
    node->keys_counter = node->keys_counter + 1;
    sort(node);
}

void BTree::sort(BNode* node)
{
    int swap;
    for (int i = 0; i < (2 * btree_degree - 1); i++)
    {
        for (int j = i + 1; j <= (2 * btree_degree - 1); j++)
        {
            if ((node->keys[i] != 0) && (node->keys[j] != 0))
            {
                if ((node->keys[i]) > (node->keys[j]))
                {
                    swap = node->keys[i];
                    node->keys[i] = node->keys[j];
                    node->keys[j] = swap;
                }
            }
            else break;
        }
    }
}

void BTree::rebuild_node(BNode* node)
{
    BNode *first_child = new BNode(0);
    first_child->keys_counter = 0;

    BNode *second_child = new BNode(0);
    second_child->keys_counter = 0;

    setting_new_children_for_node(first_child, second_child, node);
    if (node == root)
    {
        node->keys[0] = node->keys[btree_degree - 1];
        for (int i = 1; i < (2 * btree_degree - 1); i++)
        {
            node->keys[i] = 0;
        }
        node->keys_counter = 1;
        node->child[0] = first_child;
        node->child[1] = second_child;

        for (int i = 2; i < (2 * btree_degree); i++)
        {
            node->child[i] = nullptr;
        }
    }
    else
    {
        BNode *parent_node = search_parent(node, root);
        insert_to_node(parent_node, node->keys[btree_degree - 1]);

        for (int i = 0; i < (2 * btree_degree); i++)
        {
            if (parent_node->child[i] == node)
            {
                parent_node->child[i] = nullptr;
            }
            if (parent_node->child[i] == nullptr)
            {
                for (int j = (2 * btree_degree - 1); j > (i + 1); j--)
                {
                    parent_node->child[j] = parent_node->child[j - 1];
                }
                parent_node->child[i] = first_child;
                parent_node->child[i + 1] = second_child;
                break;
            }
        }
    }
}

void BTree::setting_new_children_for_node(BNode *first_child, BNode *second_child, BNode *node)
{
    for (int i = 0; i < (btree_degree - 1); i++)
    {
        first_child->keys[i]  = node->keys[i];
        second_child->keys[i] = node->keys[i + btree_degree];
    }
    first_child->keys_counter  = btree_degree - 1;
    second_child->keys_counter = btree_degree - 1;
    if (node->child[0] != nullptr)
    {
        for (int i = 0; i <= (btree_degree - 1); i++)
        {
            first_child->child[i]  = node->child[i];
            second_child->child[i] = node->child[i + btree_degree];
        }
    }
}

BNode* BTree::search_parent(BNode *node, BNode *root)
{
    for (int i = 0; i < (2 * btree_degree); i++)
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

BNode* BTree::search_leaf(int key)
{
    BNode *temp = root;
    while (temp->child[0] != nullptr)
    {
        for (int i = 0; i < (2 * btree_degree - 1); i++)
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
            else break;
        }
    }
    return temp;
}

int main()
{
    BTree BtreeTest = BTree();
    BtreeTest.add_data(3);
    BtreeTest.add_data(4);
    BtreeTest.add_data(12);
    BtreeTest.print_tree(BtreeTest.root);
    BtreeTest.add_data(19);
    BtreeTest.print_tree(BtreeTest.root);
    BtreeTest.add_data(3);
    BtreeTest.print_tree(BtreeTest.root);
    BtreeTest.add_data(70);
    BtreeTest.print_tree(BtreeTest.root);
    BtreeTest.delete_data(6);
    BtreeTest.print_tree(BtreeTest.root);
    BtreeTest.add_data(22);
    BtreeTest.print_tree(BtreeTest.root);
    return 0;
}
#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    void* data;
    Node* left_child;
    Node* right_child;
public:
    Node(int key, void* data);
    ~Node() {};
};

Node::Node(const int key, void* data)
{
    this->key = key;
    this->data = data;
    left_child = nullptr;
    right_child = nullptr;
}

class Tree
{
public:
    Node* root;
public:
    Tree()
    {
        root = nullptr;
    }
    ~Tree() {};
private:
    Node* search_parent_for_new_node(int key, Node* node);
    Node* find_node(const int key, Node* node);
    Node* min_node(Node* node);
    Node* search_node_to_delete(int key_to_delete, Node* node);
    Node* search_parent_to_delete(int key_to_delete, Node* node);
public:
    int add_data(int key, void* data);
    void print_tree(Node* node);
    void search_data(const int key);
    int delete_data(int key_to_delete);
};


Node* Tree::search_parent_for_new_node(int key, Node* node)
{
    if (node->key >= key)
    {
        if (node->left_child == nullptr) return node;
        return search_parent_for_new_node(key, node->left_child);
    }
    else
    {
        if (node->right_child == nullptr) return node;
        return search_parent_for_new_node(key, node->right_child);
    }

    return nullptr;
}

int Tree::add_data(int key, void* data)
{
    Node* child = new Node(key, data);

    if (root == nullptr)
    {
        root = child;
        return 1;
    }

    Node* parent = search_parent_for_new_node(key, root);

    if (key <= parent->key)
    {
        parent->left_child = child;
    }
    else
    {
        parent->right_child = child;
    }

    return 1;
}

void Tree::print_tree(Node* node)
{
    if (node == nullptr)
        return;

    cout << node->key << " ";

    print_tree(node->left_child);
    print_tree(node->right_child);

    return;
}

Node* Tree::find_node(const int wanted_key, Node* node)
{
    Node* result = nullptr;

    if (node == nullptr)
        return result;

    if (wanted_key == node->key)
        result = node;
    else if (wanted_key > node->key)
        result = find_node(wanted_key, node->right_child);
    else
        result = find_node(wanted_key, node->left_child);

    return result;
}

void Tree::search_data(const int wanted_key)
{
    if (root == nullptr)
        return;
    if (wanted_key == root->key)
    {
        cout << "Искомое значение: " << wanted_key << ". " << "Найдено: " << root->key;
        return;
    }

    Node* result = nullptr;

    if (wanted_key > root->key)
        result = find_node(wanted_key, root->right_child);
    else
        result = find_node(wanted_key, root->left_child);

    if (result == nullptr)
        cout << "Искомое значение: " << wanted_key << ". " << "Не найдено :(";
    else
        cout << "Искомое значение: " << wanted_key << ". " << "Найдено: " << result->key;

    return;
}

Node* Tree::min_node(Node* node)
{
    Node* min = node;
    while (min->left_child != nullptr)
    {
        min = min->left_child;
    }

    return min;
}

Node* Tree::search_node_to_delete(int key_to_delete, Node* node)
{
    if (node == nullptr)
        return node;

    if (key_to_delete == node->key)
        return node;
    else if (key_to_delete < node->key)
        return search_node_to_delete(key_to_delete, node->left_child);
    else if (key_to_delete > node->key)
        return search_node_to_delete(key_to_delete, node->right_child);

    return node;
}

Node* Tree::search_parent_to_delete(int key_to_delete, Node* node)
{
    if (node == nullptr)
        return node;

    if (key_to_delete < node->key)
    {
        if ((node->left_child != nullptr) && ((node->left_child)->key == key_to_delete))
        {
            return node;
        }
        return search_parent_to_delete(key_to_delete, node->left_child);
    }
    else if (key_to_delete > node->key)
    {
        if ((node->right_child != nullptr) && ((node->right_child)->key == key_to_delete))
        {
            return node;
        }
        return search_parent_to_delete(key_to_delete, node->right_child);
    }

    return node;
}

int Tree::delete_data(int key_to_delete)
{
    Node* node_to_delete = search_node_to_delete(key_to_delete, root);
    Node* parent_to_delete = search_parent_to_delete(key_to_delete, root);

    if ((node_to_delete->left_child != nullptr) && (node_to_delete->right_child != nullptr))
    {
        Node* left_ntd = node_to_delete->left_child;
        Node* right_ntd = node_to_delete->right_child;

        Node* successor = min_node(node_to_delete->right_child);
        Node* s_parent = search_parent_to_delete(successor->key, node_to_delete->right_child);
        Node* s_right_child = successor->right_child;

        if (key_to_delete < parent_to_delete->key)
        {
            parent_to_delete->left_child = successor;
            successor->left_child = left_ntd;
        }
        else if (key_to_delete > parent_to_delete->key)
        {
            parent_to_delete->right_child = successor;
            successor->left_child = left_ntd;
        }
        else if (key_to_delete == parent_to_delete->key)
        {
            root = successor;
            successor->left_child = left_ntd;
        }

        if (successor->key != right_ntd->key)
        {
            successor->right_child = right_ntd;
        }
        if (successor->key != s_parent->key)
        {
            s_parent->left_child = s_right_child;
        }

        delete node_to_delete;

        return 1;
    }

    if ((node_to_delete->left_child != nullptr) && (node_to_delete->right_child == nullptr))
    {
        Node* left_ntd = node_to_delete->left_child;

        if (key_to_delete < parent_to_delete->key)
        {
            parent_to_delete->left_child = left_ntd;
        }
        else if (key_to_delete > parent_to_delete->key)
        {
            parent_to_delete->right_child = left_ntd;
        }

        delete node_to_delete;

        return 1;
    }

    if ((node_to_delete->right_child != nullptr) && (node_to_delete->left_child == nullptr))
    {
        Node* right_ntd = node_to_delete->right_child;

        if (key_to_delete < parent_to_delete->key)
        {
            parent_to_delete->left_child = right_ntd;
        }
        else if (key_to_delete > parent_to_delete->key)
        {
            parent_to_delete->right_child = right_ntd;
        }

        delete node_to_delete;

        return 1;
    }

    if (key_to_delete < parent_to_delete->key)
    {
        parent_to_delete->left_child = nullptr;
    }
    else if (key_to_delete > parent_to_delete->key)
    {
        parent_to_delete->right_child = nullptr;
    }

    delete node_to_delete;

    return 1;
}


int main() {

    return 0;
}

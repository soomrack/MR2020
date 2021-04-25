#include <iostream>
#include <string>

const int number_of_pointers = 3;
const int empty_key = 2147483647;


class Node {
public:
    int array_of_keys[number_of_pointers - 1];
    std::string array_of_data[number_of_pointers - 1];

    Node* array_of_pointers[number_of_pointers];

    Node();
    ~Node();
};

class Tree {
private:
    Node* root;
    bool is_Node_full(Node* root);
    int find_child_index(Node* root, int key);
    int find_index(Node* current_Node, int key);
    void adding(Node* root, int key, std::string data);
    bool is_Node_leaf(Node* root);
    int amount_of_keys(Node* current_Node);
    void split(Node* parent, Node* child);
    std::string get_Node_data(Node* current_Node, int key);
    Node* get_parent(Node* current_Node, int key, Node* parent);
    Node* get_Node_by_key(Node* root, int key);
    void deleting(Node* NodeWithDeletedKey, int key, Node* parent);
    void delete_key_from_node(Node* current_Node, int key);
    void merge(Node* left_Node, Node* right_Node, Node* parent, int index);
    void rebalance_leaf(Node* current_Node, int keysNum, int index, Node* parent);
public:
    bool add(const int key, std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() 
{
    for (int counter = 0; counter <= (number_of_pointers - 2); counter ++)
    {      
        array_of_data[counter] = "";
        array_of_pointers[counter] = nullptr;
        array_of_keys[counter] = empty_key;
    }
    array_of_pointers[number_of_pointers - 1] = nullptr;
}

Node::~Node()
{
    delete array_of_pointers[number_of_pointers - 1];
}

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree() 
{
    delete root;
}

bool Tree::is_Node_leaf(Node* root)
{
    for (int counter = 0; counter <= number_of_pointers - 1; counter++)
    {
        if (root -> array_of_pointers[counter] != nullptr)
        {
            return false;
        }
    }
    return true;
}

bool Tree::is_Node_full(Node* root)
{
    if (root -> array_of_keys[number_of_pointers - 2] == empty_key)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Tree::adding(Node* node, int key, std::string data)
{
    int index = find_child_index(node, key);
    if (is_Node_leaf(node) == true)
    {
        Node* child = new Node();
        node -> array_of_pointers[index] = child;
        child -> array_of_data[0] = data;
        child -> array_of_keys[0] = key;
        split(node, child);
        return;
    }
    return adding(node -> array_of_pointers[index], key, data);
}

std::string Tree::find(const int key) 
{
    std::string data = get_Node_data(root, key);
    return data;
}

int Tree::amount_of_keys(Node* current_Node)
{
    int number = 0;
    for (int counter = 0; counter <= (number_of_pointers - 2); counter ++)
    {
        if (current_Node -> array_of_keys[counter] != empty_key)
        {
            number++;
        }
    }
    return number;
}

bool Tree::add(const int key, std::string data)
{
    if (get_Node_data(root, key) != "")
    {
        return false;
    }
    if (root == nullptr)
    {
        root = new Node();
        root -> array_of_keys[0] = key;
        root -> array_of_data[0] = data;
        return true;
    }
    adding(root, key, data);
    return true;
}

void Tree::split(Node* parent, Node* child) 
{
    int index = find_child_index(parent, child->array_of_keys[0]);
    if (is_Node_full(parent) == false)
    {
        parent->array_of_keys[number_of_pointers - 2] = child -> array_of_keys[0];
        parent->array_of_data[number_of_pointers - 2] = child -> array_of_data[0];
        parent -> array_of_pointers[index] = child -> array_of_pointers[0];
        parent -> array_of_pointers[number_of_pointers - 1] = child -> array_of_pointers[1];
        for (int counter = index; counter <= (number_of_pointers - 3); counter ++)
        {
            std::swap(parent -> array_of_keys[counter], parent -> array_of_keys[number_of_pointers - 2]);
            std::swap(parent -> array_of_data[counter], parent -> array_of_data[number_of_pointers - 2]);
            std::swap(parent -> array_of_pointers[counter + 1], parent-> array_of_pointers[number_of_pointers - 1]);
        }
        delete child;
        return;
    }

    int temporary_array[number_of_pointers];
    std::string temporary_array_data[number_of_pointers];
    Node* temporary_array_pointers[number_of_pointers + 1];
    for (int counter_2 = 0; counter_2 <= (number_of_pointers - 2); counter_2++)
    {
        temporary_array[counter_2] = parent -> array_of_keys[counter_2];
        temporary_array_data[counter_2] = parent -> array_of_data[counter_2];
        temporary_array_pointers[counter_2] = parent -> array_of_pointers[counter_2];
    }

    temporary_array_pointers[number_of_pointers - 1] = parent -> array_of_pointers[number_of_pointers - 1];
    temporary_array_pointers[index] = child -> array_of_pointers[0];
    temporary_array[number_of_pointers - 1] = child -> array_of_keys[0];
    temporary_array_data[number_of_pointers - 1] = child -> array_of_data[0];
    temporary_array_pointers[number_of_pointers] = temporary_array_pointers[1];

    for (int counter_3 = index; counter_3 <= (number_of_pointers - 2); counter_3++)
    {
        std::swap(temporary_array[counter_3], temporary_array[number_of_pointers - 1]);
        std::swap(temporary_array_data[counter_3], temporary_array_data[number_of_pointers - 1]);
        std::swap(temporary_array_pointers[counter_3 + 1], temporary_array_pointers[number_of_pointers]);
    }

    Node* left = new Node();
    Node* right = new Node();
    int mid;
    if ((number_of_pointers % 2) == 1)
    {
        mid = (number_of_pointers - 1) / 2;
    }
    else 
    {
        if (index < (number_of_pointers / 2))
        {
            mid = number_of_pointers / 2;
        }
        else
        {
            mid = ((number_of_pointers / 2) - 1);
        }
    }

    for (int counter_4 = 0; counter_4 <= (mid - 1); counter_4++)
    {
        left -> array_of_keys[counter_4] = temporary_array[counter_4];
        left -> array_of_data[counter_4] = temporary_array_data[counter_4];
        left -> array_of_pointers[counter_4] = temporary_array_pointers[counter_4];
    }

    left -> array_of_pointers[mid] = temporary_array_pointers[mid];
    for (int counter_5 = mid + 1; counter_5 <= (number_of_pointers - 1); counter_5++)
    {
        right -> array_of_keys[counter_5 - (mid + 1)] = temporary_array[counter_5];
        right -> array_of_data[counter_5 - (mid + 1)] = temporary_array_data[counter_5];
        right -> array_of_pointers[counter_5 - (mid + 1)] = temporary_array_pointers[counter_5];
    }

    right->array_of_pointers[number_of_pointers - (mid + 1)] = temporary_array_pointers[number_of_pointers];
    int tempMid = temporary_array[mid];
    std::string tempMidData = temporary_array_data[mid];
    for (int counter_6 = 0; counter_6 <= (number_of_pointers - 2); counter_6++)
    {
        parent -> array_of_keys[counter_6] = empty_key;
        parent -> array_of_data[counter_6] = "";
        parent -> array_of_pointers[counter_6] = nullptr;
    }

    parent -> array_of_pointers[number_of_pointers - 1] = nullptr;
    parent -> array_of_keys[0] = tempMid;
    parent -> array_of_data[0] = tempMidData;
    parent -> array_of_pointers[0] = left;
    parent -> array_of_pointers[1] = right;
    Node* grandpa = get_parent(root, parent -> array_of_keys[0], root);
    delete child;
    if (parent == root)
    {
        return;
    }
    return split(grandpa, parent);
}

int Tree::find_index(Node* current_Node, int key)
{
    int index = 0;
    for (int counter = 0; counter <= (number_of_pointers - 2); counter++)
    {
        if (current_Node->array_of_keys[counter] == key)
        {
            return index;
        }
        index++;
    }
}

int Tree::find_child_index(Node* root, int key)
{
    int index = 0;
    for (int counter = 0; counter <= (number_of_pointers - 2); counter++)
    {
        if (root -> array_of_keys[counter] <= key)
        {
            index = counter + 1;
        }
        if (root-> array_of_keys[counter] > key)
        {
            break;
        }
    }
    return index;
}

std::string Tree::get_Node_data(Node* current_Node, int key)
{
    int index = find_child_index(current_Node, key);
    if (index != 0) {
        if (current_Node -> array_of_keys[index - 1] == key)
        {
            return current_Node -> array_of_data[index - 1];
        }
    }
    if (is_Node_leaf(current_Node) == true)
    {
        return "";
    }
    return get_Node_data(current_Node -> array_of_data[index], key);
}

Node* Tree::get_parent(Node* current_Node, int key, Node* parent) 
{
    Node* father = parent;
    if (current_Node == root)
    {
        father = nullptr;
    }
    int index = find_child_index(current_Node, key);
    if (index != 0) 
    {
        if (current_Node ->array_of_keys[index - 1] == key)
        {
            return father;
        }
    }
    return get_parent(current_Node -> array_of_pointers[index], key, current_Node);
}

Node* Tree::get_Node_by_key(Node* root, int key) 
{
    Node* current_Node = root;
    int index = find_child_index(root, key);
    if (current_Node -> array_of_keys[index - 1] == key)
    {
        return current_Node;
    }
    return get_Node_by_key(current_Node -> array_of_pointers[index], key);
}

void Tree::delete_key_from_node(Node* current_Node, int key)
{
    int index = 0;
    for (int counter = 0; counter <= (number_of_pointers - 2); counter++)
    {
        if (current_Node -> array_of_keys[counter] == key)
        {
            current_Node -> array_of_keys[counter] = empty_key;
            current_Node -> array_of_data[counter] = "";
            current_Node -> array_of_pointers[counter + 1] = nullptr;
            break;
        }
        index++;
    }
    for (int counter_2 = index; counter_2 <= (number_of_pointers - 3); counter_2++)
    {
        std::swap(current_Node -> array_of_keys[counter_2], current_Node -> array_of_keys[counter_2 + 1]);
        std::swap(current_Node -> array_of_data[counter_2], current_Node -> array_of_data[counter_2 + 1]);
        std::swap(current_Node -> array_of_pointers[counter_2 + 1], current_Node -> array_of_pointers[counter_2 + 2]);
    }
}

void Tree::merge(Node* left_Node, Node* right_Node, Node* parent, int index) 
{
    int keysNum = amount_of_keys(left_Node);
    left_Node -> array_of_keys[keysNum] = parent -> array_of_keys[index - 1];
    left_Node -> array_of_data[keysNum] = parent -> array_of_data[index - 1];
    left_Node -> array_of_pointers[keysNum + 1] = right_Node -> array_of_pointers[0];
    int rightKeysNum = amount_of_keys(right_Node);
    int counter_1 = 0;
    for (int counter_2 = keysNum + 1; counter_2 <= (keysNum + rightKeysNum); counter_2++)
    {
        left_Node -> array_of_keys[counter_2] = right_Node -> array_of_keys[counter_1];
        left_Node -> array_of_data[counter_2] = right_Node -> array_of_data[counter_1];
        left_Node -> array_of_pointers[counter_2 + 1] = right_Node -> array_of_pointers[counter_1 + 1];
        counter_1 ++;
    }
    delete_key_from_node(parent, parent -> array_of_keys[index - 1]);
}

void Tree::rebalance_leaf(Node* current_Node, int keysNum, int index, Node* parent) {
    if (current_Node == root)
        return;
    Node* left_brother = root;
    Node* right_brother = root;
    if (index != 0) {
        left_brother = parent->array_of_pointers[index - 1];
        int leftKeysNum = amount_of_keys(left_brother);
        if (leftKeysNum >= (number_of_pointers / 2)) {
            int tempKey = left_brother -> array_of_keys[leftKeysNum - 1];
            std::string tempData = left_brother -> array_of_data[leftKeysNum - 1];
            current_Node -> array_of_keys[keysNum] = parent -> array_of_keys[index - 1];
            current_Node -> array_of_data[keysNum] = parent -> array_of_data[index - 1];
            for (int counter = keysNum; counter > 0; counter ++) {
                std::swap(current_Node -> array_of_keys[keysNum], current_Node -> array_of_keys[keysNum - 1]);
                std::swap(current_Node -> array_of_data[keysNum], current_Node -> array_of_data[keysNum - 1]);
            }
            parent -> array_of_keys[index - 1] = tempKey;
            parent -> array_of_data[index - 1] = tempData;
            left_brother -> array_of_keys[leftKeysNum - 1] = empty_key;
            left_brother -> array_of_data[leftKeysNum - 1] = "";
            return;
        }
    }

    if (index != number_of_pointers - 1) {
        right_brother = parent->array_of_pointers[index + 1];
        int rightKeysNum = amount_of_keys(right_brother);
        if (rightKeysNum >= (number_of_pointers / 2)) {
            int tempKey = right_brother-> array_of_keys[0];
            std::string tempData = left_brother-> array_of_data[0];
            current_Node -> array_of_keys[keysNum] = parent -> array_of_keys[index + 1];
            current_Node -> array_of_data[keysNum] = parent -> array_of_data[index + 1];
            parent -> array_of_keys[index + 1] = tempKey;
            parent -> array_of_data[index + 1] = tempData;
            delete_key_from_node(right_brother, right_brother -> array_of_keys[0]);
            return;
        }
    }

    Node* grandpa = get_parent(root, parent -> array_of_keys[0], root);
    if (index != 0)
        merge(left_brother, current_Node, parent, index);
    else
        merge(current_Node, right_brother, parent, index + 1);
    int parKeysNum = amount_of_keys(parent);
    if (parKeysNum < (number_of_pointers / 2)) {
        if (parent == root) //временная мера
            return;
        int parIndex = find_child_index(grandpa, parent -> array_of_keys[0]);
        return rebalance_leaf(parent, parKeysNum, parIndex, grandpa);
    }
}

void Tree::deleting(Node* Node_and_deleted_Key, int key, Node* parent) {
    if (is_Node_leaf(Node_and_deleted_Key) == true) {
        if (Node_and_deleted_Key == root) {
            delete_key_from_node(Node_and_deleted_Key, key);
            return;
        }

        int number_of_keys = amount_of_keys(Node_and_deleted_Key);
        if (number_of_keys >= (number_of_pointers / 2)) {
            delete_key_from_node(Node_and_deleted_Key, key);
            return;
        }

        else {
            int index = 0;
            for (int counter = 0; counter <= (number_of_pointers - 1); counter ++) {
                if (parent->array_of_pointers[counter] == Node_and_deleted_Key) {
                    index = counter;
                    break;
                }
            }
            delete_key_from_node(Node_and_deleted_Key, key);
            rebalance_leaf(Node_and_deleted_Key, number_of_keys, index, parent);
            return;
        }
    }

    if (is_Node_leaf(Node_and_deleted_Key) == false) {
        int index = find_index(Node_and_deleted_Key, key);
        Node* leftChild = root;
        Node* rightChild = root;
        if (Node_and_deleted_Key-> array_of_pointers[index] != nullptr) {
            leftChild = Node_and_deleted_Key-> array_of_pointers[index];
            int childKeys = amount_of_keys(leftChild);
            Node_and_deleted_Key-> array_of_keys[index] = leftChild -> array_of_keys[childKeys - 1];
            Node_and_deleted_Key-> array_of_data[index] = leftChild -> array_of_data[childKeys - 1];
            return deleting(leftChild, leftChild->array_of_keys[childKeys - 1], Node_and_deleted_Key);
        }
        if (Node_and_deleted_Key->array_of_pointers[index + 1] != nullptr) {
            rightChild = Node_and_deleted_Key->array_of_pointers[index + 1];
            Node_and_deleted_Key-> array_of_keys[index] = rightChild -> array_of_keys[0];
            Node_and_deleted_Key-> array_of_data[index] = rightChild -> array_of_data[0];
            return deleting(rightChild, rightChild -> array_of_keys[0], Node_and_deleted_Key);
        }
        delete_key_from_node(Node_and_deleted_Key, key);
        return;
    }
}

bool Tree::del(const int key) {
    Node* NodeWithDeletedKey = get_Node_by_key(root, key);
    Node* parent = get_parent(root, key, root);
    deleting(NodeWithDeletedKey, key, parent);
    return true;
}

int main() 
{
    return 0;
}


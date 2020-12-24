#include <iostream>
using namespace std;

class Node
{
public:
    int key;             // Ключ, т.е. метка, по которой осуществляется поиск данных в дереве
    void* data;          // Данные
    Node* left_child;    // Указатель на левого потомка
    Node* right_child;   // Указатель на правого потомка
public:
    Node(int key, void* data);
    ~Node() {};
};

Node::Node(const int key, void* data)    // Функция для формирования узла
{
    this->key = key;          //    Please help me
    this->data = data;        //    I am losing my mind
    left_child = nullptr;     //    RLS
    right_child = nullptr;    //    Robert Laurel Smith
}                             //    head of development Department

class Tree
{
public:
    Node* root;    // Указатель на корень
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
    if (node->key >= key)    // Если ключ текущего узла меньше или равен ключю корня
    {
        if (node->left_child == nullptr) return node;    // Если у корня отсутствует левый потомок, то возвращаем корень
        return search_parent_for_new_node(key, node->left_child);    // Если у корня есть левый потомок, то принимаем его за родителя и продолжаем поиск
    }
    else    // Иначе, т.е. если ключ текущего узла больше ключа корня
    {
        if (node->right_child == nullptr) return node;    // Если у корня отсутствует правый потомок, то аозвращаем корень
        return search_parent_for_new_node(key, node->right_child);    // Если у корня есть правый потомок, то принимаем его за родителя и продолжаем поиск
    }

    return nullptr;
}

int Tree::add_data(int key, void* data)
{
    Node* child = new Node(key, data);    // Создание нового узла

    if (root == nullptr)    // Если корень отсутствует, то принимаем новый узел за него
    {
        root = child;
        return 1;
    }

    Node* parent = search_parent_for_new_node(key, root);

    if (key <= parent->key)    // Если ключ текущего узла меньше или равен ключу найденного родителя
    {
        parent->left_child = child;    // Помещение "потомственного" узла слева
    }
    else
    {
        parent->right_child = child;    // Иначе, помещение "потомственного" узла справа
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

    if ((node_to_delete->left_child != nullptr) && (node_to_delete->right_child != nullptr))    // Если у удаляемого узла имеются оба потомка
    {
        Node* left_ntd = node_to_delete->left_child;
        Node* right_ntd = node_to_delete->right_child;

        Node* successor = min_node(node_to_delete->right_child);    // В качестве наследника выбираем минимальный элемент правого поддерева удаляемого узла
        Node* s_parent = search_parent_to_delete(successor->key, node_to_delete->right_child);    // Поиск родителя наследника
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

    if ((node_to_delete->left_child != nullptr) && (node_to_delete->right_child == nullptr))    // Если у удаляемого узла имеется только левый потомок
    {
        Node* left_ntd = node_to_delete->left_child;

        if (key_to_delete < parent_to_delete->key)
        {
            parent_to_delete->left_child = left_ntd;    // Замена левого потомка родителя удаляемого узла на левого потомка удаляемого узла
        }
        else if (key_to_delete > parent_to_delete->key)
        {
            parent_to_delete->right_child = left_ntd;    // Замена правого потомка, если удаляемый узел был расположен справа
        }

        delete node_to_delete;

        return 1;
    }

    if ((node_to_delete->right_child != nullptr) && (node_to_delete->left_child == nullptr))    // Если у удаляемого узла имеется только правый потомок
    {
        Node* right_ntd = node_to_delete->right_child;

        if (key_to_delete < parent_to_delete->key)
        {
            parent_to_delete->left_child = right_ntd;    // Замена правого потомка родителя удаляемого узла на правого потомка удаляемого узла
        }
        else if (key_to_delete > parent_to_delete->key)
        {
            parent_to_delete->right_child = right_ntd;    // Замена левого потомка, если удаляемый узел был расположен слева
        }

        delete node_to_delete;

        return 1;
    }

    if (key_to_delete < parent_to_delete->key)    // Если у удаляемого узла нет потомков
    {
        parent_to_delete->left_child = nullptr;    // Обнуление одной из ссылок в родительском узле
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

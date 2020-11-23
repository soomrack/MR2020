#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int key;
    string data;

    Node *left;
    Node *right;

    Node();
    Node(const int key, const string data);
    Node(const int key, const string data, Node *left, Node *right);
};

class Tree
{
private:
    Node* root;
public:

    bool add(const int key, const string data);             // false if key already exists
    void add(const int key, const string data, Node* leaf);
    bool del(const int key);                                // false if no key
    string find(const int key);                             // return "" if no key

    Node* find(int key, Node* leaf);
    Node* find_min(Node* ptr);

    bool add(int key);
    bool add(int key, Node* leaf);

    Tree();
    ~Tree();

private:
    void del_tree(Node* leaf);
};

Node::Node(const int key, const string data)
{
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const string data, Node *left, Node *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    del_tree(root);
}

Node* Tree::find_min(Node* ptr) //Поиск узла с минимальным ключом в дереве
{
    return ptr->left ? find_min(ptr->left) : ptr;
}

void Tree::del_tree(Node *leaf)
{
    if(leaf!=nullptr)		    //Елси дерево не пустое
    {
        del_tree(leaf->left);
        del_tree(leaf->right);
        delete leaf;
    }
}

bool Tree::add(const int key, const string data)
{
    if (find(key) != "")
        return false;
    else
    {
        if (root != nullptr)            //если дерево не пустое
            add(key, data, root);       //рекурсивная функции для добавления элемента
        else                            //иначе добавить элемент в корень
            root = new Node(key, data);
        return true;
    }
}

void Tree::add(const int key, const string data, Node *leaf)
{
    if (key < leaf->key)
    {
        if (leaf->left != nullptr)
            add(key, data, leaf->left);         //Добавляем узел, если левый лист последний
        else
            leaf->left = new Node(key, data);   //Иначе идем дальше по ветке
    }
    else if (key >= leaf->key)
    {
        if (leaf->right != nullptr)
            add(key, data, leaf->right);
        else
            leaf->right = new Node(key, data);
    }
}


string Tree::find(const int key)
{
    if (find(key, root) == nullptr)
        return "";
    else  //если дерево не пустое, то запускается рекурсиваня функции для поиска
        return find(key,root)->data;
}

Node* Tree::find(int key, Node* leaf)
{
    if (leaf != nullptr)
    {
        if (key == leaf->key)
            return leaf;
        if (key < leaf->key)	            //Если искомое ключевое значение меньше ключевого значения узла
            return find(key, leaf->left);
        else                                //Тогда искомое значение больше ключевого
            return find(key, leaf->right);
    }
    else return nullptr;
}

bool Tree::del(const int key)
{
    Node *curr = root;
    Node *prev = nullptr;
    if (curr == nullptr)
        return false;
    else {
        while (curr->key != key) //Поиск удаляемого элемента
        {
            if (curr->key < key) //Ход по правой ветке
            {
                if (curr->right != nullptr)
                {
                    prev = curr;
                    curr = curr->right;
                } else
                    return false;
            }
            if (curr->key > key) //Ход по левой ветке
            {
                if (curr->left != nullptr)
                {
                    prev = curr;
                    curr = curr->left;
                } else
                    return false;
            }
        }
    }
    Node *left = curr->left;
    Node *right = curr->right;
    if (curr!=root) //Если удаляем не корень
    {
        if (right != nullptr)
        { //Если справа есть ветка
            find_min(right)->left = left;
            Node *prevright = prev->right;
            if (prevright->key == curr->key) //Если элемент был слева
            {
                prev->right = right;
            }
            else //Тогда был справа
                prev->left = right;
        } else { //Иначе справа пусто
            if (prev->left == curr) //Когда элемент был слева
            {
                prev->left = left;
            } //Иначе он был справа
            else prev->right = left;
        }
    }
    else{ //Иначе удаляем корень
        if (right != nullptr) //Елси справа есть ветка
        {
            find_min(right)->left = left;
            root = right;
        } else { //Если же и спрва пусто
            root = left;
        }
    }
    delete curr;
    return true;
}

int main() {
    std::cout << "The end." << std::endl;
}
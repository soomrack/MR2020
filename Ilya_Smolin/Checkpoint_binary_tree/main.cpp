#include <iostream>
#include <string>

// Binary search tree


class Node {
public:
    int key;
    std::string data;
public:
    Node *left;
    Node *right;
public:
    Node();
    ~Node();
};

class Tree {
private:
    Node *root;
    Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left ? findmin(p->left) : p;
    }
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() {left = nullptr; right = nullptr;}

Tree::Tree() {root = nullptr;}

bool Tree::add(const int key, const std::string data)
{
    Node *current = root;
    if (current == nullptr)
    {
        root = new Node;
        root->key = key;
        root->data = data;
        return true;
    }
    while (true)
    {
        if (current->key < key)
        {
            if (current->right == nullptr)
            {
                current->right = new Node;
                Node *newNode = current->right;
                newNode->key = key;
                newNode->data = data;
                return true;
            }
                current = current->right;
        }
        if (current->key > key)
        {
            if (current->left == nullptr)
            {
                current->left = new Node;
                Node *newNode = current->left;
                newNode->key = key;
                newNode->data = data;
                return true;
            }
                current = current->left;
        }
        if (current->key == key)
            return false;
    }
}

bool Tree::del(const int key)
{
    Node *current = root;
    Node *prev = nullptr;
    if (current == nullptr)
        return false;

    while (current->key != key)
    {
        if (current->key < key)
        {
            if (current->right != nullptr)
            {
                prev = current;
                current = current->right;
            } else
                return false;
        }
        if (current->key > key) {
            if (current->left != nullptr)
            {
                prev = current;
                current = current->left;
            } else
                return false;
        }
    }

    Node *current_left = current->left;
    Node *current_right = current->right;

    if (current == root)
    {
        if (current_right != nullptr)
        {
            findmin(current_right)->left = current_left; //Левая подветка идет вниз
            root = current_right; //Корнем становится правый элемент от от корня
        }
        else //Удаляемый элемент - корень, и справа пусто
        {
            root = current_left;
        }
        delete current;
        return true;
    }
    if (current_right != nullptr)
    {
        findmin(current_right)->left = current_left; //Левая подветка идет вниз
        Node *prevright = prev->right;
        if (prevright->key == current->key) //Если удаляемый элемент был слева у родителя
        {
            prev->right = current_right;
        }
        else
            prev->left = current_right; //Если справа
    }
    else
    {
        if (prev->left == current) //Если удаляемый элемент был слева у родителя
            prev->left = current_left;
        else prev->right = current_left;
    }
    delete current;
    return true;
}

std::string Tree::find(const int key)
{
    Node *current = root;
    if (current == nullptr)
        return "";
    while (current->key != key)
    {
        if (current->key < key)
        {
            if (current->right == nullptr)
                return std::string("");
            current = current->right;
        }
        else if (current->key > key)
        {
            if (current->left == nullptr)
                return std::string("");
            current = current->left;
        }
    }
    return (current->data);
}
Tree::~Tree() {delete root;}
Node::~Node() {delete left; delete right;}
int main()
{
    Tree mytree;
    mytree.add(10, "10");
    mytree.add(19,"19");
    mytree.add(21,"21");
    mytree.add(20,"20");
    mytree.add(15,"15");
    mytree.add(5,"5");
    std::cout<<mytree.find(19)<<std::endl;
    std::cout<<mytree.find(10)<<std::endl;
    std::cout<<mytree.find(15)<<std::endl;
    mytree.del(15);
    std::cout<<mytree.find(15)<<std::endl;
}
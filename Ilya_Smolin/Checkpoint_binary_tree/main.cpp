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
        return p->left?findmin(p->left):p;
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
bool Tree::add(const int key, const std::string data) {
    Node *current = root;
    if (current == nullptr) {
        root = new Node;
        root->key = key;
        root->data = data;
    }
    else{
        while (current->key != key)
        {
            if (current->key < key) {
                if (current->right == nullptr) {
                    current->right = new Node;
                    Node *newNode = current->right;
                    newNode->key = key;
                    newNode->data = data;
                    return true;
                } else
                    current = current->right;
            } else if (current->key > key) {
                if (current->left == nullptr) {
                    current->left = new Node;
                    Node *newNode = current->left;
                    newNode->key = key;
                    newNode->data = data;
                    return true;
                } else current = current->left;
            } else if (current->key == key)
                return false;
        }
    }
    return false;
}
bool Tree::del(const int key)
{
    Node *current = root;
    Node *prev = nullptr;
    if (current == nullptr)
        return false;
    else {
        while (current->key != key) {
            if (current->key < key) {
                if (current->right != nullptr) {
                    prev = current;
                    current = current->right;
                } else
                    return false;
            }
            if (current->key > key) {
                if (current->left != nullptr) {
                    prev = current;
                    current = current->left;
                } else
                    return false;
            }
        }
    }
    std::cout<<"To, chto udalayem: ";
    std::cout<<current->data<<std::endl;

    Node *q = current->left;
    Node *r = current->right;

    if (current!=root) { //Когда удаляемый элемент не корень дерева
        if (r != nullptr) { //Удаляемый элемент - не корень, и справа есть узел
        findmin(r)->left = q; //Левая подветка идет вниз
            Node *prevright = prev->right;
            if (prevright->key == current->key) //Если удаляемый элемент был слева у родителя
            {
                prev->right = r;
            }
            else
                prev->left = r; //Если справа
        } else { //Удаляемый элемент - не корень, и справа пусто
            if (prev->left == current) //Если удаляемый элемент был слева у родителя
                prev->left = q;
            else prev->right = q;
        }
    }
    else{ //Удаляемый элемент - корень дерева
        if (r != nullptr) { //Удаляемый элемент - корень, и справа есть узел
            findmin(r)->left = q; //Левая подветка идет вниз
            root = r; //Корнем становится правый элемент от от корня
        } else { //Удаляемый элемент - корень, и справа пусто
            root = q;
        }
    }
    delete current;
    return true;
}
std::string Tree::find(const int key) {
    Node *current = root;
    if (current == nullptr)
        return "its empty here";
    else {
        while (current->key != key) {
            if (current->key < key) {
                if (current->right == nullptr) {
                    return std::string("Oops");
                } else
                    current = current->right;
            } else if (current->key > key) {
                if (current->left == nullptr) {
                    return std::string("Ooops");
                } else current = current->left;
            }
        }
        return (current->data);
    }
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
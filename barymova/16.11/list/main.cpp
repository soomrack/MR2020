#include <iostream>

#define EX -2147483648

class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node(const int value);
    Node(int value, Node *next);
    ~Node();
};

class List;

class Iterator {
private:
    Node *current;
    Node *prev;
    List *list;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
    bool isEmpty();
public:
    Iterator();
    Iterator(List &root);
    ~Iterator();
};

class List {
private:
    friend class Iterator;
    Node *root;
public:
    Iterator begin();
public:
    List();
    ~List();
};

Node::Node() {
    value = EX;
    next = nullptr;
}

Node::Node(const int value) {
    this->value = value;
    this->next = nullptr;
}

Node::Node(int value, Node *next) {
    this->value = value;
    this->next = next;
}

Node::~Node() {
    delete next;
}

Iterator::Iterator() {
    current = nullptr;
    prev = nullptr;
    list = nullptr;
}

Iterator::~Iterator() {
    delete current;
    delete prev;
    delete list;
}

Iterator::Iterator (List &root){
    list = &root;
    current = list->root;
    prev = nullptr;
}

bool Iterator::isEmpty(){
    if (current == nullptr)
        return true;
    else
        return false;
}

Iterator Iterator::next() {
    if (!isEmpty()){
        prev = current;
        current = current->next;
    }
    return *this;
}

int Iterator::get_value() {
    if (isEmpty()) return EX;
    return current->value;
}

void Iterator::set_value(const int value) {
    if (isEmpty()) return;
    current->value = value;
}

void Iterator::insert(const int value) {
    if (isEmpty()) {
        list->root = new Node(value);
        current = list->root;
        return;
    }
    current->next = new Node(value);
    if (current == list->root) list->root->next = current->next;
    prev = current;
    current = current->next;
}

void Iterator::del() {
    if (isEmpty()) return;
    delete current;
    if (current == list->root){
        delete list->root;
    } else{
        current = prev;
        current->next = nullptr;
        if (current == list->root){
            prev = nullptr;
            return;
        }
        prev = list->root;
        while (prev->next != current){
            prev = prev->next;
        }
    }
}

List::List() {
    root = nullptr;
}

List::~List() {
    while (root != nullptr){
        Node *temp = root;
        root = root->next;
        delete temp;
    }
}

Iterator List::begin() {
    Iterator begin(*this);
    return begin;
}

int main() {
    List list;
    Iterator iterator = list.begin();
    iterator.insert(6);
    std::cout << iterator.get_value() << std::endl;
    iterator.set_value(5);
    std::cout << iterator.get_value() << std::endl;
    iterator.insert(4);
    std::cout << iterator.get_value() << std::endl;
    iterator.del();
    std::cout << iterator.get_value() << std::endl;
    std::cout << "The end." << std::endl;
}

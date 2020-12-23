#include <iostream>

class List;
const int err = 666666666;

class Node {
public:
    int value;
    Node *next;
public:
    Node(int value);
    Node(int value, Node *next);
};

Node::Node(int value){
    this->value = value;
    next = nullptr;
}

Node::Node(int value, Node *next) {
    this-> value = value;
    this-> next = next;
}


class Iterator {
private:
    Node *current;
    Node *prev;
    List *first_element;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);
    void del();
public:
    Iterator();
    Iterator (List &first_element);
};


void Iterator::set_value(const int value){
    if (!current)
        return;
    current->value = value;
}

Iterator Iterator::next() {
    if (current != nullptr){
        prev = current;
        current = current->next;
    }
    return *this;
}


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

Iterator::Iterator (List &first){
    first_element = &first;
    current = first_element->root;
    prev = nullptr;
}


Iterator::Iterator(){
    current = first_element->root;
}

Iterator List::begin(){
    Iterator foo(*this);
    return foo;
}

List::List() {
    root = nullptr;
}

List::~List() {
    Iterator Destruct;
    while (root)
        Destruct.del();
}

void Iterator::insert (const int value){
    if (!current){
        current = new Node(value, current);
        first_element->root = current;
        return;
    }
    current->next = new Node(value, current->next);
}

void Iterator::del() {
    if (current && prev)
    {
        prev->next = current->next;
        delete current;
        current = prev->next;
        return;
    }
    if (!prev && current)
    {
        first_element->root = current->next;
        delete current;
        current = first_element->root;
        return;
    }
}

int Iterator::get_value() {
    if (!current)
        return err;
    return current->value;
}



int main() {
    List list;
    Iterator iterator = list.begin();
    iterator.insert(1);
    std::cout << iterator.get_value() << '\n';
    iterator.insert(3);
    iterator.next();
    std::cout << iterator.get_value() << '\n';
    iterator.del();
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(18);
    std::cout << iterator.get_value() << '\n';
    std::cout << "The end." << std::endl;
}
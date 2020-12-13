#include <iostream>

class List;
const int error = 2147483647;

class Node {
public:
    int value;
    Node *next;
public:
    Node(int value);
    Node(int value, Node *next);
};


class Iterator {
private:
    Node *current;
    Node *prev;
    List *head;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert_before(const int value);
    void insert_after (const int value);
    void del();
public:
    Iterator();
    Iterator (List &head);
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



Node::Node(int value){
    this->value = value;
    next = nullptr;
}

Node::Node(int value, Node *next) {
    this-> value = value;
    this-> next = next;
}


Iterator::Iterator(){
    current = head->root;
    prev = nullptr;
}

Iterator::Iterator (List &root){
    head = &root;
    current = head->root;
    prev = nullptr;
}

void Iterator::insert_before (const int value){
    if (prev == nullptr && current == nullptr) {
        current = new Node (value, current);
        head->root = current;
        return;
    }
    prev->next = new Node (value, current);
    current = prev->next;
}

void Iterator::insert_after (const int value) {
    if (current == nullptr){
        current = new Node (value, current);
        head->root = current;
        return;
    }
    current->next = new Node (value, current->next);
}

void Iterator::del() {
    if (current != nullptr && prev != nullptr)
    {
        prev->next = current->next;
        delete current;
        current = prev->next;
        return;
    }

    if (prev == nullptr && current != nullptr)
    {
        head->root = current->next;
        delete current;
        current = head->root;
        return;
    }
}

int Iterator::get_value() {
    if (current == nullptr)
        return error;
    return current->value;
}

void Iterator::set_value(const int value) {
    if (current == nullptr) return;
    current->value = value;
}

Iterator Iterator::next() {
    if (current != nullptr){
        prev = current;
        current = current->next;
    }
    return *this;
}


Iterator List::begin(){
    Iterator begin(*this);
    return begin;
}

List::List() {
    root = nullptr;
}

List::~List() {
    Iterator toDelete;
    while (root != nullptr)
        toDelete.del();
}


int main() {
    List list;
    Iterator iterator = list.begin();
    iterator.insert_after(1);
    iterator.insert_after(2);
    iterator.insert_after(3);
    iterator.next();
    iterator.del();
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(5);
    std::cout << iterator.get_value() << '\n';
    iterator.insert_before(4);
    Iterator iterator2 = list.begin();
    std::cout << iterator2.get_value() << '\n';
    iterator2.next();
    std::cout << iterator2.get_value() << '\n';
    iterator2.next();
    std::cout << iterator2.get_value() << '\n';
    iterator2.next();
    std::cout << iterator2.get_value() << '\n';
    iterator2.next();
    std::cout << "The end." << std::endl;
}

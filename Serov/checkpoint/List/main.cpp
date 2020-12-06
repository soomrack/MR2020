#include <iostream>

class List;

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
    void insert(const int value);
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

Node :: Node(int value){
    this->value = value;
    next = nullptr;
}

Node ::Node(int value, Node *next) {
    this-> value = value;
    this-> next = next;
}

Iterator :: Iterator(){
    current = head->root;
}

Iterator :: Iterator (List &rooot){
    head = &rooot;
    current = head->root;
    prev = nullptr;
}

Iterator List :: begin(){
    Iterator remake(*this);
    return (*this);
}

List ::List() {
    root = nullptr;
}

List :: ~List() {
    Iterator toDelete;
    while (root != nullptr)
        toDelete.del();
}

void Iterator::insert (const int value){
    current = new Node(value, current);
    head->root = current;
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

int Iterator  :: get_value() {
    return current->value;
}

void Iterator ::set_value(const int value) {
    current->value = value;
}

Iterator Iterator ::next() {
    if (current != nullptr){
        prev = current;
        current = current->next;
    }
    return *this;
}


int main() {
    List list;
    Iterator iterator = list.begin();
    iterator.insert(1);
    iterator.insert(2);
    std::cout << iterator.get_value() << '\n';
    iterator.del();
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(25);
    std::cout << iterator.get_value() << '\n';
    std::cout << "The end." << std::endl;
}

#include <iostream>


class Node {
public:
    int value;
    Node* next;
public:
    Node(int value);
    Node(int value, Node* next);
};


class Iterator {
private:
    Node* current;
    Node* prev;
    List* list;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator();
    Iterator(List& list);
};

class List {
private:
    friend class Iterator;
    Node* root;
    int count;
public:
   Iterator begin();
public:
   List();
   ~List();
};

Node::Node(const int value)
{
    this->value = value;
    this->next = nullptr;
}

Node::Node(const int value, Node* next)
{
    this->value = value;
    this->next = next;
}

List::List() {
   root = nullptr;
}

List::~List()
{
    Iterator Delete;
    while (root != nullptr)
        Delete.del();
}

Iterator::Iterator(List& list)
{
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

Iterator Iterator::next()
{
    if (current->next == nullptr)
    {
        prev = nullptr;
        current = nullptr;
        return *this;
    }
    prev = current;
    current = current->next;
    return *this;
}

int Iterator::get_value()
{
    if (current != nullptr)
        return current->value;
    return 0 ;
}

void Iterator::set_value(const int value)
{
    if (current != nullptr)
        current->value = value;
}

void Iterator::del()
{
    if (current == list->root) {
        list->root = list->root->next;
        delete current;
        current = list->root;
        return;
    }

    if (current->next == nullptr) 
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
        return;
    }
 
    prev->next = current->next;
    delete current;
    current = list->root;
    list->count--;
}

void Iterator::insert(const int value)
{
    prev->next = new Node(value, current);
    list->count++;
}

Iterator List::begin()
{
    Iterator tmp(*this);
    return (tmp);
}


int main() {
    std::cout << "The end." << std::endl;
}
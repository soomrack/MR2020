#include <iostream>
using namespace std;

const int error = -1;

class Node {
public:
    int value{};
    Node *next;
public:
    Node();
    Node(const int value);
    Node(const int value, Node *next);
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
    void insert(const int value);   // insert new node after current
    void del();                     // delete current node
public:
    Iterator(List & list);
};


class List {
private:
    friend class Iterator;
    Node *root;
    int list_size;
public:
    Iterator begin();
    void pop_first();
public:
    List();
    ~List();
};

Node::Node()
{
    next = nullptr;
}

Node::Node(const int value)
{
    this->value = value;
    this->next = nullptr;
}

Node::Node(const int value, Node *next)
{
    this->value = value;
    this->next = next;
}

List::List()
{
    list_size = 0;
    root = nullptr;
}

List::~List()
{
    while (list_size) { pop_first(); }
}

void List::pop_first()
{
    Node *temp = root;
    root = root->next;
    delete temp;
    list_size--;
}

Iterator::Iterator(List &list)
{
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

Iterator List::begin()
{
    Iterator tmp(*this);
    return (tmp);
}

Iterator Iterator::next()
{
    if ( current != nullptr && current->next != nullptr )
    {
        this->prev = this->current;
        this->current = this->current->next;
        return *this;
    }
}

int Iterator::get_value()
{
    if (current != nullptr)
        return current->value;
    return error;
}

void Iterator::set_value(const int value)
{
    if (current != nullptr)
        current->value = value;
}

void Iterator::del()
{
    if (current == nullptr)
        return;
    if (current == list->root)
    {
        list->root = list->root->next;
        delete current;
        current = list->root;
        list->list_size--;
        return;
    }
    if (current->next == nullptr)
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
        list->list_size--;
        return;
    }
    prev->next = current->next;
    delete current;
    current = prev->next;
    list->list_size--;
}

void Iterator::insert(const int value)
{
    if (list->root == nullptr)
    {
        list->root = new Node (value);
        list->list_size++;
        current = list->root;
        prev = nullptr;
        return;
    }
    if (current != nullptr)
    {
        if (current->next != nullptr)
            current->next = new Node(value, current->next);
        else
            current->next = new Node(value);
        list->list_size++;
    }
}

int main() {
    
    return 0;
}

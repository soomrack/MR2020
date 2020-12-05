#include <iostream>

class Node {
public:
    int value;
    Node *next;
public:
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
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator(List &list);
};


class List {
private:
    friend class Iterator;
    Node *root;
    int size;
public:
    Iterator begin();
private:
    void pop_front();
public:
    List();
    ~List();
};

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
    size = 0;
    root = nullptr;
}

List::~List()
{
    while(size)
        pop_front();
}

void List::pop_front()
{
    if (size == 0)
        return;
    Node *temp = root;
    root = root->next;
    delete temp;
    size--;
}

Iterator::Iterator(List &list)
{
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

Iterator Iterator::next()
{
    if (current->next == nullptr)
    {
        prev = current;
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
    return 101;
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
    if (current->next == nullptr)
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
        list->size--;
        return;
    }
    if (current == list->root)
    {
        list->root = list->root->next;
        delete current;
        current = list->root;
        list->size--;
        return;
    }
    prev->next = current->next;
    delete current;
    current = list->root;
    list->size--;
}

void Iterator::insert(const int value)
{
    if (list->size == 0)
    {
        list->root = new Node (value);
        list->size++;
        current = list->root;
        prev = nullptr;
        return;
    }
    current = new Node (value);
    prev->next = current;
    list->size++;
}

Iterator List::begin()
{
    Iterator tmp(*this);
    return (tmp);
}

int main()
{
    std::cout << "The end." << std::endl;
}

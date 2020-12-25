#include <iostream>

const int nol;
class Node {
public:
    int value{};
    Node *next;
public:
    Node();
    Node(int value);
    Node(int value, Node *next);
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
    void set_value( int value);
public:
    void insert( int value);
public:
    Iterator(List & list);
};


class List {
private:
    friend class Iterator;
    Node *root;
    int size;
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

Node::Node( int value)
{
    this->value = value;
    this->next = nullptr;
}

Node::Node( int value, Node *next)
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
    while (root == nullptr){
        pop_first();
    }
}
void List::pop_first()
{
    if (root == nullptr)
        return;
    Node *tmp = root;
    root = root->next;
    delete tmp;
    size--;
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
    if (this->current == nullptr) return *this;
    this->prev = this->current;
    this->current = this->current->next;

    return *this;
}

int Iterator::get_value()
{
    if (current)
    {
        return current->value;
    }
    return nol;
}

void Iterator::set_value(const int value)
{
    if (current)
    {
        current->value = value;
    }
}
void Iterator::insert(const int value)
{
    if (list->root == nullptr)
    {
        list->root = new Node (value);
        list->size++;
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
        list->size++;
    }
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
        list->size--;
        return;
    }
    if (current->next == nullptr)
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
        list->size--;
        return;
    }
    prev->next = current->next;
    delete current;
    current = prev->next;
    list->size--;
}



int main() {
    std::cout << "The end." << std::endl;
}
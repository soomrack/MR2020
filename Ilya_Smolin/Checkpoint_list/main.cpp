#include <iostream>

const int errorcode = -666;

class Node {
public:
    int value;
    Node *next;
public:
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
    void set_value(const int value);
public:
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator(List & list);
};



class List {
private:
    friend class Iterator;
    Node *root;
public:
    Iterator begin();
    void clear();
    void pushBack (int value);
    void popFront();
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
    this -> value = value;
    this -> next = next;
}


List::List()
{
    root = nullptr;
}


List::~List()
{
    clear();
}


void List::pushBack(int value) //Считается, что лист не зациклен
{
    if (root == nullptr)
    {
        root = new Node(value);
        return;
    }
    Node *current = this->root;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = new Node (value);
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
    return errorcode;
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
}


void Iterator::insert(const int value)
{
    if (list->root == nullptr)
    {
        list->root = new Node (value);
        current = list->root;
        prev = nullptr;
        return;
    }
    if (prev == nullptr)
    {
        list->root = new Node (value, current);
    }
    prev->next = new Node (value, current);
}

Iterator List::begin()
{
    Iterator tmp(*this);
    return (tmp);
}

void List::popFront()
{
    if (root == nullptr) return;
    Node *ptr = root;
    root = root->next;
    delete ptr;
}

void List::clear()
{
    while (root != nullptr)
    {
        popFront();
    }
}


int main() {
    List list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);
    Iterator itr = list.begin();
    itr.del();
    itr.next();
    itr.next();
    itr.next();
    itr.insert(9);
    list.clear();
    List list2;
    list2.pushBack(3);
    }
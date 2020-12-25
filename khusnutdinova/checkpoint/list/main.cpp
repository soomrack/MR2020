#include <iostream>

const int END_OF_LIST = 1212121;

class List;

class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node( int value);
    Node( int value,  Node *next);
};

class Iterator {
private:
    Node *current;
    Node *prev;
    List *master;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);
    void del();
public:
    Iterator();
    Iterator(List &master);
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


Node::Node()
{
    next = nullptr;
}

Node::Node(int value)
{
    this->value = value;
}

Node::Node( int value,  Node *next)
{
    this->value = value;
    this->next = next;
}

List::List()
{
    root = nullptr;
}

Iterator List::begin()
{
    Iterator newIter(*this);
    return newIter;
}

List::~List()
{
    Iterator eraser(*this);
    while(root != nullptr)
    {
        eraser.del();
    }
}


Iterator::Iterator()
{
    current = master->root;
    prev = nullptr;
}

Iterator::Iterator(List &masterList)
{
    master = &masterList;
    current = master->root;
    prev = nullptr;
}

void Iterator::insert(const int value)
{
    if (prev == nullptr)
    {
        current = new Node (value, current);
        master->root = current;
        return;
    }

    prev->next = new Node (value, current);
}

void Iterator::del()
{
    if (current == nullptr ) return;

    if (master->root->next == nullptr)
    {
        delete current;
        master->root = nullptr;
        return;
    }

    if (prev == nullptr)
    {
        master->root = current->next;
        delete current;
        current = master->root;
        return;
    }

    prev->next = current->next;
    delete current;
    current = prev->next;
    return;

}

int Iterator::get_value()
{
    if (current == nullptr)
    {
        return END_OF_LIST;
    }
    return current->value;
}

void Iterator::set_value(int value)
{
    if (current == nullptr) {return;}

    current->value = value;
}

Iterator Iterator::next()
{
    if (this->current == nullptr) return *this;

    this->prev = this->current;
    this->current = this->current->next;

    return *this;
}
int main()
{
    std::cout << "The end." << std::endl;
}

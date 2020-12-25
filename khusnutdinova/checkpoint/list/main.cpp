#include <iostream>

const int END_OF_LIST = 1212121;

class List;
class Iterator;

class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node( int value);
    Node( int value,  Node *next);
    ~Node();
};

class Iterator {
private:
    List *master;

    Node *current;
    Node *prev;
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

Node::~Node()
{

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

void Iterator::insert(const int value){
    if (current != nullptr){
        current->next = new Node(value, current->next);;
        current = current->next;
    }else{
        current = new Node(value, current);
        list->root = current;
    }
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

Iterator::~Iterator()
{
    //delete this;
}


int main()
{
    std::cout << "The end." << std::endl;
}


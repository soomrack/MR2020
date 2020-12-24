#include <iostream>

const int error = NULL;

class List;
class Iterator;

class Node 
{
public:
    int value;
    Node* next;
public:
    Node();
    Node(int value);
    Node(int value, Node* next);
    ~Node();
};

class Iterator 
{
private:
    List* master;

    Node* current;
    Node* prev;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator();
    Iterator(List& master);
    ~Iterator();
};

class List 
{
private:
    friend class Iterator;
    Node* root;     //more like head but ok
    int size;
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

Node::Node(const int value)
{
    this->value = value;
    this->next = nullptr;
}

Node::Node(int value, Node* next)
{
    this->value = value;
    this->next = next;
}

Node::~Node()
{
    //delete this;
}

List::List()
{
    size = 0;
    root = nullptr;
}

Iterator List::begin()
{
    Iterator fresh(*this);
    return fresh;
}

List::~List()
{
    while (root != nullptr) {
        Node* temp = root;
        root = root->next;
        delete temp;
        size--;
    }
}


Iterator::Iterator()
{
    current = master->root;
    prev = nullptr;
}

Iterator::Iterator(List& masterList)
{
    master = &masterList;
    current = master->root;
    prev = nullptr;
}

void Iterator::insert(const int value)
{
    Node* tempNode = new Node(value, current);
    if (prev != nullptr)
    {
        prev->next = tempNode;
        return;
    }
    current = tempNode;
    master->root = current;
}

void Iterator::del()
{
    if (current && prev)     
    {
        prev->next = current->next;  
        delete current;                  
        current = prev->next;
    }
    else if (current == master->root)
    {
        master->root = current->next; 
        delete current;
        current = master->root;
    }
}

int Iterator::get_value()
{
    if (current)        
    {
        return current->value;
    }
    return error;
}

void Iterator::set_value(int value)
{
    if (current)       
    {
        current->value = value;
    }
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

int main() {
    std::cout << "The end." << std::endl;
}
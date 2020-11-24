  
#include <iostream>

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
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator();
    ~Iterator();
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
    delete this;
} 

class List {
private:
    friend class Iterator;
    Node *root;     //more like head but ok
public:
    Iterator begin();
public:
    List();
    ~List();
};

List::List()
{
    root = nullptr;
}

Iterator List::begin()
{
    return Iterator();
}

List::~List()
{
    Iterator eraser;
    while(root)
    {
        eraser.del();
    }
}


Iterator::Iterator()
{
    current = nullptr;
}

void Iterator::insert(const int value)
{
    Node* newNodePtr = new Node(value, current);
    next();
}

void Iterator::del()
{
    if (current && prev)       //if the list is not empty and previous element present
    {
        prev->next = current->next;     //ties neighbours together
    }
    else if (current == master->root)
    {
        master->root = current->next;   //update head
    }
    delete current;
    next();
}

int Iterator::get_value()
{
    if (current)        //not null
    {
        return current->value;
    }
    return -1;
}

Iterator Iterator::next()
{
    /*Node *temp;
    temp = master->root;        //workaround to fix lack of fileds 
    master->root = current->next; */  //since root is the only available data in constructor 
    Iterator newIt;                 
    newIt.current = current->next;
    newIt.prev = current;

    return newIt;
}

Iterator::~Iterator()
{
    delete this;
}


int main() {
    List test;
    Iterator it = test.begin(); 
    it.insert(6);
    for (; it.get_value(); it.next())
    {
        it.insert(5);
        it.insert(4);
        it.insert(3);
        it.get_value();
        it.del();
        it.get_value();
        it.insert(2);
    }
    std::cout << "The end." << std::endl;
}
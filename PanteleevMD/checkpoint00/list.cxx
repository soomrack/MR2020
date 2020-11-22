  
#include <iostream>

class List;
class Iterator;

class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node(const int value);
    Node(const int value, const Node *next);
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

Node::Node(const int value)
{
    this->value = value;
} 

Node::Node(const int value, const Node *next)
{
    this->value = value;
    this->next = next;
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
    root->next = nullptr;
    root->value = -111111;
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
    current = master->root;
}

void Iterator::insert(const int value)
{
    Node* newNodePtr = new Node;
    newNodePtr->value = value; 
    newNodePtr->next = master->root; // Initialize all the fields

    master->root = newNodePtr;

}

void Iterator::del()
{
    if (master->root)       //if the list is not empty
    {
        Node* newHead = master->root->next;
        delete master->root;
        master->root = newHead;
    }
}

int Iterator::get_value()
{
    if (current)
    {
        return current->value;
    }
}

Iterator Iterator::next()
{
    Node *temp;
    temp = master->root;
    master->root = current->next;   //workaround to fix lack of fileds 
    Iterator newIt;                 //since root is the only available data in constructor 
    master->root = temp;            //fix root

    return newIt;
}



int main() {
    List test;
    Iterator it = test.begin(); 
    it.insert(6);
    for (it; it.get_value(); it.next())
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
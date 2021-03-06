  
#include <iostream>

#define END_OF_LIST -1212121

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
    Iterator(List &master);
    ~Iterator();
};

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
    //delete this;
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
    while(root != nullptr)     //deletes elements untill nullptr is reached
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
//             <-
//root -> e3 -> e2 -> e1 -- nullptr

void Iterator::insert(const int value)
{
    /*if (current == nullptr)
    {
        current = new Node (value, nullptr);
        master->root = current;
        return;
    }*/
    if (prev == nullptr)            //iterator on root
    {
        current = new Node (value, current);
        master->root = current;
        return;
    }

    current->next = new Node (value, current->next);
}

void Iterator::del()
{
    if (current == nullptr ) return;     //nothing to delete

    if (master->root->next == nullptr)      //list of single element
    {
        delete current;
        master->root = nullptr;
        return;
    }
    
    if (prev == nullptr)                //deleting head
    {
        master->root = current->next;
        delete current;
        current = master->root;
        return;
    }
    //middle deletion
    prev->next = current->next;      //ties neighbours together
    delete current;
    current = prev->next;
    return;                         //no need in updating head
  
}

int Iterator::get_value()
{
    if (current == nullptr)        //list is empty
    {
        return END_OF_LIST;
    }
    return current->value;
}

void Iterator::set_value(int value)
{
    if (current == nullptr) {return;}       //list is empty

    current->value = value;
}

Iterator Iterator::next()
{
    if (this->current == nullptr) return *this;       //idk what to retun (no .end())
    
    this->prev = this->current;
    this->current = this->current->next;

    return *this;
}

Iterator::~Iterator()
{
    //delete this;
}


int main() {
    List test;

    std::cout << "Simple test" << '\n';
    Iterator it = test.begin(); 
    it.insert(1);
    it.insert(2);
    it.insert(3);
    it.insert(4);
    it.insert(5);
    for (; it.get_value() != END_OF_LIST; it.next())
    {
        std::cout << it.get_value()  << '\n';
    }

    std::cout << "Second iterator test" << '\n';
    Iterator it2 = test.begin();

    std::cout << it2.get_value() << '\n';
    it2.del();
    std::cout << it2.get_value() << '\n';
    it2.set_value(71);
    std::cout << it2.get_value() << '\n';
    it2 = it2.next();
    std::cout << it2.get_value() << '\n';

    std::cout << "Delete middle element test" << '\n';
    Iterator it3 = test.begin();
    it3.set_value(4);
    it3.insert(5);

    it3.next();
    it3.next();
    it3.del();
    it3.del();

    for (Iterator it3 = test.begin(); it3.get_value() != END_OF_LIST; it3.next())
    {
        std::cout << it3.get_value()  << '\n';
    }

    std::cout << "Middle insertion test" << '\n';
    Iterator it4 = test.begin();
    it4.next();
    it4.next();
    it4.insert(99);
    for (Iterator it4 = test.begin(); it4.get_value() != END_OF_LIST; it4.next())
    {
        std::cout << it4.get_value()  << '\n';
    }


    std::cout << "The end." << std::endl;
}
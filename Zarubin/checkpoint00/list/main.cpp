#include <iostream>
const int ERROR = 12345678;
class List;

class Node {
public:
    int value;
    Node *next;
public:
    Node(int value);
    Node(int value, Node *next);
};


class Iterator {
private:
    Node *current;
    Node *prev;
    List *head;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);
    void del();
public:
    Iterator();
    Iterator (List &head);
};


class List {
private:
    friend class Iterator;
    Node *root;
public:
    Iterator begin();
public:
    List();
};

Node::Node(const int value){
    this->value = value;
    this->next = nullptr;
}

Node::Node(const int value, Node *next){
    this->value = value;
    this->next = next;
}

Iterator Iterator::next(){
    if (this->current == nullptr){return *this;}

    this->prev = this->current;
    this->current = this->current->next;
    return *this;
};

int Iterator::get_value(){
    if(current){return current->value;}
    return NULL;
};

void Iterator::set_value(const int value){
    if(current){current->value = value;}
};

Iterator::Iterator(){
    current = head->root;
}

Iterator::Iterator (List &rooot){
    head = &rooot;
    current = head->root;
    prev = nullptr;
}

Iterator List::begin(){
    Iterator remake(*this);
    return (remake);
}

List::List() {
    root = nullptr;
}

void Iterator::insert (const int value){
    Node* tempNode = new Node(value, current);
    if (prev != nullptr)
    {
        prev->next = tempNode;
        return;
    }
    current = tempNode;
    head->root = current;
}

void Iterator::del() {
    if (current && prev)
    {
        prev->next = current->next;
        delete current;
        current = prev->next;
    }
    else if (current == head->root)
    {
        head->root = current->next;
        delete current;
        current = head->root;
    }
}

int main() {
    List list;

    Iterator iterator = list.begin();
    iterator.insert(4);
    iterator.insert(8);
    iterator.insert(12);
    std::cout << iterator.get_value() << '\n';
    iterator.del();
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(16);
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(24);
    std::cout << iterator.get_value() << '\n';
    std::cout << "The end." << std::endl;
}

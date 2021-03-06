#include <iostream>
using namespace std;

#define ERROR_OCCURED -1488

class List;

class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node(const int value);
    Node(const int value, Node *next);
    ~Node(); 
};

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
    ~Iterator();
};

class List {
private:
    friend class Iterator;
    Node *root; // a head of the list 
public:
    Iterator begin();
public:
    List();
    ~List();
};

Node::Node(){
    this->next = nullptr;
}

Node::Node(const int value){
    this->value = value;
    this->next = nullptr;
}

Node::Node(const int value, Node *next){
    this->value = value;
    this->next = next;
}

Node::~Node(){  

}

Iterator::Iterator(List &list){
    this->list = &list;
    this->current = list.root;
    this->prev = nullptr;
}

Iterator::~Iterator(){ 

}

Iterator Iterator::next(){
    if (this->current != nullptr){
        prev = current;
        current = current->next;
    }else{
        prev = current;
        this->current = nullptr;
        // current = list->root;
    }
    return *this;
}

int Iterator::get_value(){
    if (current != nullptr){
        int value = this->current->value;
        return value;
    }
    return ERROR_OCCURED;    
}

void Iterator::set_value(const int value){
    if (current != nullptr){
        current->value = value;
    }
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

void Iterator::del(){
    // if (current == nullptr){
    //     return;
    // }

    if (current == list->root){
        list->root = current->next;
        delete current;
        current = list->root;
        return;
    }else {
        prev->next = current->next;
        delete current;
        current = prev->next;
    }
}

Iterator List::begin(){
    Iterator firstIterator(*this);
    return firstIterator;
}

List::List(){
    this->root = nullptr;
}

List::~List(){
    Iterator cleaner(*this);

    while (root != nullptr){
        cleaner.del();
    }
}

int main() {  
    List testList;
    Iterator testIterator = testList.begin();

    testIterator.insert(1);
    testIterator.insert(2);
    testIterator.insert(3);
    // testIterator.next();
    Iterator testIterator2 = testList.begin();
    for(; testIterator2.get_value() != ERROR_OCCURED; testIterator2.next()){
        cout << testIterator2.get_value() << endl;
    }
    
    cout << "The end." << std::endl;
}
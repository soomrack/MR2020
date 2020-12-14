  
#include <iostream>
using namespace std;

class List;
class Iterator;

class Node {
    public:
        int value;
        Node *next;
    public:
        Node();
        Node(int value);
        Node(int value, Node *next);
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
        void set_value(int value);
    public:
        void insert(int value);  // insert new node after current
        void del();  // delete current node
    public:
        Iterator();
        Iterator(List &list);
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

Node::Node(){
    next = nullptr;
}

Node::Node(int value){
    this->value = value;
}

Node::Node(int value, Node *next){
    this->value = value;
    this->next = next;
}

Node::~Node(){
    //delete this;
}

List::List(){
    root = nullptr;
}

List::~List(){
    //delete this; 
    Iterator deleter(*this);
    while (root != nullptr){
        deleter.del();
    } //or empty
}

Iterator List::begin(){
    Iterator newNode(*this);
    return newNode;
}

// Iterator::Iterator(){
    
// }

Iterator::Iterator(List &list){
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

void Iterator::insert(int value){
    Node *tempNode = new Node(value, current);
    if (prev != nullptr){
        prev->next = tempNode;
        return;
    }
    current = tempNode;
    list->root = current;
}

void Iterator::del(){
    if(current == list->root){
        list->root = current->next;
        delete current;
        current =list->root;
        return;
    }
    if(current && prev){
        prev->next = current->next;
        delete current;
        current = prev->next;
    }
}

int Iterator::get_value(){
    if (current != nullptr){
        return current->value;
    }
    return NULL;
}

void Iterator::set_value(int value){
    if (current != nullptr){
        current->value = value;
    }
}

Iterator Iterator::next(){
    if (this->current == nullptr){
        // this->prev = this->current;
        // this->current = this->list->root;
        return *this;
    }
        prev = current;
        current = current->next;
    return *this;
}

Iterator::~Iterator(){

}

int main() {
    // Node test;
    // test.value = 2;
    // cout << test.value << endl;
     List test;

    Iterator iterator = test.begin(); 
    iterator.insert(1);
    iterator.insert(2);
    iterator.insert(3);
    
        for (; iterator.get_value() != NULL; iterator.next()){
        std::cout << iterator.get_value()  << '\n';
    }
    cout << "The end." << endl;
}
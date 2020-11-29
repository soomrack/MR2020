#include <iostream>
class List;

class Node {
public:
    int value;
    Node *next;
public:
    Node(int value){
        this->value = value;
        next = nullptr;
    }
    Node(int value, Node *next){
        this-> value = value;
        this-> next = next;
    }
};


class Iterator {
private:
    Node *current;
    Node *prev;
    List *head;
public:
    Iterator next(){
        if (current != nullptr){
            prev = current;
            current = current->next;
        }
        return *this;
    };
    int get_value(){
        return current->value;
    };
    void set_value(const int value){
        current->value = value;
    };
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
Iterator :: Iterator(){
    current = head->root;
}
Iterator :: Iterator (List &rooot){
    head = &rooot;
    current = head->root;
    prev = nullptr;
}
Iterator List :: begin(){
    Iterator remake(*this);
    return (*this);
}
List ::List() {
    root = nullptr;
}
void Iterator::insert (const int value){
    current = new Node(value, current);
    head->root = current;
}
void Iterator::del() {
    if (current != nullptr && prev != nullptr)       
    {
        prev->next = current->next;
        delete current;
        current = prev->next;
    }
    else if (prev == nullptr && current != nullptr)
    {
        head->root = current->next;
        delete current;
        current = head->root;
    }
}
int main() {
    List list;

    Iterator iterator = list.begin();
    iterator.insert(1);
    iterator.insert(2);
    std::cout << iterator.get_value() << '\n';
    iterator.del();
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(25);
    std::cout << iterator.get_value() << '\n';
    std::cout << "The end." << std::endl;
}


#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next;
public:
    Node(const int value);
    Node(int value, Node* next);
};

class List;

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
};


class List {
private:
    friend class Iterator;
    Node* root;
    int Count;
public:
    bool is_empty() { return root == nullptr; }
    Iterator begin();
    void clear();
    void push_end(int value);
    void pop_front();
    int get_count ();
public:
    List();
    ~List();
};

Node::Node(const int value)
{
    this->value = value;
    this->next = nullptr;
};

Node::Node(const int value, Node* next)
{
    this->value = value;
    this->next = next;
}

List::List()
{
    Count = 0; //количество элементов в списке
    root = nullptr;
}

List::~List()
{
    clear();
}

void List::push_end(int value)
{
    if (root == nullptr)
    {
        root = new Node(value);
    }
    else 
    {
        Node* current = this->root;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new Node(value);
    }
    Count++;
}

Iterator::Iterator(List & list)
{
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

Iterator Iterator::next() {
    if (current->next == nullptr)
    {
        prev = current;
        current = list->root; //Идём в начало списка
    }
    else
    {
        prev = current;
        current = current->next;
    }
    return *this;
}

int Iterator::get_value() 
{
    return current->value;
}

void Iterator::set_value(const int value)
{
    current->value = value;
}

void Iterator::del() 
{
    if (current->next == nullptr) 
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
    }
    else if (current == list->root) 
    {
        list->root = list->root->next;
        delete current;
        current = list->root;
    }
    else
    {
        prev->next = current->next;
        delete current;
        current = list->root;
    }
    list->Count--;
}

void Iterator::insert(const int value) 
{
    prev->next = new Node(value, current);
    list->Count++;
}
Iterator List::begin() 
{
    Iterator tmp(*this);
    return (*this);
}
void List::pop_front() 
{
    if (Count == 0) return;
    Node* ptr = root;
    root = root->next;
    delete ptr;
    Count--;
}
void List::clear() 
{
    std::cout << "Cleaning..." << std::endl;
    while (Count != 0) {
        pop_front();
    }

}int List::get_count() { return Count; }

int main() 
{
    List list;
    list.push_end(6);
    list.push_end(12);
    list.push_end(43);
    list.push_end(15);
    list.push_end(34);
    Iterator itr = list.begin();
    printf("%d\n", itr.get_value());
    itr.del();
    itr.next();
    printf("%d\n", itr.get_value());
    itr.next();
    printf("%d\n", itr.get_value());
    itr.next();
    printf("%d\n", itr.get_value());
    std::cout << "The end." << std::endl;
}
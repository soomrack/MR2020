#include <iostream>


class Node {
public:
    int value;
    Node *next;
public:
    Node(int value);
    Node(int value, Node *next);
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
    Node *root;
    int count;
public:
    bool isEmpty () {return root == nullptr;}
    Iterator begin();
    void clear();
    void pushBack (int value);//Кладем в конец списка элемент
    void popFront();
public:
    List();
    ~List();
};


Node::Node(const int value)
{
    this->value = value;
    this->next = nullptr;
}

Node::Node(const int value, Node *next)
{
    this -> value = value;
    this -> next = next;
}

List::List(){
    count = 0; //Количество элементов в списке, обновляем при добавлении или удалении элементов из списка
    root = nullptr;
}

List::~List()
{
    clear();
}

void List::pushBack(int value) //Считается, что  список не зациклен
{
    if (root == nullptr)
    {
        root = new Node(value);
        return;
    }
    Node *current = this->root;
    while (current->next != nullptr) //Идем к концу списка
    {
        current = current->next;
    }
    current->next = new Node (value);
    count++;
}

Iterator::Iterator(List &list)
{
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

Iterator Iterator::next()
{
    if (current->next == nullptr)
    {
        prev = nullptr;
        current = nullptr;
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
    if (current != nullptr)
        return current->value;
    return 666;
}

void Iterator::set_value(const int value)
{
    if (current != nullptr)
        current->value = value;
}

void Iterator::del()
{
    if (current == nullptr) //Проверка
        return;
    if (current->next == nullptr) //Удаление последнего
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
        return;
    }
    if (current == list->root){
        list->root = list->root->next;
        delete current;
        current = list->root;
        return;
    }
    prev->next = current->next;
    delete current;
    current = list->root;
    list->count--;
}

void Iterator::insert(const int value)
{
    prev->next = new Node (value, current);
    list->count++;
}

Iterator List::begin()
{
    Iterator tmp(*this);
    return (tmp);
}

void List::popFront()
{
    if (count == 0) return;
    Node *ptr = root;
    root = root->next;
    delete ptr;

    count--;
}

void List::clear()
{
    while (count != 0)
    {
        popFront();
    }
}


int main() {
    List list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);
    Iterator itr = list.begin();
    itr.del();
    itr.next();
    itr.next();
    itr.next();
    list.clear();
    List list2;
    list2.pushBack(3);
    }
#include <iostream>


class Node {
public:
    int value{};
    Node *next;
public:
    Node();
    Node(const int value);
    Node(const int value, Node *next);
};

class List;

class Iterator {
private:
    Node *current;
    Node *prev;
    List *list; //additional
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);   // insert new node after current
    void del();                     // delete current node
public:
    Iterator(List & list);
};


class List {
private:
    friend class Iterator;
    Node *root;
    int list_size;   //added
public:
    Iterator begin();
    void pop_first();
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

Node::Node(const int value, Node *next)
{
    this->value = value;
    this->next = next;
}

List::List()
{
    list_size = 0;
    root = nullptr;
}

List::~List()
{
    while (list_size)   //Пока list_size не станет равным нулю
    {
        pop_first();
    }
}

void List::pop_first()
{
    Node *temp = root;  //Временный узел, для хранения адреса первого элемента
    root = root->next;  //Адресс следующиего элемента за головой (второй элемент)
    delete temp;        //Удаление первого узла
    list_size--;
}

Iterator::Iterator(List &list)
{
    current = list.root;
    prev = nullptr;
    this->list = &list;
}

Iterator List::begin()
{
    Iterator tmp(*this);
    return (tmp);
}

Iterator Iterator::next()
{
    if (current->next != nullptr)
    {
        this->prev = this->current;
        this->current = this->current->next;
        return *this;
    }
}

int Iterator::get_value()
{
    if (current != nullptr)
        return current->value;
}

void Iterator::set_value(const int value)
{
    if (current != nullptr)
        current->value = value;
}

void Iterator::del()
{
    if (current == list->root)      //Если удаляем первый узел
    {
        list->root = list->root->next;
        delete current;
        current = list->root;
        list->list_size--;
        return;
    }
    if (current->next == nullptr)   //Если удаляем последний узел
    {
        prev->next = nullptr;
        delete current;
        current = list->root;
        list->list_size--;
        return;
    }                               //Тогда удаляем промежуточный
    prev->next = current->next;
    delete current;
    current = prev->next;
    list->list_size--;
}

void Iterator::insert(const int value)
{
    Node* tmp = new Node(value, current);
    if (prev != nullptr)
    {       //Если добавляем не в начало
        prev->next = tmp;
        prev = tmp;
        list->list_size++;
        return;
    }       //Тогда добавляем в начало
    current = tmp;
    list->root = current;
    list->list_size++;
}



int main() {
    List debug;
    Iterator iter = debug.begin();
    iter.insert(12);
    iter.insert(13);
    iter.del();
    iter.insert(9);
    iter.insert(22);
    iter.next();
    iter.insert(11);
    iter.del();
    return 0;
}

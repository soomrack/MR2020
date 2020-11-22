#include <iostream>


class Node {
public:
    int value;
    Node *next;
public:
    Node(const int value);
    Node(const int value, Node *next);
};


class List {
private:
    Node *root;
    int size;
public:
    int& operator[](const int index);
    void push_front(const int value);
    void pop_front();
    void insert(const int value);
    void insert_index(int value, int index);
    void del_index(int index);

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

List::List()
{
    size = 0;
    root = nullptr;
}

List::~List()
{
    while(size)
        pop_front();
}

void List::insert(const int value)
{
    if (root == nullptr)
    {
        root = new Node(value);
    }
    else
    {
        Node *current = this->root;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new Node(value);
    }
    size++;
}

int & List::operator[](const int index)
{
    int counter = 0;
    Node *current = this->root;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->value;
        }
        current = current->next;
        counter++;
    }
    exit(101);
}

void List::pop_front()
{
    Node *temp = root;
    root = root->next;
    delete temp;
    size--;
}

void List::push_front(const int value)
{
    root = new Node(value, root);
}

void List::insert_index(int value, int index)
{
    if (index == 0)
        {
            push_front(value);
        }
        else
        {
            Node *previous = this->root;
            for (int i = 0; i < index - 1; i++)
            {
                previous = previous->next;
            }
            Node *newNode = new Node(value, previous->next);
            previous->next = newNode;
            size++;
        }
}

void List::del_index(int index)
{
    if (index == 0)
        {
            pop_front();
        }
        else
        {
            Node *previous = this->root;
            for (int i = 0; i < index - 1; i++)
            {
                previous = previous->next;
            }
            Node *toDelete = previous->next;
            previous->next = toDelete->next;
            delete toDelete;
            size--;
        }
}


int main()
{
    std::cout << "The end." << std::endl;
}

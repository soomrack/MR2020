#include <iostream>

const int Error = 12345;

class Node {
public:
    int data;
    Node *prev;
public:
    Node();
    Node(const int value);
};

class Queue {
public:
    int pop();
    void push(const int value);
    Queue();
    ~Queue();
    bool isEmpty();
private:
    Node *first;
    Node *last;
};

Node::Node(const int value)
{
    this->data = value;
    this->prev = nullptr;
}

Queue::Queue()
{
    first = nullptr;
    last = nullptr;
}

void Queue::push(const int value)
{
    Node *new_node = new Node(value);
    if (first == nullptr)
    {
        first = new_node;
        last = new_node;
        return;
    }
    if (first == last)
    {
        first->prev = new_node;
    }
    last->prev = new_node;
    last = new_node;
}

int Queue::pop()
{
    if (isEmpty()) { return Error; }
    int temp = first->data;
    Node *previous = first;
    first = first->prev;
    delete previous;
    return temp;
}

bool Queue::isEmpty()
{
    if (first == nullptr)
        return true;
    return false;
}

Queue::~Queue()
{
    while (first)
    {
        Node *temp = first;
        first = first->prev;
        delete temp;
    }
}

int main()
{
    Queue debug;
    debug.push(12);
    debug.push(13);
    debug.push(14);
    debug.pop();
    debug.pop();
    debug.push(15);
    debug.push(12);
    debug.pop();
}

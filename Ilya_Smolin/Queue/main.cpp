#include <iostream>

const int ERROR_CODE = 666;
using namespace std;

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
    void print();
    Queue();
    ~Queue();
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
    if (last == nullptr)
    {
        first = new_node;
        last = new_node;
        return;
    }
    first->prev = new_node;
    first = new_node;
    return;
}

int Queue::pop()
{
    if (last == nullptr)  return ERROR_CODE;
    int answer = last->data;
    Node *node_to_pop = last;
    last = last->prev;
    delete node_to_pop;
    return answer;
}


Queue::~Queue()
{
    while (last)
    {
        pop();
    }
}

void Queue::print()
{
    Node *pointer = last;
    if (pointer == nullptr)
    {
        cout<< "queue is empty" <<endl;
        return;
    }
    while (pointer)
    {
        cout<<pointer->data<<endl;
        pointer = pointer->prev;
    }
}

int main()
{
    Queue debug;
    debug.push(12);
    debug.push(13);
    debug.push(14);
    debug.print();
    debug.pop();
    debug.pop();
    debug.pop();
    debug.print();
    debug.push(15);
    debug.push(12);
    debug.pop();
    debug.print();
}
#include <iostream>

class Stack {

public:
    int pop();
    void push(const int value);
    Stack();
    ~Stack();
    bool isEmpty();

private:
    struct node;
    node *top;
};

struct Stack::node {
    int data;
    node *pointer;
};

Stack::Stack() : top(NULL) {}

void Stack::push(const int value)
{
    node *previous = new node;
    previous->data = value;
    previous->pointer = top;
    top = previous;
}

int Stack::pop()
{
    if (isEmpty()) { return -1; }
    int temp = top->data;
    node *previous = top;
    top = top->pointer;
    delete previous;
    return temp;
}

bool Stack::isEmpty()
{
    return top ? false : true;
}


Stack::~Stack()
{
    while (top)
    {
        node *previous = top;
        top = top->pointer;
        delete previous;
    }
}


int main()
{
    std::cout << "The end." << std::endl;
}
#include <iostream>

const int error = -1;

class Stack {

public:
    int pop();
    void push(int value);
    Stack();
    ~Stack();
    bool isEmpty();

private:
    struct node;
    node *top;
};

struct Stack::node {
        int elements;
        node *pointer;
};

Stack::Stack() :top(nullptr) {}

void Stack::push(const int value)
{
    node *previous = new node;
    previous->elements = value;
    previous->pointer = top;
    top = previous;
}

int Stack::pop()
{
    if (isEmpty())
    {
        return error;
    }
    int temp = top->elements;
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
#include <iostream>

const int Error = 12345;

class Stack {

public:
    int pop();
    void push(const int value);
    Stack();
    ~Stack();
    bool isEmpty();

private:
    struct node *top;
};

struct node {
    int data;
    node *next;
};

Stack::Stack() : top(NULL) {}

void Stack::push(const int value)
{
    node *previous = new node;
    previous->data = value;
    previous->next = top;
    top = previous;
}

int Stack::pop()
{
    if (isEmpty()) { return Error; }
    int temp = top->data;
    node *previous = top;
    top = top->next;
    delete previous;
    return temp;
}

bool Stack::isEmpty()
{
    if (top == nullptr)
        return true;
    return false;
}


Stack::~Stack()
{
    while (top)
    {
        node *previous = top;
        top = top->next;
        delete previous;
    }
}


int main()
{
    std::cout << "The end." << std::endl;
}
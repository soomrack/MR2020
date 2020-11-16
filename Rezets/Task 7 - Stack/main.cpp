#include <iostream>

#define STACK_MAX_SIZE 1000

class Stack
{
public:
    int pop();
    void push(int value);
public:
    Stack();
    ~Stack();
private:
    int data[STACK_MAX_SIZE];
    size_t size;
};

int Stack::pop()
{
    if (size == 0)
        return -101;
    size--;
    return data[size];
}

void Stack::push(int value)
{
    data[size] = value;
    size++;
}

Stack::Stack()
{
    size = 0;
}

Stack::~Stack()
{
    while (size)
    pop();
}

int main()
{
    std::cout << "The end." << std::endl;
}

#include <iostream>

#define STACK_MAX_SIZE 1000
#define ERROR_EMPTY_STACK 101

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
        return ERROR_EMPTY_STACK;
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
    size = 0;
}

int main()
{
    std::cout << "The end." << std::endl;
}

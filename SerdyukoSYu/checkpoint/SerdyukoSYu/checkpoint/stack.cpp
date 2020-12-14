#include <iostream>



class Stack
{
public:
    int pop();
    void push(int value);
public:
    Stack();
    ~Stack();
private:
    const int stackmax=1000;
    const int erorstack=101;
    int data[stackmax];
    size_t size;
};

int Stack::pop()
{
    if (size == 0)
        return erorstack;
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
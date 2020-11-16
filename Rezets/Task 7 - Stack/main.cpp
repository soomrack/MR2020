#include <iostream>

#define STACK_MAX_SIZE 1000

class Stack
{
public:
    int pop()
    {
        size--;
        return data[size];
    }
    
    void push(int value)
    {
        data[size] = value;
        size++;
    }
public:
    Stack()
    {
        size = 0;
    }
    
    ~Stack()
    {
        while (size)
            pop();
    }
private:
    int data[STACK_MAX_SIZE];
    size_t size;
};

int main()
{
    std::cout << "The end." << std::endl;
}

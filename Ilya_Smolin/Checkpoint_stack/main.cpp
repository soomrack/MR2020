#include <iostream>

int const errorcode = -666;

class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};


struct Elem
{
    int value;
    struct Elem* next;
};

struct Elem *Top;


int Stack::pop()
{
    if (Top == nullptr)
        return (errorcode);
    struct Elem *pointer;
    int answer;
    pointer = Top;
    answer = pointer->value;
    Top = pointer->next;
    delete pointer;
    return answer;
}


void Stack::push(const int value)
{
    struct Elem *pointer;
    pointer= new struct Elem;
    pointer->value = value;
    pointer->next = Top;
    Top = pointer;
}


Stack::Stack()
{
    Top = nullptr;
}


Stack::~Stack()
{
    while(Top != nullptr)
        pop();
}


int main() {
    Stack mystack;
    mystack.push(22);
    mystack.push(5);
    mystack.push(8);
    int top = mystack.pop();
    printf("%d\n",top);
    top = mystack.pop();
    printf("%d\n",top);
    top = mystack.pop();
    printf("%d\n",top);
    printf("%d\n",mystack.pop());
}
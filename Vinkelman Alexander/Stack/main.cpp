#include <iostream>

int const CODE_OF_ERROR = -1000;

class Stack {
public:
    int stack_pop();
    void stack_push(const int value);
public:
    Stack();
    ~Stack();
};

struct Stack_Element {
    int stack_value;
    struct Stack_Element* next;
};

struct Stack_Element *Top;

int Stack::stack_pop() {
    if (Top == nullptr) {
        return (CODE_OF_ERROR);
    }
    struct Stack_Element *pointer;
    int answer;
    pointer = Top;
    answer = pointer -> stack_value;
    Top = pointer -> next;
    delete pointer;
    return answer;
}

void Stack::stack_push(const int value)
{
    struct Stack_Element *pointer;
    pointer = new struct Stack_Element;
    pointer -> stack_value = value;
    pointer -> next = Top;
    Top = pointer;
}

Stack::Stack()
{
    Top = nullptr;
}

Stack::~Stack()
{
    while(Top != nullptr)
        stack_pop();
}

int main() {

    return 0;
}

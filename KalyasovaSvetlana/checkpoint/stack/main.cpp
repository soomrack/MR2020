#include <iostream>
const int err = 666666666;

class Stack {
private:
    struct stack;
    struct stack *peak;
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};

struct Stack::stack{
    int value;
    struct stack *next;
};

Stack::~Stack() {
    while (peak) {
        stack *element = peak;
        peak = peak->next;
        delete(element);
    }
}

int Stack::pop(){
    if (!peak)
        return err;
    int temp = peak->value;
    stack *MyStack = peak;
    peak = peak->next;
    delete MyStack;
    return temp;
}

Stack::Stack() {
    peak = nullptr;
}

void Stack::push(const int value) {
    stack *MyStack = new stack;
    MyStack->value = value;
    MyStack->next = peak;
    peak = MyStack;
}

int main() {
    std::cout << "The end." << std::endl;
}


#include <iostream>
#include <stack>

const int error = 000;

class Stack {

public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
}

struct Element
{
    int value;
    struct Element* next;
};

struct Element* Top;

void Stack::push(const int value) {
    struct Element* point;
    point = new Element;
    point->value = value;
    point->next = Top;
    Top = point;
}

int Stack::pop() {
    if (Top == nullptr) {
        return error;
    }
    int temp = Top->value;
    Element* pointer = Top;
    Top = Top->next;
    delete pointer;
    pointer = nullptr;
    return temp;
}

Stack::Stack() {
    Top = nullptr;
}

Stack::~Stack() {
    while (Top != nullptr) {
        Element* pointer = Top;
        Top = Top->next;
        delete pointer;
    }
}

int main() {
    std::cout << "The end." << std::endl;
}  
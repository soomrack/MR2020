#include <iostream>
const int ERR0R = 2147483647;

class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};

struct element {
    int value;
    struct element *next;
};
struct element *top;

int Stack::pop(){
    if (top == nullptr){return ERROR;}
    int temp = top -> value;
    element *pointer = top;
    top = top -> next;
    delete pointer;
    pointer = nullptr;
    return temp;
};

void Stuck::push(const int value){
    element *pointer = nullptr;
    pointer = new element;
    pointer -> value = value;
    pointer -> next = top;
    top = poiner;
};

Stack::Stack(){
    top = nullptr;
};

Stack::~Stack(){
    while (top != nullptr){
        element *pointer = top;
        top = top -> next;
        delete pointer;
    }
};

int main() {
    std::cout << "The end." << std::endl;
}
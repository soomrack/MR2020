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
    element *poiner = top;
    top = top -> next;
    delete poiner;
    poiner = nullptr;
    return temp;
};

void Stuck::push(const int value){
    element *poiner = nullptr;
    poiner = new element;
    poiner -> value = value;
    poiner -> next = top;
    top = poiner;
};

Stack::Stack(){
    top = nullptr;
};

Stack::~Stack(){
    while (top != nullptr){
        element *poiner = top;
        top = top -> next;
        delete poiner;
    }
};

int main() {
    std::cout << "The end." << std::endl;
}
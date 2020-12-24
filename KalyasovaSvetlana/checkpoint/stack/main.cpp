#include <iostream>
const int err = 666666666;

struct Node{
    int value;
    Node *next;
};

class Stack {
private:
    Node *peak;
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};


Stack::~Stack() {
    while (peak) {
        Node *element = peak;
        peak = peak->next;
        delete(element);
    }
}

int Stack::pop(){
    if (!peak)
        return err;
    int temp = peak->value;
    Node *MyStack = peak;
    peak = peak->next;
    delete MyStack;
    return temp;
}

Stack::Stack() {
    peak = nullptr;
}

void Stack::push(const int value) {
    Node *MyStack = new Node;
    MyStack->value = value;
    MyStack->next = peak;
    peak = MyStack;
}

int main() {
    std::cout << "The end." << std::endl;
}

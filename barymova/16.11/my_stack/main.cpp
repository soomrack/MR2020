#include <iostream>

class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();

private:
    struct Node {
        int value;
        Element *next;
    };
    Node *top;
};

Stack::Stack(){
    top = nullptr;
}

void Stack::push(const int value) {
    Node *newNode = nullptr;
    newNode = new Node;
    newNode -> value = value;
    newNode -> next = top;
    top = newNode;
}

int Stack::pop() {
    if (top == nullptr){
        return -1;
    }
    int temporary = top -> value;
    Node *tempNode = top;
    top = top -> next;
    delete newNode;
    return temporary;
}


Stack::~Stack() {
    while (top != nullptr){
        Node *tempNode = top;
        top = top -> next;
        delete tempNode;
    }
}

int main() {
    std::cout << "The end." << std::endl;
}

#include <iostream>

class Stack {
private:
    const int POP_ERROR = -42;
    struct Node;
    Node* top;

public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};

struct Stack::Node {
    int content;
    Node* point;
};

int Stack::pop() {
    if (!top) {
        return POP_ERROR;
    }
    int end = top->content;
    Node* targetNode = top;
    top = top->point;
    delete targetNode;
    return end;
}

void Stack::push(const int value) {
    Node* temp;
    temp = new Node;
    temp->content = value;
    temp->point = top;
    top = temp;
};

Stack::Stack():top(NULL){}

Stack::~Stack() {
    while (top) {
        Node* half = top;
        top = top->point;
        delete (half);
    }
}

int main() {
    Stack go_check;
    go_check.push(22);
    go_check.push(7);
    go_check.pop();
    int element = go_check.pop();

    std::cout << element <<"The end." << std::endl;

    go_check.~Stack();
}
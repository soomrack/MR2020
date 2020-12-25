#include <iostream>
const int POP_ERROR = -1;

class Stack {
private:
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

Stack::Stack() :top(NULL) {}

Stack::~Stack() {
    while (top) {
        Node* half = top;
        top = top->point;
        delete (half);
    }
}
int main() {
    std::cout << "The end" << std::endl;
}
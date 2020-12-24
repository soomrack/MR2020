#include <iostream>
const int error = 2147483647;

struct Node{
    int value;
    Node* next;
};


class Stack {
private:
    Node* top;
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};


int Stack::pop() {
    struct Node* temp;
    temp = new Node;
    if (!top) {
        return error;
    }
    int end = top->value;
    temp = top;
    top = top->next;
    temp->next = nullptr;
    delete (temp);
    return end;
}

void Stack::push(const int value) {
    struct Node* temp;
    temp = new Node();
    temp->value = value;
    temp->next = top;
    top = temp;
}

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    while (top) {
        Node *delTop = top;
        top = top ->next;
        delete (delTop);
    }
}


int main() {
    Stack letsCheck;
    letsCheck.push(228);
    letsCheck.push(1488);
    letsCheck.push(666);
    letsCheck.pop();
    int element = letsCheck.pop();
    printf("%d\n",element);
    std::cout <<"The end." << std::endl;
}

#include <iostream>
const int error = 2147483647;

class Stack {
private:
    struct Node;
    struct Node* top;
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};


struct Stack::Node {
    int value;
    struct Node* next;
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
    Stack letscheck;
    letscheck.push(228);
    letscheck.push(1488);
    letscheck.push(666);
    letscheck.pop();
    int element = letscheck.pop();
    printf("%d\n",element);
    std::cout <<"The end." << std::endl;
}
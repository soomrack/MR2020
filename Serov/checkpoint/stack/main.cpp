#include <iostream>

class Stack {
private:
    struct Node {
        int value;
        struct Node* link;
    };
    struct Node* top;
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};

int Stack ::pop() {
    struct Node* temp;
    temp = new Node;
    if (!top) {
        return 2147483647;
    }
    int end = top->value;
    temp = top;
    top = top->link;
    temp->link = nullptr;
    free (temp);
    return end;
}

void Stack  ::push(const int value) {
    struct Node* temp;
    temp = new Node();
    temp->value = value;
    temp->link = top;
    top = temp;
}

Stack ::Stack() {
    top = nullptr;
}

Stack ::~Stack() {
    {
        while (top) {
            Node *half = top;
            top = top ->link;
            free (half);
        }
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
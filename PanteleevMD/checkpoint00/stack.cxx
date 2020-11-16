#include <iostream>


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();

private:
    struct Node
    {
        int content;
        Node *point;
    };
    Node *top;
};

Stack::Stack() //:top(NULL) 
{
    top = NULL;
}

void Stack::push(const int value)
{
    Node *nwel = new Node;
    nwel->content = value;
    nwel->point = top;
    top = nwel;
}

int Stack::pop()
{
    int temp = top->content;
    Node *nwel = top;
    top = top->point;
    delete nwel;
    return temp;
}

Stack::~Stack()
{
    while (top) {
        Node *nwel = top;
        top = top->point;
        delete nwel;
    }
}




int main() {
    Stack makeshiftStack;
    makeshiftStack.push(5);
    makeshiftStack.push(4);
    makeshiftStack.push(3);
    makeshiftStack.push(2);
    makeshiftStack.pop();
    makeshiftStack.pop();
    int last = makeshiftStack.pop();

    std::cout << last << " The end." << std::endl;

    makeshiftStack.~Stack();
}

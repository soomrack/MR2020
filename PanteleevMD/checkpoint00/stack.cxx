#include <iostream>

#define POP_ERROR -42;

struct Node
{
    int content;
    Node *point;        //pointer to previous element
};

class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    Node *top;
};

Stack::Stack() :top(NULL) {}


void Stack::push(const int value)
{
    Node *nwel = new Node;
    nwel->content = value;
    nwel->point = top;
    top = nwel;
}

int Stack::pop()
{
    if (!top)       //emptiness check
    {
        return -42;             //magic exit code
    }
    int value = top->content;
    Node *targetNode = top;
    top = top->point;
    delete targetNode;

    return value;
}

Stack::~Stack()
{
    while (top) {           //until top = NULL
        Node *targetNode = top;
        top = top->point;
        delete targetNode;
    }
}



int main() {
    Stack makeshiftStack;
    makeshiftStack.push(5);
    makeshiftStack.push(4);
    //makeshiftStack.push(3);
    //makeshiftStack.push(2);
    makeshiftStack.pop();
    makeshiftStack.pop();
    int last = makeshiftStack.pop();

    std::cout << last << " The end." << std::endl;

    makeshiftStack.~Stack();
}

#include <iostream>

class Stack {

public:
    int pop();
    void push(int value);
    Stack();
    ~Stack();
    bool isEmpty();

private:
    struct node {
        int d;
        node *p;
    };
    node *top;
};

Stack::Stack() :top(nullptr) {}

void Stack::push(const int value)
{
    node *pv = new node;
    pv->d = value;
    pv->p = top;
    top = pv;
}

int Stack::pop()
{
    if (isEmpty())
    {
        return -1;
    }
    int temp = top->d;
    node *pv = top;
    top = top->p;
    delete pv;
    return temp;
}

bool Stack::isEmpty()
{
    return top ? false : true;
}


Stack::~Stack()
{
    while (top)
    {
        node *pv = top;
        top = top->p;
        delete pv;
    }
}

int main()
{
    std::cout << "The end." << std::endl;
}

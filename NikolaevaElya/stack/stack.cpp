#include <iostream>
using namespace std;

struct element {
    int value;              // a value on the stack
    element *nextElement;   //a pointer to the next element on the stack
};

class Stack {
    public:
        int pop();
        void push(const int value);
    public:
        Stack();
        ~Stack();
    private:
        element *top;
};

Stack::Stack() :top(nullptr){};

Stack::~Stack(){
    while(top != nullptr){
        element *elementNow = top;
        top = top->nextElement;
        delete elementNow;
    }
}

int Stack::pop(){
    if(!top){
        return -1;
    }
    int value = top->value;
    element *elementNow = top;
    top = top -> nextElement;
    delete elementNow;
    
    return value;
}

void Stack::push(const int value){
    element *newElement = new element;
    newElement->value = value;
    newElement->nextElement = top;
    top = newElement;
}


int main() {
    Stack check;
    check.push(6);
    check.push(8);
    check.push(3);
    check.pop();
    int a = check.pop();
    cout << a << endl;
}
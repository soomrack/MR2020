#include <iostream>
using namespace std;

#define ERROR_OCCURED -1488

struct component{
    int value; // a value of the component
    component *nextComponent; // a pointer to the next component
};

class Stack{
    public:
        int pop();
        void push(const int value);
        Stack();
        ~Stack();
    private:
        component *top;
};

Stack::Stack() :top(nullptr){}

Stack::~Stack(){
    while (top){
        component *currentComponent = top;
        top = top->nextComponent;
        delete currentComponent;
    } 
}

int Stack::pop(){
    if (top == nullptr){
        return ERROR_OCCURED;
    }
    int value = top->value;
    component *currentComponent = top;
    top = top->nextComponent;
    delete currentComponent;

    return value;
}

void Stack::push(const int value){
    component *newComponent = new component;
    newComponent->value = value;
    newComponent->nextComponent = top;
    top = newComponent;
}

int main() {
    Stack myStack;

    myStack.push(5);
    myStack.push(4);
    myStack.push(3);
    myStack.pop();
    myStack.pop();
    int a = myStack.pop();
    cout << a << endl;
}
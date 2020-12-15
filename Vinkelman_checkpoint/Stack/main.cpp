#include <iostream>
using namespace std;

class Stack{
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();

private:
    struct Znach{
        int v;
        Znach *p;
    };
    Znach *top;
};

Stack::Stack() {
    top = nullptr;
}

void Stack::push(const int value) {
    Znach *pp = nullptr;
    pp = new Znach;
    pp -> v = value;
    pp -> p = top;
    top = pp;
}

int Stack::pop() {
    if (top == nullptr){
        return -1;
    }
    int value = top -> v;
    Znach *pp = top;
    top = top -> p;
    delete pp;
    pp = nullptr;
    return value;
}

Stack::~Stack() {
    while (top != nullptr){
        Znach *pp = top;
        top = top -> p;
        delete pp;
        pp = nullptr;
    }
}

int main() {
    cout << "The end." << endl;
    return 0;
}

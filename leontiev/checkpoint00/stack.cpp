#include <iostream>

const int EMPTY_STACK = -1; //учёл пустой стек

class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    int top;
    int* data;
};


int main() {
    Stack stk;

    stk.push(11);
    stk.push(111);
    stk.push(1111);
    stk.push(33333);

    std::cout << stk.pop() << ' ' << stk.pop() << ' ' << stk.pop() << ' ' << stk.pop();
    std::cout << "\nThe end." << std::endl;
    return 0;
}


Stack::Stack() {
    this->top = 0;
    this->data = new int[1];
    this->data[0] = 0;
}

Stack::~Stack() {
    this->top = 0;
    delete[] this->data;
}

void Stack::push(const int value) {
    this->top++;
    int* copy = new int[this->top];
    for (int i = 0; i < this->top - 1; i++) {
        copy[i] = this->data[i];
    }
    delete[] this->data;
    this->data = copy;
    this->data[this->top - 1] = value;

}

int Stack::pop() {
    if (!top){                   //учёл пустой стек
        return EMPTY_STACK;      //учёл пустой стек
    }                            //учёл пустой стек
    this->top--;
    int elem = this->data[this->top];
    int* copy = new int[this->top];
    for (int i = 0; i < this->top; i++) {
        copy[i] = this->data[i];
    }
    delete[] this->data;
    this->data = copy;
    return elem;

}

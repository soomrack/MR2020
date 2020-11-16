#include <iostream>


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};



int main() {
    std::cout << "The end." << std::endl;
}

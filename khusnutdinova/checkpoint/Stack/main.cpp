#include <iostream>


class Stack {
private:
    struct element {
        int value;
        element *Next;
    };
    element *top;
public:
    int pop(){
        if (top == nullptr){
            return 2147483647;
        }
        int temp = top -> value;
        element *pointer = top;
        top = top -> Next;
        delete pointer;
        pointer = nullptr;
        return temp;
    };

    void push(const int value){
        element *pointer = nullptr;
        pointer = new element;
        pointer -> value = value;
        pointer -> Next = top;
        top = pointer;
    };

    Stack(){
        top = NULL;
    };

    ~Stack(){
        while (top != nullptr){
            element *pointer = top;
            top = top -> Next;
            delete pointer;
            pointer = nullptr;
        }
    };
};

int main() {
    std::cout << "The end." << std::endl;
}
#include <iostream>
const int ERR0R = 2147483647;

struct element {
    int value;
    struct element *Next;
};

struct element *top;

class Stack {
public:
    int pop(){
        if (top == nullptr){return ERROR;}
        int temp = top -> value;
        element *poiner = top;
        top = top -> Next;
        delete poiner;
        poiner = nullptr;
        return temp;
    };

    void push(const int value){
        element *poiner = nullptr;
        poiner = new element;
        poiner -> value = value;
        poiner -> Next = top;
        top = poiner;
    };

    Stack(){
        top = NULL;
    };

    ~Stack(){
        while (top != nullptr){
            element *poiner = top;
            top = top -> Next;
            delete poiner;
            poiner = nullptr;
        }
    };
};

int main() {
    std::cout << "The end." << std::endl;
}
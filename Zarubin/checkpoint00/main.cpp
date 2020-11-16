#include <iostream>


class Stack {
public:
    int pop(){
        if (top == nullptr){
            return 2147483647;
        }
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

private:
    struct element {
        int value;
        element *Next;
    };

    element *top;
};

int main() {
    std::cout << "The end." << std::endl;
}
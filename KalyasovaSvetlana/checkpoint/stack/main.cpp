#include <iostream>


class Stack {
private:
    struct stek
    {
        int value;
        struct stek *next;
    };
    struct stek *NEXT;
public:
    int pop(){
        int temp = NEXT->value;
        stek *MyStack = NEXT;
        NEXT = NEXT->next;
        delete MyStack;
        return temp;
    }
    void push(const int value){
        stek *MyStack = new stek;
        MyStack->value = value;
        MyStack->next = NEXT;
        NEXT = MyStack;
    };
public:
    Stack(){
        NEXT = NULL;
    };
    ~Stack() {
        while (NEXT) {
            stek *element = NEXT;
            NEXT = NEXT->next;
            free(element);
        }
    }
};



int main() {
    std::cout << "The end." << std::endl;
}
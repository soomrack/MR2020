#include <iostream>
#include <stack>

class Stack {

public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    struct Element
    {
        int a;
        struct Element* next;
    };
    struct Element* Top;
};


void Stack::push(const int value) {
    struct Element* poin;
    poin = new Element;
    poin->a = value;
    poin->next = Top;
    Top = poin;
}

int Stack::pop() {
    if (Top == nullptr) {      
        return 000;
    }
    int temp = Top->a;
    Element* pp = Top;       
    Top = Top->next;           
    delete pp;              
    pp = nullptr;            
    return temp;        
}

Stack::Stack() {
    Top = nullptr;
}
Stack::~Stack() {
    while (Top != nullptr) {
        Element* pp = Top;
        Top = Top->next;
        delete pp;
        pp = nullptr;
    }
}
int main() {
    std::cout << "The end." << std::endl;
}

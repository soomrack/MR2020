#include <iostream>


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();

private:
    struct Element {
        int v;
        Element* p;
    };

    Element* top;
};

//Создание стэка
Stack::Stack() {
    top = nullptr;
}

//Добавление нового элемента
void Stack::push(const int value) {
    Element* pp = nullptr;     
    pp = new Element;          
    pp->v = value;           
    pp->p = top;             
    top = pp;                  
}

//Изьятие верхнего элемента из стэка
int Stack::pop() {
    if (top == nullptr) {      
        return -1;
    }
    int temporary = top->v; 
    Element* pp = top;        
    top = top->p;           
    delete pp;                
    pp = nullptr;             
    return temporary;         
}

//Высвобождение стэка
Stack::~Stack() {
    while (top != nullptr) {
        Element* pp = top;        
        top = top->p;           
        delete pp;                
        pp = nullptr;             
    }
}

int main() {
    std::cout << "The end." << std::endl;
}
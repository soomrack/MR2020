#include <iostream>


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    int top;
    int * data;
};




int main() {


    Stack stk;

    // Тестики
    stk.push(1);
    stk.push(313);
    stk.push(1);
    stk.push(313);

    std::cout << stk.pop() << ' ' << stk.pop() << ' ' << stk.pop() << ' ' << stk.pop();

    return 0;
}


// Конструктор стека при инициализвции без аргументов
Stack::Stack(){
    this->top = 0;
  
    this->data = new int[ 1 ];
    this->data[0] = 0;
}

// Деструктор стека - вызывается при завершении времени жизни объекта (например - закрылась скобка области видимости)
Stack::~Stack(){
    this->top = 0;
    delete [] this->data;
}

void Stack::push(const int value){
        
        this->top++;
        int * copy = new int[this->top];
        for (int i = 0; i < this->top-1; i++){
            copy[i] = this->data[i];
        }
        delete [] this->data;
        this->data = copy;
        this->data[this->top-1] = value;
            
}

int Stack::pop(){

    this->top--;
    int elem =  this->data[this->top];
    int * copy = new int[this->top];
    for (int i = 0; i < this->top; i++){
        copy[i] = this->data[i];
    }
    delete [] this->data;
    this->data = copy;
    return elem;

}
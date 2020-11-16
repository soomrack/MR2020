#include <iostream>


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    int top_;
    int * data_;
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
    this->top_ = 0;
    // в целом вообще это не надо, но я не знаю как иницилизировать массив без это.
    this->data_ = new int[ 1 ];
    this->data_[0] = 0;
}

// Деструктор стека - вызывается при завершении времени жизни объекта (например - закрылась скобка области видимости)
Stack::~Stack(){
    this->top_ = 0;
    delete [] this->data_;
}

void Stack::push(const int value){
        #warning нет проверки на переполение стека вызовов 
        this->top_++;
        int * copy = new int[this->top_];
        for (int i = 0; i < this->top_-1; i++){
            copy[i] = this->data_[i];
        }
        delete [] this->data_;
        this->data_ = copy;
        this->data_[this->top_-1] = value;
        
}

int Stack::pop(){

    this->top_--;
    int elem =  this->data_[this->top_];
    int * copy = new int[this->top_];
    for (int i = 0; i < this->top_; i++){
        copy[i] = this->data_[i];
    }
    delete [] this->data_;
    this->data_ = copy;
    return elem;

}
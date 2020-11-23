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

    return 0;
}

Stack::Stack(){
    this->top_ = 0;
    this->data_ = new int[ 1 ];
    this->data_[0] = 0;
}

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
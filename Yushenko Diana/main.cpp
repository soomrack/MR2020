#include <iostream>
#define ERROR -100;
using namespace std;

struct Elem {
    int value;
    Elem *NextElem;
};

class Stack {
    public:
        int pop();
        void push(const int value);
    public:
        Stack();
        ~Stack();
    private:
        Elem *top;
};

Stack::Stack() {
    top = nullptr;
};

int Stack::pop(){
    if(!top){
        return ERROR;
    }
    int value = top -> value;
    Elem *elementNow = top;
    top = top -> NextElem;
    delete elementNow;

    return value;
}

void Stack::push(const int value){
    Elem *NewElem = new Elem;
    NewElem -> value = value;
    NewElem -> NextElem = top;
    top = NewElem;
}

Stack::~Stack(){
    while(top != nullptr){
        Elem *NowElem = top;
        top = top->NextElem;
        delete NowElem;
    }
}


int main() {
    Stack checking;
    checking.push(4);
    checking.pop();
    checking.push(21);
    checking.push(74);
    checking.pop();
    int check = checking.pop();
    cout << check << endl;   //result is 21
}

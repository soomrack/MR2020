#include <iostream>

const int EMPTY_STACK = -1;

struct Node{
    int data;   
    Node * prev; // pointer to the previous node
};


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    // int top;
    // int * data;
    Node * top;
};


Stack::Stack() :top(NULL) {}


Stack::~Stack(){

    while(top){
        Node * nodeToDelete = top;
        top = top->prev;
        delete nodeToDelete;
    }

}


void Stack::push(const int value){

    Node * newNode = new Node;
    newNode->data = value;
    newNode->prev = top;
    top = newNode;

}


int Stack::pop(){

    if (!top){
        return EMPTY_STACK;
    }

    int value = top->data;
    Node * currentNode = top;
    top = top->prev;
    delete currentNode;

    return value;

}


int main() {

    Stack stk;

    // Тестики
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);

    std::cout << stk.pop() << ' ' << stk.pop() << ' ' << stk.pop() << ' ' << stk.pop();

    return 0;
}

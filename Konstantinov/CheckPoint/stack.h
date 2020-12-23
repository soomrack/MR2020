//
// Created by alex on 09.12.2020.
//

#ifndef CPP_CHECKPOINT_STACK_H
#define CPP_CHECKPOINT_STACK_H
#define STACK_MEMORY_FAULT -100
#include <iostream>

class Stack_Node {
public:
    int value;
    Stack_Node* next;

public:
    Stack_Node()= default;
    Stack_Node(int value, Stack_Node* next);
    ~Stack_Node()= default;
};


class Stack {
public:
    int pop();
    void push(int value);
public:
    Stack();
    ~Stack();
private:
    Stack_Node* stack_pointer;
};



#endif //CPP_CHECKPOINT_STACK_H

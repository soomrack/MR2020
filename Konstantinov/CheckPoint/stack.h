//
// Created by alex on 09.12.2020.
//

#ifndef CPP_CHECKPOINT_STACK_H
#define CPP_CHECKPOINT_STACK_H

#include <iostream>

class Stack_Node {
public:
    int value;
    Stack_Node* next;

public:
    Stack_Node();
    Stack_Node(const int value, Stack_Node* next);
    ~Stack_Node();
};


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    Stack_Node* stack_pointer;

};



#endif //CPP_CHECKPOINT_STACK_H

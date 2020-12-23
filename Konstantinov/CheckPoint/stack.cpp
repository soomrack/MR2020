//
// Created by alex on 09.12.2020.
//

#include "stack.h"


int Stack::pop(){
    if(this->stack_pointer == nullptr){
        exit(STACK_MEMORY_FAULT);
    }
    int popped = this->stack_pointer->value;
    Stack_Node* old_sp = this->stack_pointer;
    this->stack_pointer = this->stack_pointer->next;
    delete old_sp;
    return popped;
}


void Stack::push(const int value){
    Stack_Node* prev_sp = this->stack_pointer;

    this->stack_pointer = new Stack_Node(value, prev_sp);

    if(this->stack_pointer == nullptr){
        this->stack_pointer = prev_sp;
        delete this;
        exit(STACK_MEMORY_FAULT);
    }
}

Stack::Stack(){
    this->stack_pointer = nullptr;
}

Stack::~Stack(){
    while(this->stack_pointer != nullptr){
        pop();
    }
}


Stack_Node::Stack_Node(int value, Stack_Node* next){
    this->value = value;
    this->next = next;
}
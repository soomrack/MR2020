//
// Created by alex on 09.12.2020.
//

#include "list.h"

List::List(){
    this->root = NULL;

}

List::~List() {


}


Iterator List::begin() {
    Iterator iter(*this);
    return iter;
 }

 Iterator::Iterator(List &list) {
    this->current = list.root;
    this->prev = NULL;
}

Iterator::~Iterator() {

}

void Iterator::next() {

}


void Iterator::insert(const int value) {

    List_Node* new_node;

    if(this->current->next != NULL) {
        new_node = new List_Node(value, this->current->next);
    }
    else
        new_node = new List_Node(value);

    if(new_node == NULL){
        exit(-1);
    }

    this->prev = this->current;
    this->current = new_node;

}

int Iterator::get_value() {
    return this->current->value;
}


void Iterator::set_value(const int value) {

    this->current->value = value;

}

void Iterator::del() {

    if(this->current->next == NULL) {
        delete this->current;
        this->current = this->prev;
        return;
    }

    List_Node* to_be_deleted = this->current;

    this->current = to_be_deleted->next;
    this->prev->next = this->current;

    delete to_be_deleted;
}

List_Node::List_Node(int value, List_Node *next){
    this->value = value;
    this->next = next;

}
List_Node::List_Node(int value){
    this->value = value;
    this->next = NULL;
}

List_Node::List_Node(){

}

List_Node::~List_Node() {

}
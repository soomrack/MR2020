#include <iostream>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


class Stack;
class List;

class NodeList {
public:
    int value;
    bool isSymbol;
    NodeList *next;
    NodeList *prev;
public:
    NodeList(int value, bool isDigit);
    NodeList(int value, NodeList *next, bool isDigit);
};


class Iterator {
private:
    NodeList *prev;
    List *head;
public:
    NodeList *current;
    Iterator previous();
    Iterator next();
    int get_value();
    void set_value(const int value);
    bool getIsNodeDigit ();
    Iterator makePolishCode (const char* formula, Iterator iterator, Stack myStack);
public:
    void insert_before(const int value);
    void insert_after (const int value, bool isDigit);
    void del();
public:
    Iterator();
    Iterator (List &head);
};


class List {
private:
    friend class Iterator;
    NodeList *root;
public:
    Iterator begin();
public:
    List();
    ~List();
};

NodeList::NodeList(int value, bool isDigit){
    this->value = value;
    next = nullptr;
    prev = nullptr;
    this->isSymbol = isDigit;
}

NodeList::NodeList(int value, NodeList *next, bool isDigit) {
    this->value = value;
    this->next = next;
    prev = nullptr;
    this->isSymbol = isDigit;
}


Iterator::Iterator(){
    current = head->root;
    prev = nullptr;
}

Iterator::Iterator (List &root){
    head = &root;
    current = head->root;
    prev = nullptr;
}

void Iterator::insert_after (const int value, bool isDigit) {
    if (current == nullptr){
        current = new NodeList (value, current, isDigit);
        head->root = current;
        return;
    }
    current->next = new NodeList (value, current->next, isDigit);
    current->next->prev = current;
}

void Iterator::del() {
    if (current != nullptr && prev != nullptr)
    {
        current->prev->next = current->next;
        delete current;
        current = prev->next;
        return;
    }

    if (prev == nullptr && current != nullptr)
    {
        head->root = current->next;
        delete current;
        current = head->root;
        return;
    }
}

int Iterator::get_value() {
    if (current == nullptr)
        return 66666666;
    return current->value;
}

void Iterator::set_value(const int value) {
    if (current == nullptr) return;
    current->value = value;
    current->isSymbol = true;
}

Iterator Iterator::next() {
    if (current != nullptr){
        prev = current;
        current = current->next;
    }
    return *this;
}

Iterator Iterator::previous() {
    if ((current != nullptr) && (current->prev != nullptr)) {
        prev = current->prev->prev;
        current = current->prev;
    }
    return *this;
}

bool Iterator::getIsNodeDigit() {
    return current->isSymbol;
}

Iterator List::begin(){
    Iterator begin(*this);
    return begin;
}

List::List() {
    root = nullptr;
}

List::~List() {
    Iterator toDelete = begin();
    while (root != nullptr)
        toDelete.del();
}

const int error = 2147483647;

int getPriority (char symbol){
    int priority;
    if (symbol == '+')
        priority = 1;
    if (symbol == '-')
        priority = 1;
    if (symbol == '*')
        priority = 2;
    if (symbol == '/')
        priority = 2;
    if (symbol == '(')
        priority = 0;
    return priority;
}

bool isDigit (char symbol){
    if (symbol == '+')
        return false;
    if (symbol == '-')
        return false;
    if (symbol == '/')
        return false;
    if (symbol == '*')
        return false;
    if (symbol == '(')
        return false;
    if (symbol == ')')
        return false;
    return true;
}

bool isBinaryOperation (char symbol){
    if (symbol == '+')
        return true;
    if (symbol == '-')
        return true;
    if (symbol == '/')
        return true;
    if (symbol == '*')
        return true;
    return false;
}

int transferOperations (char symbol){
    if (symbol == '+')
        return 1;
    if (symbol == '-')
        return 2;
    if (symbol == '/')
        return 3;
    if (symbol == '*')
        return 4;
    return 0;
}

struct Node {
    char symbol;
    int priority;
    Node* next;
};


class Stack {
private:
public:
    Node* top;
    void pop(Iterator iterator);
    void push(char value);
    void pushWithPriority(char value, Iterator iterator);
public:
    Stack();
    ~Stack();
};


void Stack::pop(Iterator iterator) {
    struct Node* temp;
    temp = new Node;
    if (!top) {
        return;
    }

    if (top->symbol != '(') {
        int numberOfOperation = transferOperations(top->symbol);
        iterator.insert_after(numberOfOperation, false);
        iterator.next();
    }

    temp = top;
    top = top->next;
    temp->next = nullptr;
    delete (temp);
}

void Stack::push(char value) {
    struct Node* temp;
    temp = new Node();
    temp->symbol = value;
    temp->next = top;
    temp->priority = getPriority(value);
    top = temp;
}

void Stack::pushWithPriority(char value, Iterator iterator) {
    if (top == nullptr){
        push(value);
        return;
    }

    if (value == ')') {
        if (top->symbol != '('){
            pop(iterator);
            iterator.next();
            return pushWithPriority(value,iterator);
        }
        pop(iterator);
        return;
    }

    if (top->priority >= getPriority(value)) {
        pop(iterator);
        iterator.next();
        return pushWithPriority(value, iterator);
    }
    push(value);
}

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    while (top) {
        Node *delTop = top;
        top = top ->next;
        delete (delTop);
    }
}

Iterator Iterator:: makePolishCode (const char* formula, Iterator iterator, Stack myStack){
    int j = 0;
    int arrIndex = 0;
    int formulaIndex = 0;
    int end = strlen(formula);
    int tempArray[end];
    tempArray[0] = 0;
    int numberToPushOut = 0;
    while (formulaIndex <= end){
        if (iterator.current != nullptr){
            while (iterator.current->next != nullptr)
                iterator.next();
        }
        if (((tempArray[0] != 0) && (formulaIndex > end-1)) || ((!isDigit(formula[formulaIndex])) && (tempArray[0] != 0))) {
            while (arrIndex > 0) {
                arrIndex --;
                numberToPushOut = numberToPushOut+tempArray[arrIndex]*pow(10,j);
                tempArray[arrIndex] = 0;
                j++;
            }
            if (iterator.current == nullptr)
                iterator.insert_after(numberToPushOut, true);
            else {
                iterator.insert_after(numberToPushOut, true);
                iterator.next();
            }
            j = 0;
            arrIndex = 0;
            numberToPushOut = 0;
        }

        if (formulaIndex > end-1)
            break;

        if (isDigit(formula[formulaIndex])){
            tempArray[arrIndex] = (int) formula[formulaIndex] - (int) '0';
            formulaIndex ++;
            arrIndex ++;
            continue;
        }



        if (isBinaryOperation(formula[formulaIndex])){
            myStack.pushWithPriority(formula[formulaIndex],iterator);
            formulaIndex ++;
            continue;
        }

        if (formula[formulaIndex] == '('){
            myStack.push(formula[formulaIndex]);
            formulaIndex ++;
            continue;
        }

        if (formula[formulaIndex] == ')'){
            myStack.pushWithPriority(formula[formulaIndex], iterator);
            formulaIndex ++;
            continue;
        }
    }

    while (myStack.top != nullptr){
        myStack.pop(iterator);
        iterator.next();
    }
    return iterator;
}

int counting (int a, int b, int operationCode){
    if (operationCode == 1)
        return a+b;
    if (operationCode == 2)
        return a-b;
    if (operationCode == 3)
        return a/b;
    if (operationCode == 4)
        return a*b;
    return 0;
}

int calculate (Iterator iterator){
    int result = 0;
    while (iterator.current != nullptr){
        if (iterator.getIsNodeDigit() == false){
            int operationCode = iterator.get_value();
            iterator.previous();
            int b = iterator.get_value();
            iterator.previous();
            int a = iterator.get_value();
            result = counting(a,b,operationCode);
            iterator.set_value(result);
            if (iterator.current->next->next->next == nullptr)
                return result;
            iterator.current->next = iterator.current->next->next->next;
            iterator.current->next->prev = iterator.current;
            if (iterator.current->next == nullptr)
                return result;
        }
        iterator.next();
    }
    return result;
}

int main()
{
    Stack myStack;
    List list;
    Iterator iterator = list.begin();
    iterator = iterator.makePolishCode("(5-3)*2+((4-3)-5)+9*(6+12/3)",iterator,myStack);
    while (iterator.current->prev != nullptr)
        iterator.previous();
    int result = calculate(iterator);
    printf("%d",result);
}
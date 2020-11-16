#include <iostream>


class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
private:
    struct Elem
    {
        int c;
        struct Elem* next;
    };
    struct Elem *Top;
};

int Stack::pop() {
    if (Top == nullptr){      //Проверка, что в стеке что-то есть
        return -666;
    }
    struct Elem *pointer;
    int a;
    pointer = Top; //указатель будет ссылаться на адрес вершины стека
    a=pointer->c; //а присвоим то, что было на вершине стека
    Top = pointer->next; //элемент, следующий за вершиной стал вершиной стека
    delete pointer;
    return a; //возвращаем вершину стека
}
void Stack::push(const int value) {
    struct Elem *pointer;
    pointer= new struct Elem;
    pointer->c = value;
    pointer->next = Top;
    Top = pointer;
}
Stack::Stack() {
    Top = nullptr;
}
Stack::~Stack() {
    while(Top != nullptr)
        pop();
}
int main() {
    std::cout << "The end." << std::endl;
}
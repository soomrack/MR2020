#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>


class Stack {
public:
    int pop()
    {
        if (Top == nullptr){      //Проверка, что в стеке что-то есть
            return -666;
        }
        struct Elem *pointer;
        char a;
        pointer = Top; //указатель будет ссылаться на адрес вершины стека
        a=pointer->c; //а присвоим то, что было на вершине стека
        Top = pointer->next; //элемент, следующий за вершиной стал вершиной стека
        delete pointer;
        return a; //возвращаем вершину стека
    };
    void push(const int value)
    {
        struct Elem *pointer;
        pointer= new struct Elem;
        pointer->c = value;
        pointer->next = Top;
        Top = pointer;
    };
public:
    Stack(){
        Top = nullptr;
    };
    ~Stack(){
        while(Top != nullptr){
            pop();
        }
    };
private:
    struct Elem
    {
        int c;
        struct Elem* next;
    };
    struct Elem *Top;


};



int main() {
        std::cout << "The end." << std::endl;
}

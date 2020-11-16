#include <iostream>
#include <clocale>

using namespace std;

class Stack {
private:  //Структура элемента массива.
    struct Array
    {
        Array *prevElement; //Указатель на пердыдущий элеммент массива.
        int value;
        Array() {}
        Array(const int  val)
        {
            value = val;
            prevElement = NULL;
        }
    };

    Array* topElement = new Array();
    int size;   //Обозначение размера массива 
public:
    int pop()
    {
        if (size != 0)
        {
            Array* temp = topElement;
            topElement = topElement->prevElement;
            delete temp;
            size--;
        }
        else 
        {
            size = -1;
            return size;
        };
    };
    void push(const int value) 
    {
        Array* newElement = new Array(value);  //Создание указателя на новый элемент.
        if (size == 0) 
        {
            topElement = newElement;
        }
        else 
        {
            newElement->prevElement = topElement;
            topElement = newElement;
        }
        size++;
    };
public:
    Stack()
    {
        size = 0; //Изначальный размер стека.
    };
    ~Stack() {};
};



int main() {
    cout << "The end." << endl;
}

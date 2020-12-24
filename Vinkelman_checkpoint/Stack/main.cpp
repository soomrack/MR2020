#include <iostream>
using namespace std;

class Stack{
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();

private:
    struct Znach{
        int v;
        Znach *p;
    };
    Znach *top;
};

// Создание стека
Stack::Stack() {
    top = nullptr;
}

// Добавление нового элемента в стек
void Stack::push(const int value) {
    Znach *pp = nullptr;    // Объявляется новый указатель
    pp = new Znach;         // Выделение памяти под новый указатель
    pp -> v = value;        // Переменной value присваивается значение переданной переменной
    pp -> p = top;          // Ссылаемся на предыдущий элемент (top)
    top = pp;               // Изменение ссылки на последний элемент
}

// Изъятие верхнего элемента из стека
int Stack::pop() {
    if (top == nullptr){    // Проверяем стек на наличие пустых значений
        return -1;
    }
    int value = top -> v;    // Сохранение значения верхнего элемента
    Znach *pp = top;         // Создание указателя на последний элемент
    top = top -> p;          // Меняем ссылку на последней элемент на ссылку на предпоследний
    delete pp;               // Высвобождение памяти
    pp = nullptr;            // Замена указателя на нуль-указатель
    return value;            // Возвращение значения верхнего элемента
}

// Высвобождение стека
Stack::~Stack() {
    while (top != nullptr){
        Znach *pp = top;    // Создание указателя на последний элемент
        top = top -> p;     // Меняем ссылку на последний элемент на ссылку на предпоследний
        delete pp;          // Высвобождение памяти
        pp = nullptr;       // Замена указателя на нуль-указатель
    }
}

int main() {
    cout << "The end." << endl;
    return 0;
}

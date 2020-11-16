#include <iostream>
/*
 * Комментарии написала для себя, чтобы лучше понимать,
 * как это работает
 */

class Stack {
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();

private:
    struct Element {
        int v;
        Element *p;
    };

    Element *top;
};

//Создание стэка
Stack::Stack(){
    top = nullptr;
}

//Добавление нового элемента
void Stack::push(const int value) {
    Element *pp = nullptr;     //Объявляем новый указатель
    pp = new Element;          //Выделяем память по него
    pp -> v = value;           //Значение = переданная переменная
    pp -> p = top;             //Ссылка на пред. эл-т = top
    top = pp;                  //Меняем ссылку на последний эл-т
}

//Изьятие верхнего элемента из стэка
int Stack::pop() {
    if (top == nullptr){      //Проверка стека на пустоту
        return -1;
    }
    int temporary = top -> v; //Сохраняем знач. верхнего эл-та
    Element *pp = top;        //Создаём указ. на посл. эл-т
    top = top -> p;           //Меняем: ссылка на посл. эл-т = ссылка на предпосл.
    delete pp;                //Высвобождаем память
    pp = nullptr;             //Заменяем указатель на нуль-указатель
    return temporary;         //Возвращ. знач. верхнего эл-та
}

//Высвобождение стэка
Stack::~Stack() {
    while (top != nullptr){
        Element *pp = top;        //Создаём указ. на посл. эл-т
        top = top -> p;           //Меняем: ссылка на посл. эл-т = ссылка на предпосл.
        delete pp;                //Высвобождаем память
        pp = nullptr;             //Заменяем указатель на нуль-указатель
    }
}

int main() {
    std::cout << "The end." << std::endl;
}

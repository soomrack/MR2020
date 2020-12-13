#include <iostream>

class Stack {
private:
    struct Node {
        int value;
        struct Node* next;
    };
    struct Node* top;
public:
    int pop();
    void push(const int value);
    Stack();
    ~Stack();
};
// Функция возвращает вершину из стека
int Stack::pop() {
    struct Node* temp;
    temp = new Node;
    if (top==nullptr) {
        return 2147483647;
    }
    int end = top->value;
    temp = top;
    top = top->next;
    temp->next = nullptr;//элемент, следующий за вершиной стал вершиной
    free(temp);
    return end;
}
// Функция вносит значение в стек
void Stack::push(const int value) {
    struct Node* temp;
    temp = new  struct Node;
    temp->value = value;
    temp->next = top;
    top = temp;
}
// Конструктор стека при инициализвции без аргументов
Stack::Stack() {
    top = nullptr;
}
// Деструктор стека - вызывается при завершении времени жизни объекта (например - закрылась скобка области видимости)
Stack::~Stack() {
    while (top != nullptr) {
        pop();
    }
}


int main() {
    std::cout << "The end." << std::endl;
}

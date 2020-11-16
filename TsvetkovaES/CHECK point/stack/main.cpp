#include <iostream>

class Stack {
private:
    int* elements; // стек элементов
    int size; // размер стека
    int top; // верх стека (свободная позиция). Он же - количество элементов в стеке
public:
    Stack(int my_size);
    ~Stack();
    int Pop();
    void Push(const int value);
    void Print();
};

Stack::Stack(int my_size) {
    size = my_size;
    elements = new int(size); // выделяем память
    top = 0;
}
Stack::~Stack() {
    delete [] elements;
}
void Stack::Push(const int value) {
    if(top==size) {
        printf("Stack is full!\n");
        return;
    }
    elements[top]=value;
    top++;
}
int Stack::Pop() {
    if(top==0) {
        printf("Stack is empty!\n");
        return 0;
    }
    top--;
    printf("%d (last) element - %d\n", top+1, elements[top]);
    return elements[top];
}
void Stack::Print() {
    for (int i=0; i<top;i++) {
        printf("%d element - %d\n", i+1, elements[i]);
    }
}

int main() {
    std::cout << "The end." << std::endl;
}
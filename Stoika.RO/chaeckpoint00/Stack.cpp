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
// ������� ���������� ������� �� �����
int Stack::pop() {
    struct Node* temp;
    temp = new Node;
    if (top==nullptr) {
        return 2147483647;
    }
    int end = top->value;
    temp = top;
    top = top->next;
    temp->next = nullptr;//�������, ��������� �� �������� ���� ��������
    free(temp);
    return end;
}
// ������� ������ �������� � ����
void Stack::push(const int value) {
    struct Node* temp;
    temp = new  struct Node;
    temp->value = value;
    temp->next = top;
    top = temp;
}
// ����������� ����� ��� ������������� ��� ����������
Stack::Stack() {
    top = nullptr;
}
// ���������� ����� - ���������� ��� ���������� ������� ����� ������� (�������� - ��������� ������ ������� ���������)
Stack::~Stack() {
    while (top != nullptr) {
        pop();
    }
}


int main() {
    std::cout << "The end." << std::endl;
}

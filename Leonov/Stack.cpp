#include <iostream>
#include <clocale>

using namespace std;

class Stack {
private:
    struct element {
        int value;
        struct element* next;
    };
    struct element *top;
public:
    int pop();
    void push(const int value);
public:
    Stack();
    ~Stack();
};

int Stack::pop()
{
    if (Top == nullptr) {
        return 787898;
    };
    struct element* pointer = top;
    int number = pointer->value;
    top = pointer->next;
    delete pointer;
    return number;
};

void Stack::push(const int value)
{
    struct element* pointer = new struct element;
    pointer->value = value;
    pointre->next = top;
    top = pointer;
};

Stack::Stack()
{
    top = nullptr;
};

Stack::~Stack()
{
    while (top != nullptr)
        pop();
};

int main() {
    cout << "The end." << endl;
}

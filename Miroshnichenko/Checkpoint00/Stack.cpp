#include <iostream>
int error = 232;

class Stack {
public:
  int pop();
  void push(const int value);
public:
  Stack();
  ~Stack();
private:
  struct Element;
  struct Element * top;
};

struct Stack::Element{
  int value;
  struct Element* next;
};
int Stack::pop() {
  if (top == nullptr) {
    return error;
  }
  struct Element * pointer;
  int topElement;
  pointer = top; 
  topElement = pointer->value; 
  top = pointer->next; //элемент, следующий за вершиной стал вершиной стека
  delete pointer;
  return topElement; //возвращаем вершину стека
}

void Stack::push(const int value) {
  struct Element * pointer;
  pointer = new struct Element;
  pointer->value = value;
  pointer->next = top;
  top = pointer;
}

Stack::Stack() {
  top = nullptr;
}

Stack::~Stack() {
  while (top != nullptr) {
    pop();
  }
}

int main() {
  std::cout << "The end." << std::endl;
}
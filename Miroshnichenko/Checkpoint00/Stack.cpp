#include <iostream>


class Stack {
public:
  int pop();
  void push(const int value);
public:
  Stack();
  ~Stack();
private:
  struct Element
  {
    int value;
    struct Element * next;
  };
  struct Element * top;
};

int Stack::pop() {
  if (top == nullptr) {
    return 1234;
  }
  struct Element * pointer;
  int a;
  pointer = top; 
  a = pointer->value; 
  top = pointer->next; //элемент, следующий за вершиной стал вершиной стека
  delete pointer;
  return a; //возвращаем вершину стека
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
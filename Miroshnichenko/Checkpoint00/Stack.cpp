#include <iostream>
int error = 232;

class Stack {
public:
  int pop();
  void push(const int value);
public:
  Stack();
  ~Stack();
};

struct Element {
  int value;
  struct Element *next;
};

struct Element *top;

int Stack::pop() {
  if (top == nullptr) return error;
  struct Element *pointer;
  int topElement;
  pointer = top; 
  topElement = pointer->value; 
  top = pointer->next; //элемент, следующий за вершиной стал вершиной стека
  delete pointer;
  return topElement; //возвращаем вершину стека
}

void Stack::push(const int value) {
  struct Element *pointer;
  pointer = new struct Element;
  pointer->value = value;
  pointer->next = top; //элемент, бывший вершиной стал следующим
  top = pointer;
}

Stack::Stack() {
  top = nullptr;
}

Stack::~Stack() {
  while (top != nullptr) pop();
}

int main() {
  std::cout << "The end." << std::endl;
}
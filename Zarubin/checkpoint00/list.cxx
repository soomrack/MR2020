#include <iostream>


class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node(const int value);
    Node(const int value, const Node *next);
    ~Node();
};


class List {
private:
    Node *root;
public:
    int pop();
    void push(const int value);
    void push(const int value, 
public:
    Stack();
    ~Stack();
};



int main() {
    std::cout << "The end." << std::endl;
}

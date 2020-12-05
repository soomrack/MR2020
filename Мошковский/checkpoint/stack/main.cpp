#include <iostream>
#define POP_ERROR -42;

struct Node {
    int content;
    Node* point;
};

class Stack {
private:
    Node* top;

public:
    int pop(){
        if (!top) {
            return -42;
        }
        int end = top->content;
        Node *targetNode = top;
        top = top->point;
        delete targetNode;
        return end;
    }
    void push(const int value){
        Node* temp;
        temp = new Node;
        temp->content = value;
        temp->point = top;
        top = temp;
    };
public:
    Stack();
     ~Stack(){
        while (top) {
            Node *half = top;
            top = top ->point;
            free (half);
        }
    };
};

Stack::Stack():top(NULL){}

int main() {
    Stack go_check;
    go_check.push(22);
    go_check.push(7);
    go_check.pop();
    int element = go_check.pop();

    std::cout << element <<"The end." << std::endl;

    go_check.~Stack();
}
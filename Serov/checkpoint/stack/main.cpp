#include <iostream>

class Stack {
private:
    struct Node {
        int value;
        struct Node* link;
    };
    struct Node* top;
public:
    int pop(){
        struct Node* temp;
        temp = new Node;
        if (!top) {
            printf("Please push some elements in stack");
            exit(1);
        }
        int end = top->value;
        temp = top;
        top = top->link;
        temp->link = NULL;
        free (temp);
        return end;
    }
    void push(const int value){
        struct Node* temp;
        temp = new Node();
        temp->value = value;
        temp->link = top;
        top = temp;
    };
public:
    Stack(){
        top = NULL;
    };
    ~Stack(){
        while (top) {
            Node *half = top;
            top = top ->link;
            free (half);
        }
    };
};



int main() {
    Stack letscheck;
    letscheck.push(228);
    letscheck.push(1488);
    letscheck.push(666);
    letscheck.pop();
    int element = letscheck.pop();
    printf("%d\n",element);
    std::cout <<"The end." << std::endl;
}

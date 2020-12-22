#include <iostream>

class stack {
private:
    struct nod {
        int value;
        struct nod* link;
    };
    struct nod* top;
public:
    int pop();
    void push(const int value);
public:
    stack();
    ~stack();
};

int stack ::pop() {
    struct nod* temp;
    temp = new nod;
    if (!top) {
        return 12;
    }

    int end = top->value;
    temp = top;
    top = top->link;
    temp->link = nullptr;
    free (temp);
    return end;
}

void stack  ::push(const int value) {
    struct nod* temp;
    temp = new nod();
    temp->value = value;
    temp->link = top;
    top = temp;
}

stack ::stack() {
    top = nullptr;
}

stack ::~stack() {
    {
        while (top) {
            nod *half = top;
            top = top ->link;
            free (half);
        }
    }
}


int main() {
    stack check;
    check.push(1);
    check.push(14);
    check.pop();
    int element = check.pop();
    printf("%d\n",element);
    std::cout <<"Test finished" << std::endl;
}
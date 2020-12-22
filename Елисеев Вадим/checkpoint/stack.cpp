#include <iostream>
const int MAXstack = 100;

struct Stack{
    int elem[MAXstack];
    int top;
};

static void init(struct Stack* stk) {
    stk->top = 0;
}

static void push(struct Stack* stk, int f) {
    stk->elem[stk->top] = f;
    stk->top++;

}

static int pop(struct Stack* stk) {
    int elem;
    if ((stk->top) > 0)
    {
        stk->top--;
        elem = stk->elem[stk->top];
        return elem;
    }
    else
    {
        return 0;
    }
}

static int get(struct Stack* stk) {
    if ((stk->top) > 0) {
        return stk->elem[stk->top - 1];
    }
    else {

        return 0;
    }
}

int main() {
    struct Stack numbers;
    init(&numbers);
    long int information;
    std::string answer;
    int i;
    std::cout << "Add?" << std::endl;
    std::cin >> answer;
    for (i = 0; answer == "yes"; i++) {
        std::cout << "Enter the data  ";
        std::cin >> information;
        push(&numbers, information);
        std::cout << "Add?" << std::endl;
        std::cin >> answer;
    }
    while (i > 0) {
        std::cout << "Data:  " << get(&numbers)  << std::endl;
        pop(&numbers);
        i--;
    }
    std::cout << "Stack cleaned" << std::endl;
    return 0;
}

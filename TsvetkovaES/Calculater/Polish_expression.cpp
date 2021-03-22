#include "Polish_expression.h"
Polish_expression::Polish_expression(int size) {
    this->size = size;
    //output_string = new std::vector<char>; // выделяем память под строку
    //stack_operators = new char(size); // выделяем память под операторы
    top_out_string = 0;
    top_operator = 0;
}
Polish_expression::~Polish_expression() {
    this->size = 0;
}

int Polish_expression::priority(char symbol) {
    int priority;
    switch(symbol) {
        case '+':
        case '-':
            priority = 1;
            break;
        case '*':
        case '/':
        case '^':
            priority = 2;
            break;
        case '_':
            priority = 3;
        default:
            priority = 0; // скобка
    }
    return priority;
}
bool Polish_expression::Push_to_output(char symbol) {
    output_string.push_back(symbol);
    top_out_string++;
    return true;
}
bool Polish_expression::Push_operator(char operatorr) {
    char symbol;
    if(operatorr == '(') {
        stack_operators.push_back(operatorr);
        top_operator++;
        return true;
    } else if(!(this->stack_is_empty()) && this->priority(Head_of_stack()) >= priority(operatorr)) {
        symbol = this->Pop_operator();
        this->Push_to_output(symbol);
        stack_operators.push_back(operatorr);
        top_operator++;
        return true;
    } else {
        stack_operators.push_back(operatorr);
        top_operator++;
        return true;
    }
}
char Polish_expression::Pop_operator() {
    if(top_operator == 0) {
        std::cout << "Stack of operators is empty!\n";
        return '\0';
    }
    top_operator--;
    char operatorr = stack_operators[top_operator];
    stack_operators.pop_back();
    return operatorr;
}
char Polish_expression::Head_of_stack() {
    if(top_operator == 0) {
        std::cout << "Stack of operators is empty!\n";
        return '\0';
    }
    return stack_operators[top_operator-1];
}

bool Polish_expression::stack_is_empty() {
    if(top_operator == 0) {
        return true;
    } return false;
}
void Polish_expression::Print() {
    for (int i = 0; i < top_out_string; i++) {
        //std::cout << i+1 << " element - " << output_string[i] << std::endl;
        std::cout<< output_string[i] << " ";
    }
}

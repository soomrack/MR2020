
#ifndef POLISH_NOTATION_POLISH_EXPRESSION_H
#define POLISH_NOTATION_POLISH_EXPRESSION_H
#include <iostream>
#include <vector>
#include <string>

class Polish_expression {
private:
    std::vector<char> output_string; // выходная строка
    std::vector<char> stack_operators; // операторы из входной строки
    int size; // размер стека
    // верх стека (свободная позиция). Он же - количество элементов в выходной строке и стеке символов
    int top_out_string;
    int top_operator;
public:
    Polish_expression(int my_size);
    ~Polish_expression();
    char Pop_operator();
    char Head_of_stack();
    bool Push_to_output(char symbol);
    bool Push_operator(char operatorr);
    bool stack_is_empty();
    void Print();
    int priority(char symbol);
};

#endif //POLISH_NOTATION_POLISH_EXPRESSION_H

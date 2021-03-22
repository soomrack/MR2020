#include "Polish_expression.h"
#include <string>
using namespace std;

bool is_number(char symbol) {
    if(symbol >= '0' && symbol <= '9') {
        return true;
    } else return false;
}
bool is_unary_minus(char current_symbol, char prev_symbol) {
    if(current_symbol == '-') {
        if(prev_symbol != '\0') {
            if(prev_symbol == '('||prev_symbol == '*'||prev_symbol == '/'||prev_symbol == '^') {
                return true; // символ '-', перед ним (,*,/ или ^
            } else return false; // символ '-', перед ним не (,*,/,^
        } else return true; // символ '-', первый в строке
    } else return false; // символ НЕ '-'
}
bool is_operator(char current_symbol) {
    if(current_symbol=='*'||current_symbol=='/'||current_symbol=='+'||current_symbol=='-'||current_symbol=='^') {
        return true;
    } else return false;
}
bool is_factorial(char current_symbol, char prev_symbol) {
    if(current_symbol == '!') {
        if((prev_symbol >= '0' && prev_symbol <= '9') || prev_symbol == ')') {
            return true; // факториал стоит после числа либо после выражения в скобках
        } else return false;
    } else return false;
}
bool is_open_bracket(char current_symbol) {
    if(current_symbol == '(') {
        return true;
    } else return false;
}
bool is_close_bracket(char current_symbol) {
    if(current_symbol == ')') {
        return true;
    } else return false;
}

int main() {
    string input_string = {0};
    getline(cin,input_string);
    int number_input_symbols = input_string.length();
    
    Polish_expression output_string(number_input_symbols);
    
    for(int symbol_position = 0; symbol_position < number_input_symbols; symbol_position++) {
        char current_symbol = input_string[symbol_position];
        char prev_symbol = '\0';
        if(symbol_position) {
            prev_symbol = input_string[symbol_position - 1];
        }
        if(is_number(current_symbol)) {
            output_string.Push_to_output(current_symbol); // надо как-то сделать проверку на дву- и более значные числа, мб в push_number
            continue;
        }
        if(is_unary_minus(current_symbol, prev_symbol)) {
            output_string.Push_operator('_'); // unary minus '_'
            continue;
        }
        if(is_operator(current_symbol)) {
            output_string.Push_operator(current_symbol);
            continue;
        }
        if(is_factorial(current_symbol,prev_symbol)) {
            output_string.Push_to_output(current_symbol);
            continue;
        }
        if(is_open_bracket(current_symbol)) {
            output_string.Push_operator(current_symbol);
            continue;
        }
        if(is_close_bracket(current_symbol)) {
            char symbol = output_string.Pop_operator();
            while(!is_open_bracket(symbol)) {
                output_string.Push_to_output(symbol);
                if(output_string.stack_is_empty()) {
                    std::cout << "Bad bracket";
                    return 1;
                }
                symbol = output_string.Pop_operator();
            }
            continue;
        }
    }
    
    char symbol;
    while(!output_string.stack_is_empty()) {
        symbol = output_string.Pop_operator();
        if(is_open_bracket(symbol)) {
            std::cout << "Bad bracket";
           return 1;
        }
        output_string.Push_to_output(symbol);
    }
    output_string.Print();
    return 0;
}

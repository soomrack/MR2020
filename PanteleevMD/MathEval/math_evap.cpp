#include <string>
#include <iostream>
#include <stack>
#include <vector>

using string = typename std::string;

int get_priority (char token){
    int priority;
    if (token == '+')
        priority = 1;
    if (token == '-')
        priority = 1;
    if (token == '*')
        priority = 2;
    if (token == '/')
        priority = 2;
    if (token == '(')
        priority = 0;
    return priority;
}

bool is_digit (char token){
    if (token == '+')
        return false;
    if (token == '-')
        return false;
    if (token == '/')
        return false;
    if (token == '*')
        return false;
    if (token == '(')
        return false;
    if (token == ')')
        return false;
    return true;
}

bool is_binary_operator(char token){
    if (token == '+')
        return true;
    if (token == '-')
        return true;
    if (token == '/')
        return true;
    if (token == '*')
        return true;
    return false;
}

int evaluate_binary(int a, int b, char bin_operator){
    switch (bin_operator)
    {
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '/':
        return a/b;
        break;
    case '*':
        return a*b;
        break;
    default:
        break;
    }
}


std::vector<string> infix_to_postfix(string orig_exp)
{
    std::vector<string> postfix_exp;
    std::stack<char> operations;

    bool number_flag = false;
    char symbol;
    char prev_symbol;
    string number = "";

    for (char symbol : orig_exp)
    {
        string token(1,symbol); 
        if (is_digit(symbol)) {
                     // digit may (or may not) be multi-digit
            number_flag = true;
            //prev_symbol = symbol;
            number += symbol;
            continue;
        }
        else if (number_flag) {                 // multi-digit number has ended
            postfix_exp.push_back(number);
            number.clear();
            number_flag = false;
        }

        if (symbol == '(') {
            operations.push(symbol);
            continue;
        }
        if (symbol == ')') {
            while (!operations.empty() && operations.top() != '(') {
                postfix_exp.push_back( string(1, operations.top()) );
                operations.pop();
            }
            operations.pop();
            continue;
        }

        if (is_binary_operator(symbol))
            while (!operations.empty() && get_priority(operations.top()) >= get_priority(symbol)) {
                postfix_exp.push_back( string(1, operations.top()) );
                operations.pop();
            }
            operations.push(symbol);
    }
    if (number_flag)                 // pushing last number
        postfix_exp.push_back(number);
        //number.clear();

    while (!operations.empty()) {
        postfix_exp.push_back( string(1, operations.top()) );
        operations.pop();
    }

    return postfix_exp;
}

int evaluate_postfix(std::vector<string> postfix_expr) 
{
    int result;
    for (auto expr_iter = postfix_expr.begin() ; expr_iter != postfix_expr.end(); ++expr_iter)
    {
        string token = *expr_iter;
        if (is_binary_operator(token[0])) {
            expr_iter--;
            string operand_two = *(expr_iter);
            postfix_expr.erase(expr_iter);
            expr_iter--;
            string operand_one = *(expr_iter);
            postfix_expr.erase(expr_iter);
            
            result = evaluate_binary(std::stoi(operand_one), std::stoi(operand_two), token[0]);
            postfix_expr.insert(expr_iter, std::to_string(result));
            postfix_expr.erase(expr_iter+1);
        }
    }
    return result;
}

int eval_expr(string infix_expr)
{
    std::vector<string> postfix_expr;
    
    postfix_expr = infix_to_postfix(infix_expr);

    return evaluate_postfix(postfix_expr);
}



int main()
{
    std::cout << eval_expr("(2+12)*(1-13)");
}
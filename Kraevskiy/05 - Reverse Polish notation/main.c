#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define number_f_maximum_elements 100

struct stack {
    int elem[number_f_maximum_elements];
    int top;
};

static void initialisation(struct stack *stack)
{
    stack->top = 0;
}

static void push(struct stack *stack, long long int num)
{
    if(stack->top < number_f_maximum_elements)
    {
        stack->elem[stack->top] = num;
        stack->top++;
    }
}

static int pop(struct stack *stack)
{
    long long int elem;
    if((stack->top) > 0)
    {
        stack->top--;
        elem = stack->elem[stack->top];
        return elem;
    }
    else
    {
        return 0;
    }
}

static float stackTop(struct stack *stack) {
    if((stack->top) > 0) {
        return stack->elem[stack->top-1];
    } else {
        return 0;
    }
}

static int stackTopInt(struct stack *stack) {
    if((stack->top) > 0) {
        return stack->elem[stack->top-1];
    } else {
        return 0;
    }
}

static bool number_check(char symbol)
{
    if  (symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3'
         || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7'
         || symbol == '8' || symbol == '9')
    {
        return true;
    } else
        return false;
}

static bool symbol_check(char symbol)
{
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
    {
        return true;
    } else
        return false;
}

static void clear_buf(char buf[12])
{
    for (int i=0; i<=11; i++)
    {
        buf[i] = ' ';
    }
}

int eval( const char *formula )
{
    struct stack *operand;
    struct stack *operation;
    operand = (struct stack*)malloc(sizeof(struct stack));
    operation = (struct stack*)malloc(sizeof(struct stack));
    initialisation(operand);
    initialisation(operation);
    int result = 0;
    int counter = 0;
    int number_1;
    int number_2;
    int stack_number;
    char buf[12];
    clear_buf(buf);
    char sigh;
    char formula2[200] = " ";
    for (int i = 0; i <= strlen(formula); i++)
    {
        formula2[i] = formula[i];
    }
    int length = strlen(formula2);
    formula2[length] = ')';
    for (int i=0; i <= strlen(formula2)-2; i++)
    {
        if (formula2[i] == '(' && formula2[i+1] == '-' && number_check(formula2[i+2]))
        {
            i = i + 2; // skip '(' and '-'
            counter = 0; // counter to write to buf
            while (number_check(formula2[i]))
            {
                buf[counter] = formula2[i];
                counter++;
                i++;
            }
            i++;
            stack_number = atoi(buf);
            stack_number = - stack_number;
            push(operand,stack_number);
            clear_buf(buf);
        }
        if (number_check(formula2[i]))
        {
            counter = 0;
            while (number_check(formula2[i]))
            {
                buf[counter] = formula2[i];
                i++;
                counter++;
            }
            stack_number = atoi(buf);
            push(operand,stack_number);
            clear_buf(buf);
        }
        if (symbol_check(formula2[i]))
        {
            push(operation,formula2[i]);
        }
        if (formula2[i] == '(')
        {
            continue;
        }
        if (formula2[i] == ' ')
        {
            continue;
        }
        if (formula2[i] == ')')
        {
            if (stackTop(operation) == 0 && i==(strlen(formula2)-2))
            {
                result = pop(operand);
            }
            if (stackTop(operation) == 0)
                continue;
            number_1 = pop(operand);
            number_2 = pop(operand);
            sigh = pop(operation);
            switch (sigh)
            {
                case '+':
                    result = number_2 + number_1;
                    push(operand, result);
                    break;
                case '-':
                    result = number_2 - number_1;
                    push(operand, result);
                    break;
                case '/':
                    result = number_2 / number_1;
                    push(operand, result);
                    break;
                case '*':
                    result = number_2 * number_1;
                    push(operand, result);
                    break;
            }
        }
    }
    result = stackTopInt(operand);
    while (stackTop(operation) != 0)
    {
        number_1 = pop(operand);
        number_2 = pop(operand);
        sigh = pop(operation);
        switch (sigh)
        {
            case '+':
                result = number_2 + number_1;
                push(operand, result);
                break;
            case '-':
                result = number_2 - number_1;
                push(operand, result);
                break;
            case '/':
                result = number_2 / number_1;
                push(operand, result);
                break;
            case '*':
                result = number_2 * number_1;
                push(operand, result);
                break;
        }
    }
    free (operand);
    free (operation);
    return result;
}

int main()
{

}
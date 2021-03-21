#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#define STACK_MAX_SIZE 100

typedef struct {
    int data[STACK_MAX_SIZE];
    size_t size;
} Stack_t;

void push(Stack_t *stack, int value) {
    if (stack->size >= STACK_MAX_SIZE)
        exit(1);
    stack->data[stack->size] = value;
    stack->size++;
}

int pop(Stack_t *stack) {
    if (stack->size == 0)
        exit(-1);
    stack->size--;
    return stack->data[stack->size];
}

int peek(const Stack_t *stack) {
    return stack->data[stack->size - 1];
}

// Определение приоритета символа
int value (int simbol)
{
    switch (simbol)
    {
        case '-':
        case '+':
            return 2;
            break;
        case '*':
        case '/':
            return 3;
            break;
        case '(':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

int32_t eval( const char * str_inp )
{
    char str[100] = {0};
    strcpy(str, str_inp);

    // Удаление пробелов
    char *ptr = str;
    char *ptr_space;
        while (strchr(ptr, ' ')) // ptr_space = &str[позиция первого пробела]
        {
            ptr_space = strchr(ptr, ' ');
            memmove(ptr_space, ptr_space + 1, strlen(ptr)); // ptr_space + 1 = &str[позиция первого пробела + 1]
        }

    char str_rpn[100] = {0};
    strcpy(str_rpn, str);

    int call = 0;

    // Учёт унарного минуса
    for (int i = 0; i < strlen(str); ++i)
    {
        if ((str[i] == '-') && (str[i - 1] == '('))
        {
            str_rpn[i + call] = '0';
            int k = i + 1;
            while ( k - 1 < strlen(str))
            {
                str_rpn[k + call] = str[k - 1];
                k++;
            }
            call++;
        }
    }

    Stack_t stack;
    stack.size = 0;

    char str_end[100] = {0};
    char str_space[2] = " ";

    // Формирование строки ОПЗ
    for (int i = 0; i < strlen(str_rpn); i++)
    {
        // Если текущий элемент не цифра
        if (!isalnum(str_rpn[i]))
        {
            strcat(str_end, str_space); // 1+1 в ОПЗ 1 1+
            if (str_rpn[i] == ')')
            {
                while (peek(&stack) != '(')
                {
                    // Записали верхний знак в строку и выкинули его стека
                    char str_curr[2];
                    str_curr[0] = peek(&stack);
                    strcat(str_end, str_curr);
                    pop(&stack);
                }
                pop(&stack); // Выкинули '(' из стека
            }
            else if (str_rpn[i] == '(')
            {
                push(&stack, str_rpn[i]);
            }
            // Если текущций знак с большим приоритетом, чем предыдущий
            else if ((stack.size == 0) || (value(peek(&stack)) < value(str_rpn[i])))
            {
                push(&stack, str_rpn[i]);
            }
            // Если текущий знак с меньшим/равным приоритетом, чем предыдущий
            else
            {
                do
                {
                    // Записали верхний знак в строку и выкинули его стека
                    char str_curr[2];
                    str_curr[0] = peek(&stack);
                    strcat(str_end, str_curr);
                    pop(&stack);
                }
                while (!((stack.size == 0) || (value(peek(&stack)) < value(str_rpn[i]))));
                // Записали текущий знак в стек
                push(&stack, str_rpn[i]);
            }
        }
        // Если цифра
        else
        {
            // Записываем в стоку, без пробелов
            char str_curr[2];
            str_curr[0] = str_rpn[i];
            strcat(str_end, str_curr);
        }
    }
    // Остаток из стека
    while (stack.size > 0)
    {
        // Записали верхний знак и выкинули его
        char str_curr[2];
        str_curr[0] = peek(&stack);
        strcat(str_end, str_curr);
        pop(&stack);
    }
    printf("%s\n", str_end);

    // Вычисление результата
    int64_t stack2[100] = {0};
    int sp = 0;

    for (int i = 0; i < strlen(str_end); i++)
    {
        int64_t c;
        if (str_end[i] == ' ')
            continue;
        else if (str_end[i] == '+'){
            stack2[sp-2] = stack2[sp-2] + stack2[sp-1];
            sp--;}

        else if (str_end[i] == '-'){
            stack2[sp-2] = stack2[sp-2] - stack2[sp-1];
            sp--;}

        else if (str_end[i] == '*'){
            stack2[sp-2] = stack2[sp-1] * stack2[sp-2];
            sp--;}

        else if (str_end[i] == '/'){
            stack2[sp-2] = stack2[sp-2] / stack2[sp-1];
            sp--;}

        else
        {
            // Запись чисел в стек
            char str_num[100] = {0};
            while (isalnum(str_end[i]))
            {
                char str_curr[2];
                str_curr[0] = str_end[i];
                strcat(str_num, str_curr);
                i++;
            }
            i--;
            c = strtol(str_num, NULL, 10);
            stack2[sp] = c;
            sp++;
        }
    }
    return (int)stack2[sp-1];
}

int main(void)
{
    return 0;
}

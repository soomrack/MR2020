#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Структура стека
struct Stack{
    char c;
    struct Stack *next;
};
//Push
struct Stack *push(struct Stack *TOP,char a){
    struct Stack *pointer;
    if((pointer=malloc(sizeof(struct Stack)))==NULL)
    {
        puts("Not enough memory");exit(-1);
    }
    pointer->c=a;
    pointer->next=TOP;
    return pointer;
}
//Delete
char Delete(struct Stack **TOP){
    struct Stack *pointer;
    char a;
    pointer=*TOP;
    a=pointer->c;
    *TOP=pointer->next;
    return a;
}
void POPOP (struct Stack *O,struct Stack *OP){
    O = push(O,'a');
    OP = push(OP,"f");
}
int main() {
    char outpu;
    char output;
    struct Stack *OPERATORS = NULL;
    struct Stack *OPERANDS = NULL;
    OPERATORS = push(OPERATORS,'a');
    OPERANDS = push(OPERANDS,'a');
    POPOP(OPERANDS,OPERATORS);
    output=Delete(&OPERATORS);
    printf("\n%c",output);
    outpu=Delete(&OPERANDS);
    printf("\n%c",outpu);
    return 0;
}
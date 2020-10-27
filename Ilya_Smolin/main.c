#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char str [] = "1+2+3+4+5";
//Функция подсчета длины ввода
int LENGTH(str){
    int length = strlen (str);
    return length;
}
//Структура стека
struct Stack{
    char c;//Что лежит на вершине Стека
    struct Stack *next; //Это ссылка на следующий элемент стека
};
//Push
struct Stack *push(struct Stack *TOP,char a){
    struct Stack *pointer;
    pointer=malloc(sizeof(struct Stack));
    pointer->c=a; //Вершиной стека стал а
    pointer->next=TOP; //Новая вершина ссылается на тот элемент, который раньше был на вершине
    return pointer; //Возвращаем вершину стека
}
//Delete
char Delete(struct Stack **TOP){
    struct Stack *pointer;
    char a;
    pointer=*TOP; //указатель будет ссылаться на адрес вершины стека
    a=pointer->c; //а присвоим то, что было на вершине стека
    *TOP=pointer->next; //элемент, следующий за вершиной стал вершиной стека
    return a; //возвращаем вершину стека
}
//Priority
int Priority (char a){
    switch (a) {
        case '*':
        case '/':
            return 3;
        case '-':
        case '+':
            return 2;
        case '(':
            return 1;
    }
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
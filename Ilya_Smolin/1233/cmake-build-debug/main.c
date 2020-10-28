#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char str [] = "3*(2+2)";

int chartoint (char a){
    int l;
    switch (a) {
        case '0': l=0;
            break;
        case '1': l=1;
            break;
        case '2': l=2;
            break;
        case '3': l=3;
            break;
        case '4': l=4;
            break;
        case '5': l=5;
            break;
        case '6': l=6;
            break;
        case '7': l=7;
            break;
        case '8': l=8;
            break;
        case '9': l=9;
            break;
    }
    return l;
}
//Структура стека
struct Stack{
    char c;//Что лежит на вершине Стека
    struct Stack *next; //Это ссылка на следующий элемент стека
};
struct Stackk{
    int c;//Что лежит на вершине Стека
    struct Stackk *next; //Это ссылка на следующий элемент стека
};
//Push
void push(struct Stack **TOP,char a){
    struct Stack *pointer;
    pointer=malloc(sizeof(struct Stack));
    pointer->c=a;
    pointer->next=*TOP;
    *TOP = pointer;
}
void pushh(struct Stackk **TOP,int a){
    struct Stackk *pointer;
    pointer=malloc(sizeof(struct Stackk));
    pointer->c=a;
    pointer->next=*TOP;
    *TOP = pointer;
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
int Deletee(struct Stackk **TOP){
    struct Stackk *pointer;
    int a;
    pointer=*TOP; //указатель будет ссылаться на адрес вершины стека
    a=pointer->c; //а присвоим то, что было на вершине стека
    *TOP=pointer->next; //элемент, следующий за вершиной стал вершиной стека
    return a; //возвращаем вершину стека
}
//Priority
int Priority (char a){
    int l;
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
void POPOP (struct Stackk **OPERANDS,struct Stack **OPERATORS) {
    int B = (Deletee(OPERANDS));
    int A = (Deletee(OPERANDS));
    switch (Delete(OPERATORS)) {
        case '+':
            pushh(OPERANDS, A + B);
            break;
        case '-':
            pushh(OPERANDS, A - B);
            break;
        case '*':
            pushh(OPERANDS, A * B);
            break;
        case '/':
            pushh(OPERANDS, A / B);
            break;
    }
}
int main() {
    struct Stack *OPERATORS = NULL;
    struct Stackk *OPERANDS = NULL;
    for (int i=0;i < strlen(str);i++){
        if (str[i]=='0'||str[i]=='1'||str[i]=='3'||str[i]=='4'||str[i]=='5'||str[i]=='6'||str[i]=='7'||str[i]=='8'||str[i]=='9'||str[i]=='2'){
            int l = chartoint(str[i]);
            pushh(&OPERANDS, l);
        }
        else if (str[i]==')'){
            while ((OPERATORS->c)!='(')
                POPOP(&OPERANDS,&OPERATORS);
            Delete(&OPERATORS);
        }
        else if ((OPERATORS==NULL)||(Priority(str[i])>(Priority(OPERATORS->c))||str[i]=='('))
            push(&OPERATORS, str[i]);
        else  {
            while(OPERATORS!=NULL&&Priority(str[i])<=Priority(OPERATORS->c))
                POPOP(&OPERANDS,&OPERATORS);
            push(&OPERATORS, str[i]);
        }
    }
    while(OPERATORS!=NULL)
        POPOP(&OPERANDS,&OPERATORS);
    printf("\n%d",Deletee(&OPERANDS));
    return 0;
}

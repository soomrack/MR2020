#include <stdio.h>

int main() {
    char a[25];
    char b[25];
    char c[25];
    char d[25];
    int i, count;

    scanf("%s",a);//вопрос
    scanf("%s",b);//вопрос
    scanf("%s",c);//ответ
    scanf("%s",d);//ответ
int c1= 0;
    count = 0;
   int count1= 0;
    for (i = 0;i<20;i++){
    if (a[i]==c[i]){count = count+1;};

    if (b[i]==d[i]){count1 = count1+1;};}
    if (count == 20){c1 =c1+ 1;};
    if (count1 == 20){c1 =c1+ 1;};
    printf("\n  verno %d",c1);

    return 0;
}

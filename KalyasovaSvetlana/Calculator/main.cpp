
#include <stdio.h>
#include <string.h>
static long long int charToDigit(const char * vnos, int i1, int i2) //из строки считываются цифры и преобразуются в числа int
{
    long long int number = 0;
    int i;
    for(i = i1; i <= i2; i++)
    {
        if (vnos[i] == ' ') //пропуск пробела в скобках
            continue;
        int n = vnos[i] - '0';
        if (n < 0 || n > 9) return -1;
        number = 10 * number + n;
    }

    return number;
}

static int prec(int op) //считывание операций(еще тут можно постаить им приоритет)
{
    if ((op=='+') || (op=='-') || (op=='*') || (op=='/')) return 1;
    return 0;
}

static long long int calc(int op, long long int a, long long int b)//считаем два числа
{
    switch (op)
    {
        case '+':   return a + b;
        case '-':   return a - b;
        case '*':   return a * b;
        case '/':   return a / b;
    }
    return 0;
}

static long long int rekurzija(const char *vnos, int start, int konec)//реализация рекурсии
{
    int parentheses = 0; //счетчик скобок
    int mid = -1; //знак
    int i;

    if (start > konec) return 0;
    for(i = start; i <= konec; i++)
    {
        int c = vnos[i];
        if (c == '(')
        {
            parentheses++;
        }
        else if (c == ')')
        {
            parentheses--;
        }
        else if (c == ' '){
            continue;
        }
        else if (parentheses == 0)
        {
            int n = prec(c);
            if (n && (mid < 0 ))
            {
                mid = i;
            }
        }
    }
    if (mid >= 0)
    { //пропуск пробела
        int kk = mid;
        int ll = mid;
        if (vnos[kk-1] == ' ')
        {
            while (vnos[kk-1] == ' ')
            {
                kk--;
            }
        }
        if (vnos[ll+1] == ' ')
        {
            while (vnos[ll+1] == ' ')
            {
                ll++;
            }
        }
        long long int a = rekurzija(vnos, start, kk - 1);
        long long int b = rekurzija(vnos, ll + 1, konec);
        long long int res =  calc(vnos[mid], a, b);//подсчет результата
        return res;
    } else
    {
        int k =0;
        int l = 0;
        if (vnos[start] == '(' && vnos[konec] == ')'){
            k++;
            l--;
            if (vnos[start+k] == ' '){
                while (vnos[start+k] == ' '){
                    k++;
                }
            }
            if (vnos[konec+l] == ' '){
                while (vnos[konec+l] == ' '){
                    l--;
                }
            }
            return rekurzija(vnos,start + k, konec + l);//повтор рекурсии
        }

        long long int res = charToDigit(vnos,start, konec);
        return res;
    }
}

int eval( const char * formula )
{
    int konets = strlen(formula)-1;
    int nachalo = 0;
    if (formula[konets] == ' '){ // игнорирование пробелов перед скобками и после них
        while (formula[konets] == ' ')
            konets --;
    }
    if (formula[nachalo] == ' '){
        while (formula[nachalo] == ' ')
            nachalo ++;
    }
    int result = rekurzija(formula, nachalo, konets);
    return result;
}

int main(void)
{
    int a = eval("((-(3+5))*2)+4");
    printf("%d",a);
}

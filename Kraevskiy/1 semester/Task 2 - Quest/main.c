#include <stdio.h>
#include <string.h>

int a;
char str[31] = "";
int main() {
    printf("%s\n" , "Skol'ko bydet 2+2*2*5\nVarianti:\n1)40\n2)25\n3)22");
    scanf("%d", &a);
    if (a==3) {
        printf("%s\n" , "RIGHT");
    }
    else
    {
        printf("%s\n" , "NOT RIGNT");
        }
   printf("%s\n" , "Igraem dal'she?");
    scanf ("%s30" , str);
    if (!strcmp(str , "da")) {
    printf("%s\n" , "ny horosho");
    } else {
        printf("%s\n" , "ny kak hochesh");
    }


    return 0;
}

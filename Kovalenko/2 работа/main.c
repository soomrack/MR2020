#include <stdio.h>
#include <stdlib.h>
int main() {
    int a;
    printf("Poigraem?\n 1. DA\n 2. NET\n");
    scanf("%d", &a);
    {if  (a == 1)
        printf("Horosho, snachala prostoe.\n Visit grusha nelzya skushat, chto eto?\n 1. Sharik\n"
               "2. Yabloko\n 3. Lampa\n");
        else
        {printf("Kak hochesh...\n");
        exit(0);}
    }
    scanf("%d",&a);
    if (a == 3)
       printf("Molodec, igra okonchena.");
     else
        printf("Ti proigral, sogaleyu.");
    return 0;
}

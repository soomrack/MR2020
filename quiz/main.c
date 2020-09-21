#include <stdio.h>


int main() {
    int bober = 2;
    int acula = 1;
    int ans;
    int i = 0;
   printf("Dalee budut nescol'ko voprosov. Udachi!\n");
   printf("V kachestve orvetov pishite nomera vernih variantov.\n");
   printf("Skol'ko zubov u bobra?\n 1.17\n 2.20\n 3.22\n");
   scanf("%d", &ans);
   if (ans == bober) {
       i+=1;
   } else{
       i=i;
   }
   printf("Sko'ko nog u acali?\n 1.0\n 2.2\n 3.8\n");
   scanf("%d",&ans);
   if (ans == acula){
       i+=1;
   } else{
       i=i;
   }
   printf("Kolichestvo vernih otvetov - %d\n",i);
    return 0;
}

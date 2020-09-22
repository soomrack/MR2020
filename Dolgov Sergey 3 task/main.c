#include <stdio.h>
int dohod = 10000;
int srok  = 10*12;
int price = 9990000;
int dolgi = 9990000;
int price_grow = 5;
int perviy_vsnos = 10000;
int persent_po_ipoteke = 3;
int persent_po_depositu =10;
int changing_percent_po_ipoteke = 1;// v desyatih procenta
int initial_capital = 2000000;

int ipoteka_iteratsia(int dolg,int persent,int vsnos){
    dolg = dolg*persent/1200 - vsnos+dolg;
    return dolg;
}

int deposit_iteratsia(int sum , int vsnos , int persent){
    sum =sum +vsnos + sum*persent/1200;
    return sum;
}

int main() {// 2 varianta ipoteka+ dep i dep
     //deposit
     int i;
    int summa_deneg = initial_capital;
     for (i = 0;i<srok;i++){
        summa_deneg   = deposit_iteratsia(summa_deneg,dohod,persent_po_depositu);
printf("%d\n oio",summa_deneg);
price = price+price*price_grow/12000;
     };
     printf("\n________DEPOSIT___________");
     printf(" \nnakoplennaya summa budet =  %d ", summa_deneg);
     printf(" \nprice of flat =   %d", price);
       if (summa_deneg<=price){int dif  = price - summa_deneg;
       printf("\nin this case will not be enough  money to buy sum = %d  ",dif);}else{
       int dif  =summa_deneg -price ; printf("\n after getting flat , there will be free %d",dif);
       printf("\n________________________________");
    }
//konets rascheta deposita
//ipoteka
printf("\n______________IPOTEKA +DEPOSIT____________");
     summa_deneg = initial_capital - perviy_vsnos;
    for (i = 0;i<srok;i++){
        dolgi = ipoteka_iteratsia(dolgi,persent_po_ipoteke,dohod);
        printf("%d\n",dolgi);
        summa_deneg = deposit_iteratsia(summa_deneg,0,persent_po_depositu);
        persent_po_ipoteke = persent_po_ipoteke*changing_percent_po_ipoteke/1200+persent_po_ipoteke    ;

    };
       dolgi = dolgi - summa_deneg;
       printf("\nfinal debt will be %d",dolgi);
       printf("\n_______________________________");
//onetc ipoteki

    return 0;
}

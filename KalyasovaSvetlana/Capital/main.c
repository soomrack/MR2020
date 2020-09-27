#include <stdio.h>

int vklad(int a,int b, float c, int d){//расчет итоговых денег при вкладе
for (int i=1; i<=b; i++)
{
a =(a*c)+d;
}
return a;
}
int rostkv(int a, int b, float c){
    for (int i=1; i<=b; i++){
        if (i % 12==0)
            a=a*c;
    }
    return a;
}
int main() {
    int kapital = 0;
    int dohod = 0;
    float stavka = 0;
    float ipoteka = 0;
    float increasekv = 0;
    int period = 0;
    int tsenakv = 0;
    int profitkv = 0;
    printf("\nEnter initial data\n");
    printf("Initial capital (rub)-> ");
    scanf("%d", &kapital);
    printf("\nYour income (rub)-> ");
    scanf("%d", &dohod);
    printf("\nInterest rate on the deposit (perc|year)->");
    scanf("%f", &stavka);
    printf("\nPercentage of mortgage annual (perc|year)->");
    scanf("%f", &ipoteka);
    printf("\nRise in apartment value (perc|year)->");
    scanf("%d", &increasekv);
    printf("\nTime interval (years)->");
    scanf("%d", &period);
    printf("\nCost of the desired apartment (rub)->");
    scanf("%d", &tsenakv);
    printf("\nProfit of the apartment (rub|month)->");
    scanf("%d", &profitkv);
    float stavkamonth = 1 + (stavka / 1200); // месячный процент в долях
    int periodmonth = period * 12;// количество месяцев вклада
    float risekv=1+(increasekv/100);
    float ipotek=1+(ipoteka/100);
// 1) Расчет без покупки квартиры
    int kapitalvkl = vklad(kapital, periodmonth, stavkamonth, dohod);
    printf("\nCapital only for deposit = ");
    printf("%d",kapitalvkl);
    // сразу покупка кв
    if (kapital >= tsenakv)
    {
        int kapitalwithkv=kapital-tsenakv;
        kapitalwithkv = vklad(kapitalwithkv, periodmonth, stavkamonth, dohod+profitkv);
        kapitalwithkv=kapitalwithkv+rostkv(tsenakv, periodmonth, risekv);
        printf("\nCapital with the purchase of an apartment immediately = ");
        printf("%d",kapitalwithkv);
        if (kapitalvkl>kapitalwithkv) {
            printf("\nCapital without buying an apartment more investment with buying an apartment in %d",((kapitalvkl * 100 / kapitalwithkv) - 100));
            printf(" (perc)\n");
        }
            else  printf("\nCapital with the initial purchase of an apartment is more profitable than a contribution without buying an apartment in %d",((kapitalwithkv*100/kapitalvkl)-100));
        printf(" (perc)\n");
    }
    if (kapital < tsenakv)//сначала вклад для накопления денег на квартиру
    {
        int k = 0;
        int kapitalvklad = kapital;
        for (int i = 1; kapitalvklad < tsenakv && i <= periodmonth; i++) {
            kapitalvklad = kapitalvklad * stavkamonth + dohod;
            k++;
        }
        if (kapitalvklad < tsenakv)
            printf("\nBuying an apartment after deposit is impossible");
        else {
            kapitalvklad = kapitalvklad - tsenakv;
            kapitalvklad = vklad(kapitalvklad, periodmonth - k, stavkamonth, dohod + profitkv);
            kapitalvklad = kapitalvklad + rostkv(tsenakv, periodmonth - k, risekv);
            printf("\nCapital with the purchase of an apartment after deposit = ");
            printf("%d", kapitalvklad);
            if (kapitalvkl > kapitalvklad)
            {
                printf("\nCapital without buying  an apartment is more profitable than capital with an investment before buying an apartment in %d", ((kapitalvkl * 100 / kapitalvklad) - 100));
            printf(" (perc)");
            }
            else printf("\nCapital with an investment before buying an apartment is more profitable than capital without buying  an apartment in %d", ((kapitalvklad * 100 / kapitalvkl) - 100));
            printf(" (perc)");
        }
    }
    if (kapital<tsenakv)//сразу ипотека
    {
    int sumipoteka=tsenakv-kapital;
    sumipoteka=sumipoteka*ipotek;
    int n=0;
        for (int i=1;sumipoteka>0 && i<=periodmonth; i++){
            if (i%12==0)
            {
                sumipoteka=sumipoteka*ipotek;
            }
            sumipoteka=sumipoteka-dohod-profitkv;
            n++;
        }
        if (sumipoteka>0)
            printf("\nYou don't have enough income to pay the mortgage in time ");
        if (sumipoteka<=0)
        {
        int kkkapital=-sumipoteka;
        kkkapital=vklad(kkkapital, periodmonth-n, stavkamonth, dohod+profitkv);
        kkkapital=kkkapital+rostkv(tsenakv, periodmonth, risekv);
        printf("\nCapital after repayment of the mortgage and opening of a deposit = ");
        printf("%d",kkkapital);
            if (kapitalvkl>kkkapital)
            {
                printf("\nCapital without buying  an apartment is more profitable than capital with an initial mortgage and subsequent investment in %d",((kapitalvkl*100/kkkapital)-100));
            printf(" (perc)");
            }
            else  printf("\nCapital with an initial mortgage and subsequent investment is more profitable than capital without buying  an apartment in %d",((kkkapital*100/kapitalvkl)-100));
            printf(" (perc)");
        }
        }
}
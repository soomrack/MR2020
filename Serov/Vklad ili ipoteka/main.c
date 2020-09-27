#include <stdio.h>
int rostkv(int a, int b, float c){
int i=0;
while (i<b){
    if (i % 12==0)
    a=a+(a*c/100);
i++;
}
return a;
}
int vklad(int a,int b, float c, int d){//расчет итоговых денег при вкладе
    int i=0;
    while (i<b) {
        a = a + (a * c) + d;
        i++;
    }
    return a;
}
int main() {
    int doxod = 0;
    int cap = 0;
    float godvklad = 0.0;
    float rost = 0.0;
    int dopdox = 0;
    int godtime = 0;
    int kvartira = 0;
    float godip = 0;
    printf("Vvedite svoy doxod, rub/mes\n");
    scanf("%d", &doxod);
    printf("Vvedite svoy pervona4alniy kapital, rub\n");
    scanf("%d", &cap);
    printf("Vvedite protsent vklada, prots v god\n");
    scanf("%f", &godvklad);
    printf("Vvedite sredniy rost stoimosti kvartiry, prots v god\n");
    scanf("%f", &rost);
    printf("Dop doxod ot sda4i kvartiry, rub\n");
    scanf("%d", &dopdox);
    printf("Vvedite vremya ipoteki ili vklada, let\n");
    scanf("%d", &godtime);
    printf("Vvedite stoimost kvartiry, rub\n");
    scanf("%d", &kvartira);
    printf("Vvedite protsent ipoteki, prots v god\n");
    scanf("%d", &godip);
    float mesvklad = godvklad / 1200; // месячный процент в долях
    int mestime = godtime * 12; // количество месяцев вклада
    int summdox = doxod + dopdox;
 // 1) Расчет без покупки квартиры
   int cap1=vklad(cap, mestime, mesvklad, doxod);
    int cap2 = cap;// 2) Вклад до покупки квартиры
    int i = 0;
    int kvartira1=kvartira;
    while ((cap2 < kvartira1) && (i < mestime)) {
        if (i % 12 == 0)
            kvartira1=kvartira1+(kvartira1*rost/100);
        cap2 = cap2 + (cap2 * mesvklad) + doxod;
        i++;
    }
    if (cap2<kvartira1)
        cap2=0;
    if (cap2 >= kvartira1) {
        cap2 = cap2 - kvartira1;
        int mestime2 = mestime - i;
        cap2=vklad(cap2, mestime2, mesvklad, summdox);
        int kvartira2 = rostkv(kvartira1, mestime2, rost);
        cap2 = cap2 + kvartira2;
    }
int cap3=cap;// 3) Ипотека с наибыстрейшей оплатой, затем вклад
    i=0;
    int summip=kvartira-cap3;
   while ((summip>0) && (i<mestime)) {
       if (i % 12 == 0)
           summip = summip + (summip * godip / 100);
       summip = summip - summdox;
       i++;
   }
  cap3=0;
int mestime3 = mestime - i;
if (summip<=0){
   cap3=-summip;
   cap3 = vklad(cap3,mestime3,mesvklad,summdox);
   int kvartira3 = rostkv(kvartira, mestime, rost);
   cap3=cap3+kvartira3;
}
    if (cap>=kvartira)
        cap3=0;
   int dox1=cap1-cap-doxod*mestime;
    int dox2=cap2-cap-doxod*mestime;
    int dox3=cap3-cap-doxod*mestime;
    float dx1=dox1;
    float dx2=dox2;
    float dx3=dox3;
printf("Doxod tolko pri vklade =  ");
printf("%d",dox1);
if (cap2==0)
    printf("\nPokupka kvartiry bez ipoteki nevozmojna");
if (cap2!=0){
    printf("\nDoxod so vkladom i pokupkoy kvartiry bez ipoteki =  ");
    printf("%d",dox2);
}
    if (cap3==0)
        printf("\nPokupka kvartiry v ipoteku za zadanniy period nevozmojna ili ne imeet smisla");
    if (cap3!=0) {
        printf("\nDoxod s ipotekoy i posleduyushim vkladom = ");
        printf("%d", dox3);
    }
    if ((dox1>dox2) && (dox1>dox3)){
        if (cap2!=0){
        printf("\nVklad v bank bez pokupki kvartiry vigodnee pokupki kvartiry so vkladom na ");
        printf("%f",(((dx1/dx2)-1)*100));
        printf(" protsentov");
        }
        if (cap3!=0){
            printf("\nVklad v bank bez pokupki kvartiry vigodnee ipoteki na ");
            printf("%f",(((dx1/dx3)-1)*100));
            printf(" protsentov");
        }
    }
    if ((dox2>dox1) && (dox2>dox3)) {
        printf("\nVklad v bank s pokupkoy kvartiry vigodnee prosto vklada na ");
        printf("%f", (((dx2/dx1) - 1) * 100));
        printf(" protsentov");
        if (cap3 != 0) {
            printf("\nVklad v bank s pokupkoy kvartiry vigodnee ipoteky na ");
            printf("%f", (((dx2 / dx3) - 1) * 100));
            printf(" protsentov");
        }
    }
        if ((dox3 > dox1) && (dox3 > dox2)) {
            printf("\nIpoteka vigodnee prosto vklada na ");
            printf("%f", (((dx3 / dx1) - 1) * 100));
            printf(" protsentov");
            if (cap2 != 0) {
                printf("\nIpoteka vigodnne vklada v bank s pokupkoy kvartiry na ");
                printf("%f", (((dx3 / dx2) - 1) * 100));
                printf(" protsentov");
            }
        }

}
#include <stdio.h>
#include <math.h>

int startCap = 500000;
int stavkaDep = 5;
int stavkaIpot = 6;
int period = 5;
int rostKv = 4;
int cenaKV = 5000000;
int finCapDep (int platezh);
int finCapKV ();
int monthlyPay ();

int main() {
    printf("\n");
    int monthlyPay1 = monthlyPay ();
    int dp = finCapDep (monthlyPay1);
    int kv = finCapKV();
    int raznica = dp - kv;
    if (dp > kv) {
        printf("Deposit is more profitable on: %d\n", raznica);
    } else {
        raznica = - raznica;
        printf("Ipoteka is more profitable on: %d\n", raznica);
    }
    return 0;
}
int monthlyPay (){
    float mounthRate = (float)stavkaIpot/12/100;
    //printf("%.3f\n",mounthRate);
    float obshRate = powf (1 + mounthRate, (float)period * 12);
    //printf("%.3f\n", obshRate);
    float res1 = (float)cenaKV*mounthRate*obshRate/(obshRate-1);
    int res = (int)res1;
    printf("Monthly pay is: %d\n", res);
    return res;
}
int finCapKV (){
    int res = cenaKV;
    for (int i = 1; i <= period; i++) {
        res = res + res*rostKv/100;
    }
    printf("Apartment final price: %d\n", res);
    return res;
}
int finCapDep (int platezh) {
    int srok = period*12;
    int res = startCap;
    for (int i = 1; i<=srok; i++) {
        res = res + res*stavkaDep/(12*100) + platezh;
    }
    printf("Deposit final price: %d\n", res);
    return res;
}

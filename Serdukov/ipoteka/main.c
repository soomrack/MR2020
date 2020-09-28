#include <stdio.h>
#include <math.h>

int sal,srok,perv,nachk, stkv, perep,obshst, ostsrm,stkvip, srokd, dpd, schet, i;
double prip,mprip,obshstav, mplip,prrkv, mind, mprd,prd;
int main() {
    printf("Your dohod.\n");
    scanf("%d",&sal);
    printf("Stoimost kv.\n");
    scanf("%d",&stkv);
    printf("Pervonach vznos po ipot.\n");
    scanf("%d",&perv);
    printf("Proc po ipot.\n");
    scanf("%lf",&prip);
    printf("Proc rost kv.\n");
    scanf("%lf",&prrkv);
    printf("Nach kap dep.\n");
    scanf("%d",&nachk);
    printf("Procent po dep godovih.\n");
    scanf("%lf",&prd);
    printf("Srok po ipot let.\n");
    scanf("%d",&srok);
    printf("Srok dep v god.\n");
    scanf("%d",&srokd);
    mprip=(prip/12.0/100.0);
    obshstav =pow((1+mprip),(srok*12));
    mplip=(stkv-perv)*(mprip*obshstav/(obshstav-1.0));//В вывод
    perep= (int)(mplip)*srok*12-(stkv-perv);//В вывод
    obshst=perep+stkv; //В вывод
    ostsrm=sal- (int)mplip; //В вывод
    stkvip=(prrkv/100*srok+1)*stkv;// В вывод
    mprd=prd/100/12;
    schet=nachk;
    while (i<=srokd*12) {
        schet=schet+(int)mind;
        mind=schet*mprd;
        i++;
    }
    schet=schet+(int)mind;// В вывод
    dpd=schet-nachk;// В вывод
    printf("Ezhemes pl:%d\n",(int)mplip);
    printf("Pereplata:%d\n",perep);
    printf("Obshaya stoimost:%d\n",obshst);
    printf("Ostatok v mes:%d\n",ostsrm);
    printf("Stoimost kvart posle ip:%d\n",stkvip);
    printf("Schet po dep v konce:%d\n",schet);
    printf("Dohod po dep:%d\n",dpd);
    return 0;
}

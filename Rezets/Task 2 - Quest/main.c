#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    char ans[4];
    _Bool stt = 0;
    printf("DELA SEMEINIE\n\nChtobi Baron, vladika Velena, skazal gde Tsiri\nnyzhno pomoch otiscat' ego zheny.\n\n");
    printf("Bydesh pomogat'? (da/net)\n");
    while (stt == 0){
        scanf("%s", &ans);
        if (strcmp(ans, "Da") == 0 || strcmp(ans, "da") == 0){
            stt++;
        }
        else if (strcmp(ans, "Net") == 0 || strcmp(ans, "net") == 0){
            printf("\nTsiri bytet lezhat' nepoimi gde, pomirat', a tebe pomoch slozhno\n");
            exit(EXIT_SUCCESS);
        }
        else
            printf("Ne correctnii otvet\n");
    }
    stt--;
    printf("\nVi uznaete chto zhena Borona v pleny y bolotnih ved'm,\npomogaet sirotam prishedshim na topi.\nOna privodit vas k ved'mam,a oni govoriat chto skazhyt chto bilo s Tsiri esli vi ybiete derevo.\nV svou ochered' derevo rasscazivaet chto ved'mi ybivaut sirot, a ono mozhet pomoch im esli vi vipolnite ritual.\n\n");
    printf("1. Pomoch derevy.\n2. Ybit' derevo.\n");
    while (stt == 0){
        scanf("%s", &ans);
        if (strcmp(ans, "1") == 0 || strcmp(ans, "1.") == 0){
            printf("\nVi pomogaete derevy, v rezyl'tate obriada ono stanovitsa konem i spasaet sirot.\nVed'mi razozlilis' i proklali zheny Barona.\nVi rasskazivaete Barony pro to chto yznali i on govorit chto Tsiri yehala v Novigrad.\nA takzhe prosit pomoch emy rascoldovat'zheny.\nV rezhyl'tate obriada zhena ymeraet, posle etogo Baron igraet v chereshnu.\n");
            stt++;
        }
        else if (strcmp(ans, "2") == 0 || strcmp(ans, "2.") == 0){
            printf("Vi ybivaete derevo i ved'mi govoriat chto hoteli siest' Tsiri no ona ybezhala.\nZatem oni ischezzaut. Vi rasskazivaete Barony pro zheny i vmeste spasaete ee.\nPosle chego Baron govorit chto Tsiri yehala v Novigrad.\n");
            stt++;
        }
        else
            printf("Ne correctnii otvet\n");
    }
    printf("\nKonets kvesta.\n");
    return 0;
}
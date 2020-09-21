#include <stdio.h>
int main() {
    int right=0;
    int number=0;
    printf("It's a cooking quiz!\nThere are going to be 5 questions!\nGood Luck!\n");
    printf("1) Which is the most popular type of tee in Russia?\n");
    printf("1-White \n2-Milky oolong \n3-Black(red) \n4-Green\n");
    scanf("%d",&number);
    if (number==3){
        printf("Correct\n");
        right=right+1;
    }
    else
        printf("Incorrect\n");
     printf("2) Which fast food restaurant can you buy Big Tasty at?\n");
    printf("1-Subway \n2-McDonald's \n3-Burger King\n4-KFC\n");
    scanf("%d",&number);
    if (number==2){
        printf("Nice job, you are right!\n");
        right=right+1;
    }
    else
        printf("Incorrect\n");
    printf("3) Which product doesn't belong to 'Goryachaya Shtuchka' trdemark?\n");
    printf("1-Kruggetsy\n2-Chebupely \n3-Chebupizza \n4-Chebureshky\n");
    scanf("%d",&number);
    if (number==4){
        printf("Correct\n");
        right=right+1;
    }
    else
        printf("Incorrect\n");
    printf("4) What kind of meat Kruggetsi are made of?\n");
    printf("1-Chicken\n2-Pork \n3-Beef \n4-There is no meat\n");
    scanf("%d",&number);
    if (number==1){
        printf("Correct\n");
        right=right+1;
    }
    else
        printf("Incorrect\n");
     printf("5) Which nation meal 'nudly' traditionally belongs to?\n");
    printf("1-German\n2-Ukranian \n3-Turkish \n4-Jewish\n");
    scanf("%d",&number);
    if (number==2){
        printf("Correct\n");
        right=right+1;
    }
    else
        printf("Incorrect\n");
    printf("You earned ");
    printf("%d",right);
    printf(" points.");
}
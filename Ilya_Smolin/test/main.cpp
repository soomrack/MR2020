#include <stdio.h>
#include <string.h>
int result;
char ans[10];
int main() {
    printf("%s\n%s\n","Musical Test",
           "Na kaz'diy vopros budet 4 varianta otveta, vvodite nomer varianta otveta.");
    //Первый вопрос
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n","1 Question: Whole lotta red will drop out...",
           "1. 2020","2. 2021","3. 2020forsure","4. Pfff...never", "Enter the answer");
    tryagain:
    scanf("%s", &ans);
    if (strcmp(ans,"1")==0) {
        result += 0;
    }
    else if (strcmp(ans,"2")==0) {
        result += 0;
    }
    else if (strcmp(ans,"3")==0) {
        result += 0;
    }
    else if (strcmp(ans,"4")==0) {
        result += 1;
    }
    else {
        printf("%s\n", "Put in correct answer pls)...");
        goto tryagain;
    }
    //Второй Вопрос
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n","2 Question: There's new notification on ur phone. It is...",
           "1. A message from bae","2. A new Kanye's tweet","3. Vam nachisleno 1000 ballof perekrestka",
           "4. Spam", "Enter the answer");
    tryagain1:
    scanf("%s", &ans);
    if (strcmp(ans,"1")==0) {
        result += 0;
    }
    else if (strcmp(ans,"2")==0) {
        result += 1;
    }
    else if (strcmp(ans,"3")==0) {
        result += 0;
    }
    else if (strcmp(ans,"4")==0) {
        result += 0;
    }
    else {
        printf("%s\n", "Put in correct answer pls)...");
        goto tryagain1;
    }
    printf("%s\n%d%s", "Result",result,"/2");
    return 0;
}

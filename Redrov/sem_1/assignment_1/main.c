//
// Created by vladl on 19.09.2020.
//
#include "stdio.h"

int A = 0;

int test(){
    A = 0;
    int A = 2;
}

int main(void){
    int A = 1;

    printf("Hello world");
    test();
}

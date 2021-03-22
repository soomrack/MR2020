//
// Created by vladl on 19.09.2020.
//
#include "stdio.h"
#include "eval.h"

int main(void)
{
    printf("%d", eval("1+5\0"));
    return 0;
}


// add2num.c
#include <stdio.h>

int add2num(int loop){
    int number;
    int x;
    for(x = 0; x < loop; x++){
        int i;
        printf("Integer[%i]: ", x+1);
        scanf(" %i", &i);
        number += i;
    }
    return number;
}
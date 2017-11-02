// This is the herder.c file if the header project
#include <stdio.h>

int getInt(char msg[512]){
    int rv;
    printf("%s", msg);
    scanf(" %i", &rv);
    return rv;
}

char getChar(char msg[512]){
    char rv;
    printf("%s", msg);
    scanf(" %c", &rv);
    return rv;
}
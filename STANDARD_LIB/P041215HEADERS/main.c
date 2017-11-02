// This is the main.c file for the including headers project
#include <stdio.h>
#include <stdlib.h> 
#include "header.h"
#include "add2num.h"

int main(int argc, char *argv[]){
    
    int loop = strtoul(argv[1], NULL, 0);
    
    int sum = add2num(loop);
    
    printf("[SUM]%i\n", sum);
    
    return 0;
}
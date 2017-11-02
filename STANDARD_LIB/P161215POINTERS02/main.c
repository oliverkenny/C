// working with pointers 02

#include <stdio.h>

int multiply(int multiplier, int *value) {
    *value = *value * multiplier;
    return 0; 
}

int main(int argc, char *argv[]) {
    
    int multiplier, value;
    int *pvalue = NULL;
    multiplier = 3;
    value = 4;
    pvalue = &value;
    
    multiply(multiplier, pvalue);
    
    printf("The result of %i! Brill.\n", *pvalue);
    
    return 0;
}
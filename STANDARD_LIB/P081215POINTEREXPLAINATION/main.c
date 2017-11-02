#include <stdio.h>

// "&" means "address of"

int main(int argc, char *argv[]) {
    
    printf("INTRODUCTION TO POINTERS IN C!\n");
    
    int number = 0; // create an initial number variabe
    
    printf("number  = %i\n", number);
    printf("&number = %i\n", &number);
    
    int *pointer_to_number = &number;
    
    return 0;
}
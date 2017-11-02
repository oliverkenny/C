#include <stdio.h>

#define MINARGS 2

int main(int argc, char * argv[]) {
    if (argc != MINARGS) {
        printf("Expected arguments: %i  Actual arguments: %i\n", MINARGS, argc);
        printf("Executed incorrectly.\n");
    } else {
        printf("Arguments: ");
        int i;
        for(i = 1; i < MINARGS; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        printf("Executed correctly.\n");
    }
    
    return 0;
}
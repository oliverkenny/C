// Oliver Kenny 14/12/2015
// Menu System

#include <stdio.h>

int menuPrint(char *arr[], int length) {
    for(int x = 0; x < length; x++) {
        printf("%i. %s\n", x+1, arr[x+1]);
    }
    return 0;
}

char menuScan(char *arr[], int length) {
    printf("Value[1...%i]: ", length);
    int rv;
    scanf("%i", &rv);
    return arr[rv];
}

int main(int argc, char *argv[]) {
    /*
    int menuLength = argc-1;
    
    for(int x = 0; x < menuLength; x++) {
        printf("%i. %s\n", x+1, argv[x+1]);
    }
    
    printf("Value[1...%i]: ", menuLength);
    int choice;
    scanf("%i", &choice);
    
    if(choice < menuLength && choice > 1) {
        printf("You called function %s.\n", argv[choice]);
    } else {
        printf("Error[101]\n");
    }
    */
    
    menuPrint(argv, argc-1);
    char option[128];
    option = menuScan(argv, argc-1);
    printf("Returned: %s\n", option);
    
    return 0;
}
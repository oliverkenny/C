// Oliver Kenny
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int arrayLength = 20;

int getRand(int min, int max){
    int difference;
    int random;
    difference = max - min;
    random = rand() % difference + min;
    return random;
}

void fillArray(int arraySize, int *array){
    srand(time(NULL));
    int i;
    for(i = 0; i < arraySize; i++){
        array[i] = getRand(0, arraySize)*2;
    }
}

void printArray(int arraySize, int *array){
    int i;
    for(i = 0; i < arraySize; i++){
        printf("[%i,%i]  ", i+1, array[i]);
    }
}

int main() {
    
    int array[arrayLength], i;
    
    fillArray(arrayLength, array);
    
    printf("\nBAR CHART\n");
    
    printf("\t  ");
    for(i = 0; i < array[0]; i++){
        printf("_");
    }
    
    printf("\n");

    for(i = 0; i < arrayLength; i++){
        int x;
        printf("%3i %3i  |", i, array[i]);
        for(x = 0; x < array[i]; x++){
            printf("_");
        }
        if(array[i] > 0){
            printf("|");
        }
        if(!(i == arrayLength-1)){
            if(array[i] < array[i+1]){
                int excess = array[i+1] - array[i];
                for(x = 0; x < excess-1; x++){
                    printf("_");
                }
            }
        }
        printf("\n");
    }
    
    printf("\n");
    
    return 0;
}

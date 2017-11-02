// dice roll program
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    char test = argv[1];
    short val = strtol(test,NULL,10);
    
    int dice = argv[1];
    int i, dicerecord[argv[1]];// counts the amount of dice
    
    for (i = 0; i < dice; i++) {
        dicerecord[i] = rollDice();
        printf("Dice[%i]\n", i);
    }
    
    return 0;
}

int rollDice() {
    int rand;
    rand = rand() % 6;
    return rand;
}


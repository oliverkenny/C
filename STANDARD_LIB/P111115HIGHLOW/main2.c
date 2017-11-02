#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function prototypes
int playGame();
int getInput();
int getRand();
int getResult(int previousNumber, int userInput, int newNumber);
void printResult(int result);

int main() {
    int playgame = 1, credits = 5, games = 0; // accessable variables
    printf("Welcome to Low or High!\n");
    
    do{
    // print credits
    printf("Credits: %i\n", credits);
    // playgame loop
    int score = playGame();
    games++;
    if (score > 1){
        printf("Won 1 credit!\n");
        credits++;
    } else if (score == -1) {
        return 0;
    } else {
        printf("Lost 1 credit.\n");
        credits--;
    }
    
    
    printf("Play again? [y/n]: ");
    char replay;
    scanf(" %c", replay);
    getchar();
    
    if (replay == 'y'){
        playgame = 1;
    } else {
        playgame = 0;
    }
    } while (playgame == 1);
    printf("Finished with %i credits after %i games.\n", credits, games);
    
    return 0;
}

// function declarations
// playgame loop function
int playGame(){
    int previousNumber = -1, rounds = 3, x, randomNumber, result, input, score = 0; // stores the previous number generated
    
    // game loop
    for (x = 0; rounds > x; x++){
        if (previousNumber != -1) {            
            printf("Random Number: %i\n", randomNumber); // print random number
            result = getResult(previousNumber, input, randomNumber); // returns the result of the last round [0 or 1]
            score += result; // Add the result to the score
            printResult(result); // print the result
            input = getInput(); // gets the users guess
            if (input == -1) { // check for quit message
                printf("Quit was called\n");
                return -1;
            }
            previousNumber = randomNumber; // sets the random number to be the previous number to allow for another round
            randomNumber = getRand(); // generated the new random number
        } 
        else { // only execute if it is the first round
            previousNumber = getRand(); // get a random number generated and stores is as a baseline number for referal
            printf("Random Number: %i\n", previousNumber); // print random number
            input = getInput(); // gets the users input
            if (input == -1) { // check for quit message
                printf("Quit was called\n");
                return -1;
            }
            randomNumber = getRand();
        }
    }
    
    printf("Random Number: %i\n", randomNumber); // print random number
    result = getResult(previousNumber, input, randomNumber); // returns the result of the last round [0 or 1]
    printResult(result); // print the result
    score += result; // Add the result to the score
    
    printf("You scored %i/%i!\n", score, rounds);
    
    return score;
}

// calculates the result of a guess
int getResult(int previousNumber, int userInput, int newNumber){
    
    if (newNumber < previousNumber && userInput == 0) { // check tp see if the users guess was right
        return 1;
    } else if (newNumber > previousNumber && userInput == 1) {
        return 1;
    } else {
        return 0;
    }
    // return result [0 = loss or 1 = won] 
}

// takes user input of high or low
int getInput(){
    char x;
    printf("H or L: ");
    scanf(" %c", &x);
    
    switch (x) { // turns the input into a integer [-1,0,1]
        case 'H': // High returns 1
            return 1;
            break;
        case 'h': // High returns 1
            return 1;
            break;
        case 'L': // Low returns 0
            return 0;
            break;
        case 'l': // Low returns 0
            return 0;
            break;
        case 'X': // X returns -1 [exits the program]
            return -1;
            break;
        case 'x': // X returns -1 [exits the program]
            return -1;
            break;
        default: // this happens is an invalid case is intered
            printf("Error 101\n");
            return -1;
    }
}

// generates a random number
int getRand(){
    srand(time(NULL));
    int x = rand() % 10;
    return x; // returns the random generated number
}

void printResult(int result){ // either passes in a 0 or a 1
    if (result == 1){
        printf("Win!\n");
    } else {
        printf("Loss.\n");
    }
}
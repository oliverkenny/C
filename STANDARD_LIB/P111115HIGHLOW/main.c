// include libs
#include <stdio.h>
#include <time.h>

// Prototypes
int randGen();
int getInput();

// set global score for the game
int score = 0;

int main() { // start of the program
	
	int ui = NULL;

// printing menu
	printf("Welcome to high or low!\n");

	do {
// gen random number
	printf("Generating random number... \n");
	int r = randGen();
// print random number
	printf("%i\n", r);
// work out score
	getResult(r, ui);
// get user higher or lower
	ui = getInput();
// print user input
	printf("%i\n", ui);

//
	
	} while (ui != 2); // end of the game
	
	printf("Your final score was %i!\n", score);
	
	return 0; // end program
}

int randGen() { // generates a random number 
	int i = 50; // sets a number -- needs to be randomised
	return i;// return s the number
}

int getInput() { // get a usrs high or low value
	char ui;
	printf("Higher or Lower? [x = Exit]: ");
	scanf(" %c", &ui);
	switch (ui) {
	case 'l':
		return 0;
	case 'h':
		return 1;
	case 'x':
		return 2;
	default:
		printf("ERROR 101");
		return getInput();
	}
}

void getResult(int rand, int ui){
	if () {
	
	}
};

// shows how pointers work
// Oliver Kenny
#include <stdio.h>

// POINTER RULES
// [*] accesses the literate pointer varible for example "int number" in this case
// [pointer with no '*'] asseses the pointer address, the address of "int number" in this case
// Pointers allow for direct alterations to be made directly to a peice of memory rather than the forefront of a peice of data

void pminipulate(int *number) { // assign the passes pointer into another pointer variable
    *number = 25; // assign the inteter that the pointer accesses to a number '25' in this case
}

int main(int argc, char *argv[]) {

    int number = 10; // Init variable as normal
    int *ptr = NULL; // Creates pointers and assigns NULL value !IMPORTANT{Always assign null on creation}!
    ptr = &number; // set the pointer adress (pointer name without '*') to the number adress (use '&' to access the variable's adress)
    
    pminipulate(ptr); // pass ptr as an adress into the function
    
    printf("Return: %i\n", number); // prints whatever the number memory address holds
    printf("Return: %i\n", ptr);
    printf("Return: %i\n", &number);
    
    return 0; // exit the program
}
#include <stdio.h>
#include <stdlib.h>

void writefile(FILE *file, char *argv[]);
void printfile(FILE *file, char *argv[]);

int main(int argc, char *argv[]) {
    int check, charcount;
    
    printf("Exec' correctly. Args: %i \n", argc);
    printf("Opening \"%s\"\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "w+");
    
    // writefile(file, argv); // write to the file  
    
    printfile(file, argv); // printfile contents
    
    check = fclose(file);
    if(check == 0) // check if the file closed correctly
        printf("File, %s closed successfully.\n", argv[1]);
    else
        printf("Unsuccessful closure of file.\n");
    
    return 0;
}

void writefile(FILE *file, char *argv[]) {
    char sentence[128];
    printf("Write: ");
    scanf(" %[^\n]", sentence);
    int charcount = fprintf(file, sentence);
    printf("Written %i characters to the file %s.\n", charcount, argv[1]);
}

void printfile(FILE *file, char *argv[]) { // PROBLEM FUNCTION
    char c;
        printf("Printing %s...\n", argv[1]);
        while ((c = fgetc(file)) != EOF) {
            fputc(c, file);
        }
        printf("Hello this is a set line\n");
}
#include <stdio.h>
#include <allegro5/allegro>

int main(int argc, char *argv[]) {
    
    if(al_init()){
        printf("Allegro initialised correctly.\n");
    }
    
    return 0;
}
// Oliver Kenny
// Sample menu system
// gcc main.c -o main `pkg-config --libs allegro-5`

#include <allegro5/allegro.h>
#include <stdio.h>

int main()
{
    
    if(al_install_system(ALLEGRO_VERSION_INT, NULL)){
        printf("Initialised Correctly!\n");
    } else {
        printf("Initialisation Failed.\n");
        return 1;
    }
    
    printf("RAM SIZE: %iMb\n", al_get_ram_size());
    printf("CPU COUNT: %i\n", al_get_cpu_count());
    
    return 0;
}

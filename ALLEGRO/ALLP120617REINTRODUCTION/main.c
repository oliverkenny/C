#include <stdio.h>
#include <allegro5/allegro.h>

    // glabals
    int DISPLAY_WIDTH = 600;
    int DISPLAY_HEIGHT = 400;

int main(int argc, char **argv){
    
    // standard variables
    int placeholder = 0;
    
    // allegro pointer intialisation
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    
    // 
    if(!al_init()){
        printf("Allegro failed to initialise.\n");
        return -1;
    }
    
return 0;

}

// oliver kenny
// particles
// compile with : gcc main.c -o main `pkg-config --libs allegro-5`
#include <stdio.h>
#include <allegro5/allegro.h>

const int FPS = 60;
const int DISPLAY_W = 600;
const int DISPLAY_H = 400;

int main(int argc, char **argv){
    
    //standard variables
    bool redraw = true;
    int runtime;
    
    //get pointers ready
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    
    //intitalise all of the stuff
    if(!al_init()){
        printf("Allegro failed to initialise.\n");
        return -1;
    }
    
    display = al_create_display(DISPLAY_W, DISPLAY_H);
    if(!display){
        printf("Display failed to initialise.\n");
        return -1;
    }
    
    timer = al_create_timer(1.0/FPS);
    if(!timer){
        printf("Timer didn't initialise correctly.\n");
        return -1;
    }
    
    event_queue = al_create_event_queue();
    if(!event_queue){
        printf("Event queue went wrong...\n");
        return -1;
    }
    
    // event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    //start timers
    al_start_timer(timer);
    
    // main while loop
    while(1){
    
        
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER){
            runtime++;
            system("clear");
            printf("Runtime: %i\n", runtime/60);
            redraw = true;
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_flip_display();
        }
        
        
    }
        
    // destroy objects (pointers)
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    
    return 0;
}


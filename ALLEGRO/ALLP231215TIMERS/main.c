// Oliver Kenny
// Timers
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <math.h>

const float FPS = 10;

int main(int argc, char *argv[]) {
    
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;
    
    if(!al_init()){
        printf("Failed to initialise Allegro.\n");
        return -1;
    }
    
    timer = al_create_timer(1.0 / FPS);
    if(!timer){
        printf("Failed to initialise timer.\n");
        return -1;
    }
    
    display = al_create_display(500, 400);
    if(!display){
        printf("Failed to initialise display.\n");
        al_destroy_timer(timer);
        return -1;
    }
    
    event_queue = al_create_event_queue();
    if(!event_queue){
        printf("Failed to initialise event queue.\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    
    int i = 0;
    
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(i+=50, i+=50, i));
            al_flip_display();
        }
    }
    
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    return 0;
}
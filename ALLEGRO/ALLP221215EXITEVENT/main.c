// Oliver Kenny
// Exit event
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <stdio.h>
#include <allegro5/allegro.h>

int main(int argc, char *argv[]) {
    
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    
    if(!al_init()) {
        fprintf(stderr, "al_init failed\n");
        return -1;
    }
        
    display = al_create_display(500, 400);
    if(!display) {
        fprintf(stderr, "al_create_display failed\n");
        return -1;
    }
    
    event_queue = al_create_event_queue(); // initialise event queue. NTS: 'queue' is a strange word. 
    if(!event_queue) {
        fprintf(stderr, "al_create_event_queue failed\n");
        al_destroy_display(display);
        return -1;
    }
        
    al_register_event_source(event_queue, al_get_display_event_source(display)); // registers the display as an event source. Gets interactions with the display into the event queue so that they can be handled. (like the exit button being pressed)
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_flip_display();
    
    while(1) {
        ALLEGRO_EVENT ev; // create a place to store the current event 
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);
        
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_flip_display();
    }
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    printf("Exit successful.\n");
    
    return 0;
}
// Oliver Kenny
// COLOURCHANGE
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <stdio.h>
#include <allegro5/allegro.h>

// declare global variables
const float FPS = 60;
const int SCREEN_W = 600;
const int SCREEN_H = 400;
const int BOUNCER_W = 32;
const int BOUNCER_H = 32;

int main(int argc, char *argv[]) {
    
    // declare initial pointer values 
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    // set bitmap load co-ordinates
    float bouncer_x = (SCREEN_W / 2) - (BOUNCER_W / 2);
    float bouncer_y = (SCREEN_H / 2) - (BOUNCER_H / 2);
    int bouncer_color[3] = {255, 255, 255};
    int background_color[3] = {0, 0, 0};
    // standard variables
    bool redraw = true;
    
    // assign pointers
    if(!al_init()){
        printf("Error with al_init\n");
        return -1;
    };
    
    if(!al_install_mouse()){ // sets up a mouse subsystem
        printf("Error with al_install_mouse\n");
        return -1;
    }
    
    display = al_create_display(SCREEN_W, SCREEN_H); // creates the display
    if(!display){
        printf("Error with al_create_display\n");
        return -1;
    };
    
    event_queue = al_create_event_queue(); // creates the event queue
    if(!event_queue){
        printf("Error with al_create_event_queue\n");
        al_destroy_display(display);
        return -1;
    };
    
    timer = al_create_timer(1.0 / FPS); // creates the timer controlling FPS
    if(!event_queue){
        printf("Error with al_create_timer\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        return -1;
    };
    
    bouncer = al_create_bitmap(BOUNCER_W, BOUNCER_H); // creates the bitmap image (bouncer)
    if(!bouncer){
        printf("Error with al_create_bitmap\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    };
    
    al_set_target_bitmap(bouncer); // target bouncer for editing
    
    al_clear_to_color(al_map_rgb(bouncer_color[0], bouncer_color[1], bouncer_color[2])); // set color for bouncer
    
    al_set_target_bitmap(al_get_backbuffer(display)); // target backbuffer for editing
    
    al_clear_to_color(al_map_rgb(background_color[0], background_color[1], background_color[2])); // set background color for background
    
    al_flip_display(); // flip buffer
    
    // set event sources
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    al_start_timer(timer); // start timer
    
    while(1){ // main animation loop 
        ALLEGRO_EVENT ev; // creates a place to store the currecnt event
        al_wait_for_event(event_queue, &ev); // sets a place to stop until an event is present
        
        if(ev.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            bouncer_x = ev.mouse.x - (BOUNCER_W / 2);
            bouncer_y = ev.mouse.y - (BOUNCER_H / 2);
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            int i;
            for(i = 0; i < 3; i++) {
                *(bouncer_color+i) = *(bouncer_color+i) + 150;
            }
        }
        
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_set_target_bitmap(bouncer);
            al_clear_to_color(al_map_rgb(bouncer_color[0], bouncer_color[1], bouncer_color[2])); 
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(background_color[0], background_color[2], background_color[2]));
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
                       
            al_flip_display();
        }
    }
    
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_bitmap(bouncer);
    
    return 0;
}
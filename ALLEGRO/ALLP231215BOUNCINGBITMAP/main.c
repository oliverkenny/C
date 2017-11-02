// Oliver Kenny
// Bouncing Bitmap
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <stdio.h>
#include <allegro5/allegro.h>

const float FPS = 60; // set the FPS for the program
const int SCREEN_W = 1300; // set screen width
const int SCREEN_H = 400; // set screen height
const int BOUNCER_SIZE = 128; // set the size of the bitmap image

int main(int argc, char *argv[]) {
    
    ALLEGRO_DISPLAY *display = NULL; // create display pointer
    ALLEGRO_TIMER *timer = NULL; // create timer pointer
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; // create event queue pointer
    ALLEGRO_BITMAP *bouncer = NULL; // create bitmap pointer
    float bouncer_x = (SCREEN_W / 2) - (BOUNCER_SIZE / 2); // set the starting position on the x axis for the bitmap square
    float bouncer_y = (SCREEN_H / 2) - (BOUNCER_SIZE / 2); // set the starting position on the y axis for the bitmap square
    float bouncer_dx = -4.0, bouncer_dy = 4.0; // I don't know what this does yet.
    bool redraw = true;
    
    if(!al_init()){ // Initialise allegro
        printf("Error 1\n");
        return -1;
    }
    
    timer = al_create_timer(1.0 / FPS); // Initialise FPS timer
    if(!timer){
        printf("Error 2\n");
        return -1;
    }
    
    display = al_create_display(SCREEN_W, SCREEN_H); // Initialise display
    if(!display){
        printf("Error 3\n");
        al_destroy_timer(timer);
        return -1;
    }
    
    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE / 2); // Initialise bouncer bitmap(rectangle bitmap drawing)
    if(!bouncer){
        printf("Error 4\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
    
    al_set_target_bitmap(bouncer); // sets the active target as the bitmap object. Do this to say what is is you're changing.
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(display));
    
    event_queue = al_create_event_queue(); // Initialise event queue
    if(!event_queue){
        printf("Error 5\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_bitmap(bouncer);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_flip_display();
    
    al_start_timer(timer);
    
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {
                bouncer_dx = -bouncer_dx;
            }
 
            if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE / 2) {
                bouncer_dy = -bouncer_dy;
            }
 
            bouncer_x += bouncer_dx;
            bouncer_y += bouncer_dy;
 
            redraw = true;
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            al_flip_display();
        }
    }
    
    al_destroy_bitmap(bouncer);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    
    return 0;
}
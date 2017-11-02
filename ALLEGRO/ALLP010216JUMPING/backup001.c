// Oliver and Callum
#include <stdio.h>
#include <allegro5/allegro.h>

const int FPS = 60;
const int SCREEN_W = 700;
const int SCREEN_H = 500;

int main(int argc, char *argv[]) {
    
    // looping
    bool doexit = false;
    bool redraw = false;
    
    // size
    int floor_w = SCREEN_W;
    int floor_h = 100;
    int character_w = 32;
    int character_h = 32;
    
    // positioning
    int floor_x = 0;
    int floor_y = SCREEN_H - floor_h;
    int character_x = SCREEN_W / 5;
    int character_y = SCREEN_H - floor_h - character_h;
    
    // colours
    int color_background[3] = {44, 62, 80};
    int color_floor[3] = {52, 73, 94};
    int color_character[3] = {46, 204, 113};
    
    //pointers
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *floor = NULL;
    ALLEGRO_BITMAP *character = NULL;
    
    if(!al_init()){
        printf("Allegro failed to initialise.\n");
        return -1;
    }
    
    if(!al_install_mouse()){
        printf("Allegro failed to initialise mouse.\n");
        return -1;
    }
    
    if(!al_install_keyboard()){
        printf("Allegro failed to initialise keyboard.\n");
        return -1;
    }
    
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display){
        printf("Allegro failed to initialise display.\n");
        return -1;
    }
    
    event_queue = al_create_event_queue();
    if(!event_queue){
        printf("Allegro failed to initialise event queue.\n");
        al_destroy_display(display);
        return -1;
    }
    
    timer = al_create_timer(1.0/FPS);
    if(!timer){
        printf("Allegro failed to initialise timer.\n");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }
    
    floor = al_create_bitmap(floor_w, floor_h);
    if(!floor){
        printf("Allegro failed to initialise floor.\n");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return -1;
    }
    
    character = al_create_bitmap(character_w, character_h);
    if(!character){
        printf("Allegro failed to initialise character.\n");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        al_destroy_bitmap(floor);
        return -1;
    }
    
    // register event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    // start timer
    al_start_timer(timer);
    
    // while loop
    while (!doexit) {
        // wait for event
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        // FPS timer
        if(ev.timer.source == timer){
            redraw = true;
        }
        
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        
        if(redraw && al_is_event_queue_empty(event_queue)){
            
            al_set_target_bitmap(floor);
            al_clear_to_color(al_map_rgb(color_floor[0], color_floor[1], color_floor[2]));
            
            al_set_target_bitmap(character);
            al_clear_to_color(al_map_rgb(color_character[0], color_character[1], color_character[2]));
            
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(color_background[0], color_background[1], color_background[2]));
            
            al_draw_bitmap(floor, floor_x, floor_y, 0);
            al_draw_bitmap(character, character_x, character_y, 0);
            
            al_hide_mouse_cursor(display);
            al_flip_display();
            redraw = false;
        }
    }
    
    // Pre-Termination
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(floor);
    al_destroy_bitmap(character);
    
    return 0;
}
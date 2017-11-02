// Oliver and Callum
// compile with : gcc main.c -o main `pkg-config --libs allegro-5.0`
#include <stdio.h>
#include <allegro5/allegro.h>

bool collisionDetect(int obstacle_x, int obstacle_y, int obstacle_w, int obstacle_h, int character_x, int character_y, int character_w, int character_h){
    if(character_x < obstacle_x + obstacle_w &&
        character_y < obstacle_y + obstacle_h &&
        character_x + character_w > obstacle_x &&
        character_y + character_h > obstacle_y){
        return true; 
    } else {
        return false;
    }
}

void set_color(int *array, int color_one, int color_two, int color_three) {
    if(color_one <= 255 && color_one >= 0 &&
        color_two <= 255 && color_two >= 0 &&
        color_three <= 255 && color_three >= 0){
        int i;
        *array++ = color_one;
        *array++ = color_two;
        *array = color_three;
    }
}

const int FPS = 60;
const int SCREEN_W = 700;
const int SCREEN_H = 500;

enum MYKEYS {
    UP, DOWN, LEFT, RIGHT
};

int main(int argc, char *argv[]) {
    
    // physics
    int character_velocity = 0;
    int gravity = 10;
    int acceleration = 5;
    
    // looping
    bool doexit = false;
    bool redraw = false;
    bool key[4] = {false, false, false, false};
    
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
            
            // is an arrow key pressed?
            if(key[UP]||key[DOWN]||key[LEFT]||key[RIGHT]){
                if(key[UP]){
                    if(!collisionDetect(0, 0, SCREEN_W, 0, character_x, character_y, character_w, character_h)){
                        character_y = character_y - acceleration;
                        set_color(color_character, 46, 204, 113);
                    } else {
                        set_color(color_character, 255, 0, 0);
                    }
                } else if(key[DOWN]){
                    if(!collisionDetect(floor_x, floor_y, floor_w, floor_h, character_x, character_y + acceleration, character_w, character_h)){
                        set_color(color_character, 46, 204, 113);
                        character_y = character_y + acceleration;
                    }
                } else if(key[LEFT]){
                    if(!collisionDetect(0, 0, 0, SCREEN_H, character_x - acceleration, character_y, character_w, character_h)){
                        set_color(color_character, 46, 204, 113);
                        character_x = character_x - acceleration;
                    } else {
                        set_color(color_character, 255, 0, 0);
                    }
                } else if(key[RIGHT]){
                    if(!collisionDetect(SCREEN_W, 0, 0, SCREEN_H, character_x, character_y, character_w, character_h)){
                        set_color(color_character, 46, 204, 113);
                        character_x = character_x + acceleration;
                    } else {
                        set_color(color_character, 255, 0, 0);
                    }
                }
            }
            
            redraw = true;
        }
        
        // close display
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        
        // key press down
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[UP] = true;
                    break;
    
                case ALLEGRO_KEY_DOWN:
                    key[DOWN] = true;
                    break;
    
                case ALLEGRO_KEY_LEFT: 
                    key[LEFT] = true;
                    break;
    
                case ALLEGRO_KEY_RIGHT:
                    key[RIGHT] = true;
                    break;
            }
        }
        
        // key press up
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[UP] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[RIGHT] = false;
               break;
            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
         }
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
            
            // al_hide_mouse_cursor(display);
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
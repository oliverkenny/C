                                                                                                                                                                                                                                                                // Oliver Kennygcc main.c -o main `pkg-config --libs allegro-5.0` -lm
// Jump
// Compile with: 
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"
//TODO
//
// SET MAX VELOCITY
// IMPLIMENT Y VELOCITY
//
//

#include <stdio.h>
#include <allegro5/allegro.h>
#include <math.h>
#include <stdlib.h>

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

enum MYKEYS {
    UP, DOWN, LEFT, RIGHT
};

//global variables [display]
const float FPS = 60;
const float DEBUG_TIMER = 10;
const int DISPLAY_WIDTH = 600;
const int DISPLAY_HEIGHT = 400;

//global variables [obstacles]
const int FLOOR_DEPTH = 50;


int main(int argc, char *argv[]) {
    
    // allegro objects initialisation
    ALLEGRO_DISPLAY *main_display = NULL;
    ALLEGRO_TIMER *main_timer = NULL;
    ALLEGRO_EVENT_QUEUE *main_event_queue = NULL;
    ALLEGRO_BITMAP *bitmap_floor = NULL;
    ALLEGRO_BITMAP *bitmap_ledge = NULL;
    ALLEGRO_BITMAP *bitmap_character = NULL;
    ALLEGRO_TIMER *debug_timer = NULL;
    
    // color variables
    int background_color[3] = {255, 255, 255};
    int floor_color[3] = {0, 0, 0};
    int ledge_color[3] = {0, 0, 0};
    int character_color[3] = {255, 0, 0};
    
    // size variables
    int floor_width = DISPLAY_WIDTH;
    int floor_height = 50;
    int ledge_width = 200;
    int ledge_height = 50;
    int character_width = 50;
    int character_height = 50;
    
    // placement variables
    int floor_x = 0;
    int floor_y = DISPLAY_HEIGHT - floor_height;
    int ledge_x = DISPLAY_WIDTH - 250;
    int ledge_y = DISPLAY_HEIGHT - 200;
    int character_x = DISPLAY_WIDTH - 50;
    int character_y = DISPLAY_HEIGHT - (floor_height + character_height);
    
    // game variables
    bool redraw = true;
    bool doexit = false;
    bool key[4] = {false, false, false, false};
    
    // character variables
    double character_vector[2] = {0, 0};
    double character_vector_max = 10;
    double character_vector_min = -10;
    double character_acceleration = 1;
    bool character_airborn = false;
    double gravity = 5;
    
    
    // assign values to pointers
    if(!al_init()){ // initialises allegro
        printf("code [al_init()] returned faliure.\n");
        return(-1);
    }
    
    if(!al_install_keyboard()){ // initialises keyboard
        printf("code [al_install_keyboard()] returned faliure.\n");
        return(-1);
    }
    
    if(!al_install_mouse()){ // initialises mouse
        printf("code [al_install_mouse()] returned faliure.\n");
        return(-1);
    }
    
    main_display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(!main_display){ // create display
        printf("code [al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT)] returned faliure.\n");
        return(-1);
    }
    
    main_timer = al_create_timer(1.0 / FPS); // create timer
    if(!main_timer){
        printf("code [al_create_timer(1.0 / FPS)] returned faliure.\n");
        al_destroy_display(main_display); // destroys display
        return(-1);
    }
    
    main_event_queue = al_create_event_queue(); // creates event queue
    if(!main_event_queue){
        printf("code [al_create_event_queue()] returned faliure.\n");
        al_destroy_display(main_display); // destroys display
        al_destroy_timer(main_timer); // destroys timer
        return(-1);
    }
    
    bitmap_floor = al_create_bitmap(floor_width, floor_height); // creates bitmap
    if(!bitmap_floor){
        printf("code [al_create_bitmap(floor_width, floor_height)] returned faliure.\n");
        al_destroy_display(main_display); // destroys display
        al_destroy_timer(main_timer); // destroys timer
        al_destroy_event_queue(main_event_queue); // destroys event queue
        return(-1);
    }
    
    bitmap_ledge = al_create_bitmap(ledge_width, ledge_height); // creates bitmap
    if(!bitmap_ledge){
        printf("code [al_create_bitmap(ledge_width, ledge_height)] returned faliure.\n");
        al_destroy_display(main_display); // destroys display
        al_destroy_timer(main_timer); // destroys timer
        al_destroy_event_queue(main_event_queue); // destroys event queue
        al_destroy_bitmap(bitmap_floor); // destroys bitmap
        return(-1);
    }
    
    bitmap_character = al_create_bitmap(character_width, character_height); // creates bitmap
    if(!bitmap_character){
        printf("code [al_create_bitmap(character_width, character_height)] returned faliure.\n");
        al_destroy_display(main_display); // destroys display
        al_destroy_timer(main_timer); // destroys timer
        al_destroy_event_queue(main_event_queue); // destroys event queue
        al_destroy_bitmap(bitmap_floor); // destroys bitmap
        al_destroy_bitmap(bitmap_ledge); // destroys bitmap
        return(-1);
    }
    
    debug_timer = al_create_timer(1.0/DEBUG_TIMER);
    if(!debug_timer){
        printf("code [al_create_timer(1.0/DEBUG_TIMER)] returned faliure.\n");
        al_destroy_display(main_display); // destroys display
        al_destroy_timer(main_timer); // destroys timer
        al_destroy_event_queue(main_event_queue); // destroys event queue
        al_destroy_bitmap(bitmap_floor); // destroys bitmap
        al_destroy_bitmap(bitmap_ledge); // destroys bitmap
        al_destroy_bitmap(bitmap_character); // destroys bitmap
        return(-1);
    }
    
    // register event source(s)
    al_register_event_source(main_event_queue, al_get_display_event_source(main_display)); // register display as event source
    al_register_event_source(main_event_queue, al_get_timer_event_source(main_timer)); // register timer as event source
    al_register_event_source(main_event_queue, al_get_timer_event_source(debug_timer)); // register timer as event source
    al_register_event_source(main_event_queue, al_get_mouse_event_source()); // register mouse as event source
    al_register_event_source(main_event_queue, al_get_keyboard_event_source()); // register keyboard as event source
    
    // set first frame of the display
    al_set_target_bitmap(bitmap_floor); // set floor bitmap as target
    al_clear_to_color(al_map_rgb(floor_color[0], floor_color[1], floor_color[2])); // set color
    al_set_target_bitmap(bitmap_ledge); // set ledge bitmap as target
    al_clear_to_color(al_map_rgb(ledge_color[0], ledge_color[1], ledge_color[2])); // set color
    al_set_target_bitmap(bitmap_character); // set character bitmap as target
    al_clear_to_color(al_map_rgb(character_color[0], character_color[1], character_color[2])); // set color
    al_set_target_bitmap(al_get_backbuffer(main_display)); // set backbuffer as target
    al_clear_to_color(al_map_rgb(background_color[0], background_color[1], background_color[2])); // set color
    
    al_start_timer(main_timer); // start FPS timer
    al_start_timer(debug_timer); // starts the debugging timer
    
    while(!doexit) { // start main game loop
        
        ALLEGRO_EVENT ev; // make a place to store current event
        al_wait_for_event(main_event_queue, &ev); // wait for an event to happen
        
        if(ev.type == ALLEGRO_EVENT_TIMER){ // if a timer was triggered
            if(ev.timer.source == main_timer) { // check to see if the timer was the FPS timer
                
                character_airborn = !collisionDetect(0, 0, floor_width, floor_height, character_x, character_y, character_width, character_height);
                
                
                
                // action of the game
                // x axis of the character
                if(key[LEFT]){
                    if(character_vector[0] <= 0 && character_vector[0] > character_vector_min){
                        character_vector[0] -= character_acceleration;
                    } else if(character_vector[0] >= 0){
                        character_vector[0] -= character_acceleration;
                    }
                } else if (key[RIGHT]) {
                    if(character_vector[0] >= 0 && character_vector[0] < character_vector_max){
                        character_vector[0] += character_acceleration;
                    } else if(character_vector[0] <= 0 && character_vector[0] < character_vector_max){
                        character_vector[0] += character_acceleration;
                    }
                } else if(!key[LEFT], !key[RIGHT]){
                    if(character_vector[0] < 0){
                        character_vector[0] += character_acceleration;
                    } else if (character_vector[0] > 0) {
                        character_vector[0] -= character_acceleration;
                    }
                } else if (key[LEFT] && key[RIGHT]) {
                    if(character_vector[0] < 0){
                        character_vector[0] += character_acceleration;
                    } else if (character_vector[0] > 0) {
                        character_vector[0] -= character_acceleration;
                    }
                }
                character_x += character_vector[0];
                
                // y axis of the character
                if(key[DOWN]){
                    character_vector[1] += 1;
                }
                if(key[UP]){
                    character_vector[1] -= 1;
                }
                if(!key[DOWN] && !key[UP]){
                    if(character_vector[1] < 0){
                        character_vector[1] += 1;
                    } else if (character_vector[1] > 0) {
                        character_vector[1] -= 1;
                    }
                    //character_vector[1] = 0;
                }
                if(key[DOWN] && key[UP]){
                    if(character_vector[1] < 0){
                        character_vector[1] -= gravity;
                    } else if (character_vector[1] > 0){
                        character_vector[1] += gravity;
                    }
                }
                //collisionDetect
                if(collisionDetect(floor_x, floor_y, floor_width, floor_height, character_x, character_y, character_width, character_height)){
                    character_airborn = false;
                    if(character_vector[1] >= 0){
                        character_vector[1] = 0;
                    }
                }
                character_y += character_vector[1];
                redraw = true;
            } else if (ev.timer.source == debug_timer) {
                // all of the debugging variables get printed
                system("clear");
                printf("x: %f, y: %f\n", character_vector[0], character_vector[1]);
                if(key[LEFT]){
                    printf("LEFT: TRUE\n");
                } else {
                    printf("LEFT: FALSE\n");
                }
                if(key[RIGHT]){
                    printf("RIGHT: TRUE\n");
                } else {
                    printf("RIGHT: FALSE\n");
                }
                if(key[UP]){
                    printf("UP: TRUE\n");
                } else {
                    printf("UP: FALSE\n");
                }
                if(key[DOWN]){
                    printf("DOWN: TRUE\n");
                } else {
                    printf("DOWN: FALSE\n");
                }
                if(!character_airborn){
                    printf("AIRBORN: FALSE\n");
                } else {
                    printf("AIRBORN: TRUE\n");
                }
                
            }
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode){
                
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
        } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
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
            }
        }
        
        if(redraw && al_is_event_queue_empty(main_event_queue)) { // check to see if the screen should redraw
            redraw = false;
            al_set_target_bitmap(bitmap_floor); // set floor bitmap as target
            al_clear_to_color(al_map_rgb(floor_color[0], floor_color[1], floor_color[2])); // set color
            al_set_target_bitmap(bitmap_ledge); // set ledge bitmap as target
            al_clear_to_color(al_map_rgb(ledge_color[0], ledge_color[1], ledge_color[2])); // set color
            al_set_target_bitmap(bitmap_character); // set character bitmap as target
            al_clear_to_color(al_map_rgb(character_color[0], character_color[1], character_color[2])); // set color
            al_set_target_bitmap(al_get_backbuffer(main_display)); // set backbuffer as target
            al_clear_to_color(al_map_rgb(background_color[0], background_color[1], background_color[2])); // set color
            al_draw_bitmap(bitmap_floor, floor_x, floor_y, 0); // draw floor
            al_draw_bitmap(bitmap_ledge, ledge_x, ledge_y, 0); // draw ledge
            al_draw_bitmap(bitmap_character, character_x, character_y, 0); // draw character
            al_flip_display();
        } 
        
    }
    
    // finish by destroying pointers
    al_destroy_display(main_display); // destroys display
    al_destroy_timer(main_timer); // destroys timer
    al_destroy_event_queue(main_event_queue); // destroys event queue
    al_destroy_bitmap(bitmap_floor); // destroys bitmap
    al_destroy_bitmap(bitmap_ledge); // destroys bitmap
    al_destroy_bitmap(bitmap_character); // destroys bitmap
    
    return 0;
}

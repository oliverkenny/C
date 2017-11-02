// ------------------------------------//
//          NOTES                      //
// ------------------------------------//
/* Predicted appearance:
 * 
 *      _____________________
 *      |                   |
 *      |   _____________   |
 *      |   |           |   |
 *      |   |  *     *  |   |
 *      |   |           |   |
 *      |   |  *     *  |   |
 *      |   |___________|   |
 *      |                   |
 *      |                   |
 *      |   _____________   |
 *      |   |           |   |
 *      |   |  *     *  |   |
 *      |   |     *     |   |
 *      |   |  *     *  |   |
 *      |   |___________|   |
 *      |                   |
 *      |     RANDOMISE     |
 *      |                   |               
 *      |Dice A: 4/Dice B:5 |
 *      |___________________|
 * 
 * 
 * BLUE HIGHLIGHT = DEBUG CODE
*/
// ------------------------------------//
//          INCLUDE LIBRARYS           //
// ------------------------------------//

#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// ---------------------------------------//
//          FUNCTION PROTOTYPES           //
// ---------------------------------------//

int ok_random_number_generator(int min_number, int max_number);
bool ok_is_mouse_over_rectangle(int obj_tl_x, int obj_tl_y, int obj_width, int obj_height, int mouse_x, int mouse_y);

// ------------------------------------//
//          GLOBAL VARIABLES           //
// ------------------------------------//

const int FPS = 60;
const int DISPLAY_WIDTH = 300;
const int DISPLAY_HEIGHT = 500;

// ------------------------------------//
//          MAIN FUNCTION              //
// ------------------------------------//

int main(int argc, char *argv[]) {
    
// -------------------------------------//
//          POINTER VARIABLES           //
// -------------------------------------//
    
    ALLEGRO_DISPLAY *display = NULL; // main display pointer
    ALLEGRO_TIMER *timer = NULL; // main timer pointer
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; // main event queue timer
    ALLEGRO_TIMER *fps_timer = NULL; // frames per second timer
    ALLEGRO_BITMAP *dice_one = NULL; // dice one bitmap
    ALLEGRO_BITMAP *dice_two = NULL; // dice two bitmap
    ALLEGRO_BITMAP *roll_button = NULL; // re-roll button
    
// ------------------------------------//
//          VARIABLES                  //
// ------------------------------------//

    bool redraw = true; // should the backbuffer be drawn and swapped?
    bool doexit = false; // should the program exit?
    bool pause = false; // is program pasued?
    bool is_mouse_clicked = false; // is the mouse button down?
    int frames_this_second = 0; // incremented when a frame is drawn
    int fps_rate; // counts the total fps to display
    int dice_one_value = 0; // dice value for dice one
    int dice_two_value = 0; // dice value for dice two

// ------------------------------------//
//         ALLEGRO VARIABLES           //
// ------------------------------------//
   
    // background variables
    int background_color[3] = {255, 255, 255}; // display background color
    // bottom section
    int bottom_section_height = 70;
    // dice one variables
    int dice_one_padding = 20; // edge padding
    int dice_one_width = DISPLAY_WIDTH - (dice_one_padding * 2); // dice width
    int dice_one_height = (DISPLAY_HEIGHT / 2) - ((dice_one_padding * 2) + bottom_section_height / 2); // dice height
    int dice_one_xpos = dice_one_padding; // dice x position (display relative)
    int dice_one_ypos = dice_one_padding; // dice y position (display relative)
    int dice_one_radius = 10; // edge radius
    int dice_one_color[3] = {44, 62, 80}; // dice color
    // dice two variables
    int dice_two_padding = dice_one_padding; // edge padding
    int dice_two_width = DISPLAY_WIDTH - (dice_two_padding * 2); // dice width
    int dice_two_height = (DISPLAY_HEIGHT / 2) - ((dice_two_padding * 2) + bottom_section_height / 2); // dice height
    int dice_two_xpos = dice_two_padding; // dice x position (display relative)
    int dice_two_ypos = dice_two_padding + (dice_one_height + dice_one_padding); // dice y position (display relative)
    int dice_two_radius = 10; // edge radius
    int dice_two_color[3] = {44, 62, 80}; // dice color
    // roll button
    int roll_button_width = dice_one_width;
    int roll_button_height = 50;
    int roll_button_padding = (bottom_section_height - (roll_button_height)) / 2;
    int roll_button_xpos = (DISPLAY_WIDTH / 2) - (roll_button_width / 2);
    int roll_button_ypos = DISPLAY_HEIGHT - (bottom_section_height + roll_button_padding);
    int roll_button_radius = 0;
    int roll_button_color[3] = {39, 174, 96};
    
// ------------------------------------//
//          INITIALISATIONS            //
// ------------------------------------//

    al_init(); // init allegro
    al_install_mouse(); // init mouse
    al_install_keyboard(); // init keyboard
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); // create display
    timer = al_create_timer(1.0 / FPS); // create timer
    event_queue = al_create_event_queue(); // create event queue[still a strange word]
    fps_timer = al_create_timer(1); // create timer for frames per second
    dice_one = al_create_bitmap(dice_one_width, dice_one_height); // creates dice one
    dice_two = al_create_bitmap(dice_two_width, dice_two_height); // creates dice two
    roll_button = al_create_bitmap(roll_button_width, roll_button_height); // created roll button
    
// --------------------------------------------//
//          REGISTER EVENT SOURCE[S]           //
// --------------------------------------------//
    
    al_register_event_source(event_queue, al_get_display_event_source(display)); // set display event source
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); // set timer event source
    al_register_event_source(event_queue, al_get_keyboard_event_source()); // set keyboard event source
    al_register_event_source(event_queue, al_get_mouse_event_source()); // set mouse event source
    al_register_event_source(event_queue, al_get_timer_event_source(fps_timer)); // get frames per second timer events
    
// ------------------------------------//
//          START TIMER[S]             //
// ------------------------------------//
    
    al_start_timer(timer); // starts main timer
    al_start_timer(fps_timer); // starts frames per second timer
    
// ------------------------------------//
//          START WHILE LOOP           //
// ------------------------------------//
    
    while(!doexit){ // unless doexit is true, continue looping
        
        ALLEGRO_EVENT ev; // set place to store current event
        al_wait_for_event(event_queue, &ev); // wait until an event is placed in event queue
        
// ------------------------------------------//
//         IF MAIN TIMER IS CALLED           //
// ------------------------------------------//
        
        if(ev.timer.source == timer){
            
            
            
            redraw = true;
        }
        
// ------------------------------------------//
//         IF FPS TIMER IS CALLED            //
// ------------------------------------------//

        else if(ev.timer.source == fps_timer){
            fps_rate = frames_this_second; // sets the current fps rate 
            frames_this_second = 0; // resets the fps counter
            // printf("FPS: %d\n", fps_rate); // prints the fps to screen
        }
        
// -----------------------------------------------//
//         IF THE 'X' BUTTON IS PRESSED           //
// -----------------------------------------------//

        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            doexit = true;
        }
        
// -------------------------------------------------//
//         IF MOUSE BUTTON ENTERS DISPLAY           //
// -------------------------------------------------//

        else if(ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            
        }
        
// -------------------------------------------------//
//         IF MOUSE BUTTON EXITS DISPLAY            //
// -------------------------------------------------//

        else if(ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
            
        }
        
// --------------------------------------//
//         MOUSE BUTTON DOWN             //
// --------------------------------------//

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            printf("DOWN\n");
            is_mouse_clicked = true;
        }
        
// --------------------------------------//
//         MOUSE BUTTON UP               //
// --------------------------------------//
        
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            is_mouse_clicked = false;
        }
        
// -------------------------------------------------//
//         IF MOUSE BUTTON AXIS CHANGES             //
// -------------------------------------------------//

        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
        ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            if(ok_is_mouse_over_rectangle(roll_button_xpos, roll_button_ypos, roll_button_width, roll_button_height, ev.mouse.x, ev.mouse.y)){
                if(is_mouse_clicked){
                    printf("YES\n");
                    roll_button_color[0] = 26;
                    roll_button_color[1] = 188;
                    roll_button_color[2] = 156;
                    redraw = true;
                } else {
                    printf("NO\n");
                    roll_button_color[0] = 46;
                    roll_button_color[1] = 204;
                    roll_button_color[2] = 113;
                    redraw = true;
                }
            } else {
                roll_button_color[0] = 39;
                roll_button_color[1] = 174;
                roll_button_color[2] = 96;
                redraw = true;
            }
        }
        
// -------------------------//
//         RENDER           //
// -------------------------//

        if(redraw &&
        al_is_event_queue_empty(event_queue)){
            
            //roll button
            al_set_target_bitmap(roll_button); // set roll button as target
            al_clear_to_color(al_map_rgb(roll_button_color[0], roll_button_color[1], roll_button_color[2])); // set roll button color
            
            // dice one
            al_set_target_bitmap(dice_one); // set dice one as target
            al_clear_to_color(al_map_rgb(dice_one_color[0], dice_one_color[1], dice_one_color[2])); // set dice one color
            
            //dice two
            al_set_target_bitmap(dice_two); // set dice two as target
            al_clear_to_color(al_map_rgb(dice_two_color[0], dice_two_color[1], dice_two_color[2])); // set dice two color
            
            // background
            al_set_target_bitmap(al_get_backbuffer(display)); // target the backbuffer background
            al_clear_to_color(al_map_rgb(background_color[0], background_color[1], background_color[2])); // set background color
            
            
            
            //draw all
            al_draw_bitmap(roll_button, roll_button_xpos, roll_button_ypos, 0); // draw roll button
            al_draw_bitmap(dice_one, dice_one_xpos, dice_one_ypos, 0); // draw dice one
            al_draw_bitmap(dice_two, dice_two_xpos, dice_two_ypos, 0); // draw dice two
            
            // generic rendering
            al_flip_display(); // set backbuffer to main display
            redraw = false; // set to false so no redraw occurs unless an event occurs
            frames_this_second++; // increment frames drawn this second
        }
        
// -------------------------------------//
//          END OF WHILE LOOP           //
// -------------------------------------//
        
    } // ends the main while loop
    
// ----------------------------------------//
//          DEREFERENCE POINTERS           //
// ----------------------------------------//

    al_destroy_display(display); // destroy display
    al_destroy_timer(timer); // destroy timer
    al_destroy_event_queue(event_queue); // destroy event queue
    
// ------------------------------------//
//          END OF MAIN                //
// ------------------------------------//
    
} // end of main function

// ------------------------------------------//
//          FUNCTION DEFINITITIONS           //
// ------------------------------------------//

int ok_random_number_generator(int min_number, int max_number){
    int random_number;
    int number_difference = max_number - min_number;
    srand(time(NULL));
    random_number = rand() % number_difference + min_number;
    return random_number;
}

bool ok_is_mouse_over_rectangle(int obj_tl_x, int obj_tl_y, int obj_width, int obj_height, int mouse_x, int mouse_y){
    if( mouse_x > obj_tl_x &&
        mouse_x < obj_tl_x + obj_width &&
        mouse_y > obj_tl_y &&
        mouse_y < obj_tl_y + obj_height){
            return true;
        } else {
            return false;
        }
}
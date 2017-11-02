// Oliver Kenny
// obstacle
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0 allegro_ttf-5.0 allegro_font-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

enum MYKEYS {
    UPKEY, DOWNKEY, LEFTKEY, RIGHTKEY
};

// declare global variables
const float FPS = 59;
const int SCREEN_W = 600;
const int SCREEN_H = 400;
 int BOUNCER_W = 8;
 int BOUNCER_H = 8;
 int BOUNCERTWO_W = 8;
 int BOUNCERTWO_H = 8;
const int OBSTACLE_WIDTH = 2; // e.g. 1/3 of the page width
const float FONT_SIZE = 14.0;

int main(int argc, char *argv[]) {
    
    // declare initial pointer values 
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    ALLEGRO_BITMAP *obstacle = NULL;
    ALLEGRO_BITMAP *bouncertwo = NULL;
    ALLEGRO_TIMER *fpscounttimer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *font_basictitlefont = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_BITMAP *sound_on = NULL;
    ALLEGRO_BITMAP *sound_off = NULL;
    // set bitmap load co-ordinates
    float bouncer_x = (SCREEN_W / 2);
    float bouncer_y = (SCREEN_H / 2) - (BOUNCER_H / 2);
    float bouncertwo_x = (SCREEN_W / 2) - BOUNCERTWO_W;
    float bouncertwo_y = (SCREEN_H / 2) - (BOUNCERTWO_H);
    int bouncer_color[3] = {230, 126, 34};
    int bouncertwo_color[3] = {0, 0, 0};
    int background_color[3] = {231, 76, 60};
    int font_color[3] = {0, 0, 0};
    int font_basictitlefont_color[3] = {0, 0, 0};
    int sound_on_x = 10;
    int sound_off_x = 10;
    int sound_on_y = 10;
    int sound_off_y = 10;
    // obstacle variables
    float obstacle_width = SCREEN_W / OBSTACLE_WIDTH;
    float obstacle_height = SCREEN_H;
    int obstacle_x = 0;
    int obstacle_y = 0;
    int obstacle_color[3] = {241, 196, 15};
    // standard variables
    bool redraw = true;
    int fpstimer = 0;
    int fpscount;
    bool key[4] = {false, false, false, false};
    bool doexit = false;
    bool is_sound_on = true;
    ALLEGRO_SAMPLE_ID id;
    
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
    
    fpscounttimer = al_create_timer(1); // creates the timer controlling FPS
    if(!fpscounttimer){
        printf("Error with al_create_timer[fps count timer] \n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    };
    
    bouncer = al_create_bitmap(BOUNCER_W, BOUNCER_H); // creates the bitmap image (bouncer)
    if(!bouncer){
        printf("Error with al_create_bitmap\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_timer(fpscounttimer);
        return -1;
    };
    
    bouncer = al_create_bitmap(BOUNCER_W, BOUNCER_H); // creates the bitmap image (bouncer)
    if(!bouncer){
        printf("Error with al_create_bitmap[bouncer]\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_timer(fpscounttimer);
        return -1;
    };
    
    obstacle = al_create_bitmap(obstacle_width, obstacle_height); // creates the bitmap image (bouncer)
    if(!obstacle){
        printf("Error with al_create_bitmap[obstacle]\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(bouncer);
        al_destroy_timer(fpscounttimer);
        return -1;
    };
    
    bouncertwo = al_create_bitmap(BOUNCERTWO_W, BOUNCERTWO_H); // creates the bitmap image (bouncer)
    if(!bouncertwo){
        printf("Error with al_create_bitmap[bouncer two]\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(bouncer);
        al_destroy_bitmap(obstacle);
        al_destroy_timer(fpscounttimer);
        return -1;
    };
    
    al_init_font_addon();
    
    al_init_ttf_addon();
    
    font_basictitlefont = al_load_ttf_font("fonts/Roboto-Italic.ttf", FONT_SIZE, 0);
    if(!font_basictitlefont){
        printf("Error with al_load_ttf_font[font_basictitlefont]\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(bouncer);
        al_destroy_bitmap(obstacle);
        al_destroy_timer(fpscounttimer);
        al_destroy_bitmap(bouncertwo);
        return -1;
    }
    
    font = al_load_ttf_font("fonts/Roboto-Italic.ttf", FONT_SIZE, 0);
    if(!font){
        printf("Error with al_load_ttf_font[font]\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(bouncer);
        al_destroy_bitmap(obstacle);
        al_destroy_timer(fpscounttimer);
        al_destroy_bitmap(bouncertwo);
        al_destroy_font(font_basictitlefont);
        return -1;
    }
    
    al_init_image_addon();
    
    if(!al_install_keyboard()){
        printf("Error with al_init_keyboard\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(bouncer);
        al_destroy_bitmap(obstacle);
        al_destroy_timer(fpscounttimer);
        al_destroy_bitmap(bouncertwo);
        al_destroy_font(font_basictitlefont);
        al_destroy_font(font);
        return -1;
    }
    
    if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
 
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
 
   sample = al_load_sample("sounds/throne_rokus.wav");
   if (!sample){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }
   
   sound_on = al_load_bitmap("images/sound_on.png");
   sound_off = al_load_bitmap("images/sound_off.png");
    
    
    
    // set event sources
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(fpscounttimer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    ALLEGRO_SAMPLE_INSTANCE* instance = al_create_sample_instance(sample);
    al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
    
    al_start_timer(timer); // start timer
    al_start_timer(fpscounttimer);
    
    bool switchcolor = false;
    
    bool inspeakericon = false;
    
    while(!doexit){ // main animation loop 
        
        ALLEGRO_EVENT ev; // creates a place to store the currecnt event
        al_wait_for_event(event_queue, &ev); // sets a place to stop until an event is present

        if(ev.timer.source == timer){
            
            if(key[UPKEY]){
                int i;
                for(i = 0; i < 3; i++) {
                    obstacle_color[i] = 0;
                    bouncer_color[i] = 0;
                    font_color[i] = 0;
                    font_basictitlefont_color[i] = 255;
                    background_color[i] = 255;
                    bouncertwo_color[i] = 255;
                }
                switchcolor = true;
            } else if(key[DOWNKEY]) {
                int i;
                for(i = 0; i < 3; i++) {
                    obstacle_color[i] = 255;
                    bouncer_color[i] = 255;
                    font_color[i] = 255;
                    font_basictitlefont_color[i] = 0;
                    background_color[i] = 0;
                    bouncertwo_color[i] = 0;
                }
                switchcolor = false;
            } else if(key[LEFTKEY]) {
                
            } else if(key[RIGHTKEY]) {
                
            }
            
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[UPKEY] = true;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[DOWNKEY] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[LEFTKEY] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[RIGHTKEY] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[UPKEY] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[DOWNKEY] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[LEFTKEY] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[RIGHTKEY] = false;
               break;
            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
         }
      }
        else if(ev.timer.source == fpscounttimer) {
            fpscount = fpstimer;
            if(fpstimer > 800 || fpstimer < 60) {
                font_color[0] = 255;
                font_color[1] = 0;
                font_color[2] = 0;
            } else {
                if(switchcolor == false){
                    font_color[0] = 255;
                    font_color[1] = 255;
                    font_color[2] = 255;
                } else {
                    font_color[0] = 0;
                    font_color[1] = 0;
                    font_color[2] = 0;
                }
                
            }
            fpstimer = 0;
        } 
        
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } 
        
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            // check if mouse is over the right hand side of the program
            if(ev.mouse.x > obstacle_width) /* || ev.mouse.y < obstacle_y - (BOUNCER_H / 2)*/ {
                bouncer_x = ev.mouse.x;
                bouncer_y = ev.mouse.y - (BOUNCER_H / 2);
                
                bouncertwo_y = ev.mouse.y - (BOUNCERTWO_H);
                bouncertwo_x = obstacle_width - BOUNCERTWO_W;
            } else { // if the mouse is in the obstacle
                if(ev.mouse.x <= obstacle_width && ev.mouse.x > obstacle_width - BOUNCERTWO_W) {
                    bouncertwo_x = obstacle_width - BOUNCERTWO_W;
                } else {
                bouncer_y = ev.mouse.y - (BOUNCER_H / 2);
                bouncer_x = obstacle_width;
                
                bouncertwo_x = ev.mouse.x;
                bouncertwo_y = ev.mouse.y - (BOUNCERTWO_H);
                }
            }
            if(ev.mouse.x > sound_on_x &&
                ev.mouse.x < sound_on_x + 32 &&
                ev.mouse.y < sound_on_y + 32 &&
                ev.mouse.y > sound_on_y
            ){
                inspeakericon = true;

            } else{
                inspeakericon = false;
            }
        } 
        
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { // use for printing debug things
            if(inspeakericon){
            if(is_sound_on){
                is_sound_on = false;
            } else {
                is_sound_on = true;
            }
            }
            
        } 
        
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_set_target_bitmap(bouncer);
            al_clear_to_color(al_map_rgb(bouncer_color[0], bouncer_color[1], bouncer_color[2])); 
            al_set_target_bitmap(bouncertwo);
            al_clear_to_color(al_map_rgb(bouncertwo_color[0], bouncertwo_color[1], bouncertwo_color[2]));
            al_set_target_bitmap(obstacle);
            al_clear_to_color(al_map_rgb(obstacle_color[0], obstacle_color[1], obstacle_color[2])); 
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(background_color[0], background_color[2], background_color[2]));
            al_draw_bitmap(obstacle, obstacle_x, obstacle_y, 0);
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            al_draw_bitmap(bouncertwo, bouncertwo_x, bouncertwo_y + (BOUNCERTWO_H/2), 0);
            char string[10];
            sprintf(string, "%d", fpscount);
            al_draw_text(font, al_map_rgb(font_color[0], font_color[1], font_color[2]), SCREEN_W - 20, 20, ALLEGRO_ALIGN_RIGHT, string);
            al_draw_text(font_basictitlefont, al_map_rgb(font_basictitlefont_color[0], font_basictitlefont_color[1], font_basictitlefont_color[2]), 10, SCREEN_H - 20, ALLEGRO_ALIGN_LEFT, "Copyright of Oliver Kenny 2015");
            if(is_sound_on){
                al_draw_bitmap(sound_on, sound_on_x, sound_on_y, 0);
                al_set_sample_instance_playing(instance, true); // play sample
            } else {
                al_draw_bitmap(sound_off, sound_off_x, sound_off_y, 0);
                al_set_sample_instance_playing(instance, false);
            }
            al_hide_mouse_cursor(display);
            al_flip_display();
            
        }
        fpstimer++;
        if(fpstimer>1000) { // Safe net to check for overly high frame reload rate (system crash)
            printf("System Overload. [Frame barrier exceded]\n"); 
            break;
        }
    }
    
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_bitmap(bouncer);
    al_destroy_bitmap(obstacle);
    al_destroy_bitmap(bouncertwo);
    al_destroy_timer(fpscounttimer);
    al_destroy_font(font);
    al_destroy_font(font_basictitlefont);
    al_destroy_sample(sample);
    al_destroy_bitmap(sound_off);
    al_destroy_bitmap(sound_on);
    
    return 0;
}
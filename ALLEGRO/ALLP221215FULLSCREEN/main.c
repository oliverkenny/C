// Oliver Kenny
// Fullscreen mode
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0 allegro_primitives-5.0 allegro_image-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char *argv[]) {

    ALLEGRO_DISPLAY         *display = NULL;
    ALLEGRO_DISPLAY_MODE     disp_data; // stores 4 different peices of info in a struct (only using .height and .width)
    
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    
    al_get_display_mode(0, &disp_data); // first function sets the display mode by using the data from disp_data and returns the amount of display options the monitor has
    
    al_set_new_display_flags(ALLEGRO_FULLSCREEN); // sets the display mode for the OS to fullscreen [doesnt show a menu bar at the top in this case]
    
    display = al_create_display(disp_data.width, disp_data.height);
    al_clear_to_color(al_map_rgb(66, 158, 15));
    
    al_flip_display();
    
    al_rest(10.0);
    
    al_destroy_display(display);
    
    return 0;
}
// Oliver Kenny
// Bitmap image
// Compile with: gcc main.c -o main `pkg-config --libs allegro-5.0 allegro_image-5.0`
// Possible addons "allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

const int DISPLAY_W = 500;
const int DISPLAY_H = 400;
const int IMAGE_W = 200;
const int IMAGE_H = 200;

int main(int argc, char *argv[]) {
    
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *image = NULL;
    
    if(!al_init()){
        printf("Error 1\n");
        return -1;
    }
    
    if(!al_init_image_addon()){
        printf("Error 3\n");
        return -1;
    }
    
    display = al_create_display(500, 400);
    if(!display){
        printf("Error 2\n");
        return -1;
    }
    
    image = al_load_bitmap("image.png");
    if(!image){
        printf("Error 4\n");
        al_destroy_display(display);
        return -1;
    }
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(image, (DISPLAY_W / 2) - (IMAGE_W / 2), (DISPLAY_H / 2) - (IMAGE_H / 2), 0);
    
    al_flip_display();
    al_rest(5);
    
    al_destroy_display(display);
    al_destroy_bitmap(image);
    
    return 0;
}
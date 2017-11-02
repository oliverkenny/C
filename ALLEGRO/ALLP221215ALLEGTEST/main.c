// Oliver Kenny
// First Allegro 5 test
// Compile with: "gcc <*file>.c -o <*file> `pkg-config --libs allegro-5.0` [*replace this with the name of the file for example 'main.c']"

#include <stdio.h>
#include <allegro5/allegro.h>

int main (){
    
    int result, x = 500, y = 400;
    ALLEGRO_DISPLAY *display = NULL; // set the display pointer to NULL also creates two image buffers. One to display and the other to draw to
    
    if (!al_init()) // checks for a correct initialisation of allegro
        printf("Init failed.\n");
    
    if (display = al_create_display(x, y)) // assigns a display and size to the display buffer
        ;
    else
        printf("Display failed.\n");
    
    al_clear_to_color(al_map_rgb(0, 0, 0)); // clear buffer and set to color to rgb value // will return a ALLEGRO_COLOR structure
    
    al_flip_display(); // flips the buffers from the current display buffer to the draw buffer [draw buffer gets drawn to by the code]
    
    al_rest(10.0); // takes a floating point integer and holds(pauses) the display until the allocated time has passed
    
    al_destroy_display(display); // this frees the memory and in turn destroys the display. Should be called on program shutdown
    
    return 0;
}
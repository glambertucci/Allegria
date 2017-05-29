#ifndef _struct_
#define _struct_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>

typedef struct
{
    float position_x;
    float position_y;
    int lenght_x;
    int lenght_y;
    bool led_on;
    bool led_enabled;
    ALLEGRO_BITMAP * bitmap;
    
} element;


#endif
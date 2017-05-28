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

typedef struct
{
    element b_0;
    element b_1;
    element b_2;
    element b_3;
    element b_4;
    element b_5;
    element b_6;
    element b_7;
    element b_on;
    element b_off;
    element b_blink;
    
} block;

#endif
#include <allegro5/display.h>
#include <stdio.h>

#include "init.h"
#include "struct.h"


void init_coord (element * elemento ,bool led_on ,bool led_enabled,ALLEGRO_BITMAP * bitmap)
{
    static int counter1 = 0;
    static int counter2 = 0;
    
    elemento->led_enabled = led_enabled;
    
    if (elemento->led_enabled)
    {
        elemento->position_x = SQUARE_X(counter1); 
        elemento->position_y = SCREEN_H * (0.25);
        elemento->lenght_x= LARGO_X;
        elemento->lenght_y= LARGO_Y;
        ++counter1;
    }
    else if (!(elemento->led_enabled))
    {
        elemento->position_x = RECTANGLE_X(counter2); 
        elemento->position_y = SCREEN_H * (0.75);
        elemento->lenght_x= LARGO_RECT_X;
        elemento->lenght_y= LARGO_RECT_Y;
        ++counter2;
    }
    elemento->led_on = led_on;
    elemento->bitmap = bitmap;
  
}

void init_screen (void * buttons, void * screen,ALLEGRO_BITMAP * led_on,ALLEGRO_BITMAP * button, const char * color_screen, int elementos)
{
    ALLEGRO_DISPLAY * display = screen;
    element * elemento = buttons;
    int contador;
    
    for ( contador = 0 ; contador < elementos; ++contador)
    {
        if ((elemento + contador)->led_enabled)
        {
            al_draw_bitmap(led_on, (elemento + contador)->position_x,(elemento + contador)->position_y,0);

        }
        else if (!(elemento + contador)->led_enabled)
        {
        al_draw_bitmap((elemento + contador)->bitmap, (elemento + contador)->position_x,(elemento + contador)->position_y,0);
    
        }
    }
    
    al_flip_display();
    
}
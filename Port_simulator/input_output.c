#include <stdio.h>					//librerias estandar que utilizan todas las
#include <unistd.h>					// funciones
#include "input_output.h"
//#include "validation.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include "define.h"


void print_display (element * elemento, ALLEGRO_DISPLAY * display,ALLEGRO_BITMAP * led_on, ALLEGRO_BITMAP * led_off, int elementos)
{
    int counter;
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_color_name("black"));
    
    for (counter = 0 ; counter < elementos ; ++counter)
    {      
        if ((elemento + counter)->led_enabled)
        {
            if ( ( (elemento + counter)->led_on) )
            {
                al_draw_bitmap(led_on,(elemento + counter)->position_x,(elemento + counter)->position_y,0);
  
            }
            else if (! ( (elemento + counter)->led_on ) )
            {
                al_draw_bitmap(led_off,(elemento + counter)->position_x,(elemento + counter)->position_y,0);
            }
        }
        else if (! ( (elemento + counter)->led_enabled))
        {
           al_draw_bitmap((elemento + counter)->bitmap,(elemento + counter)->position_x,(elemento + counter)->position_y,0);
        }

    }

    al_flip_display();
  
}

bool click_button(int mouse_x, int mouse_y, int button_x, int button_y , int lenght_x, int lenght_y )
{
    bool valid = false; // Se fija si conciden las coordenadas del mouse con las de un boton
    if ( (mouse_x > button_x) && (mouse_x < ( button_x + lenght_x) ))
    {
        if ((mouse_y > button_y) && (mouse_y < ( button_y + lenght_y) ))
        {
            valid = true;
        }
    }
    return valid;
}

int button_pressed (int mouse_x, int mouse_y, element * pointer, int elements)
{
    int counter;
    bool valid = false;
    
    for (counter = 0 ; !valid && (counter < (elements+1)) ; ++counter) // Se fija si se toco a algun boton
    {
        valid = click_button(mouse_x,mouse_y,(pointer + counter)->position_x,(pointer + counter)->position_y, (pointer + counter)->lenght_x, (pointer + counter)->lenght_y);
    }
    
    if (counter == elements + 1)   // Si no esta en la lista, es por que no toca a ningun boton
    {
        counter = -1;
    }
    else
    {
        --counter;
    }
    
    return counter;
}


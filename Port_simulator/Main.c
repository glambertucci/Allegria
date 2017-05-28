/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TP_B.c
 * Author: lucas
 *
 * Created on May 27, 2017, 12:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include "define.h"
#include "operations.h"
#include "struct.h"
#include "init.h"
#include "input_output.h"



#define FPS (60.0)

#define B_NOT (-1)
#define B_0 (0)
#define B_1 (1)
#define B_2 (2)
#define B_3 (3)
#define B_4 (4)
#define B_5 (5)
#define B_6 (6)
#define B_7 (7)
#define B_ON (8)
#define B_OFF (9)
#define B_BLINK (10)


int main(void) 
{
    block all_buttons;
    
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_line = NULL;
    ALLEGRO_TIMER * timer = NULL;
 
    init_coord (&(all_buttons.b_0),true,true,NULL);     // declaro los bitmaps y los
    init_coord (&(all_buttons.b_1),true,true,NULL);     // estados de los leds
    init_coord (&(all_buttons.b_2),true,true,NULL);
    init_coord (&(all_buttons.b_3),true,true,NULL);
    init_coord (&(all_buttons.b_4),true,true,NULL);
    init_coord (&(all_buttons.b_5),true,true,NULL);
    init_coord (&(all_buttons.b_6),true,true,NULL);
    init_coord (&(all_buttons.b_7),true,true,NULL);
    init_coord (&(all_buttons.b_on),false,false,NULL);   
    init_coord (&(all_buttons.b_off),false,false,NULL);
    init_coord (&(all_buttons.b_blink),false,false,NULL);

            
    bool close_display = false;
    bool mouse = false;
    bool keyboard = false;
    bool redraw = false;
    
    int mouse_x = 0;
    int mouse_y = 0;
    
    char key_pressed = 0;
    
    int button = B_NOT;
    
        //Inicio allegro
    if (!al_init())
    {
        fprintf(stderr,"Allegro not initialized");
        return -1;
    }
        // Inicio el teclado
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Keyboard not installed");
        return -1;
    }
        // Inicio el mouse
    if (!al_install_mouse())
    {
        fprintf(stderr,"Mouse not installed");
        return -1;
    }
        // Inicio las primitivas (aunque no las use)
    if ( !al_init_primitives_addon() )
    {
        fprintf(stderr,"Primitives not initialized");
        return -1;
    }
        //Creo el display
    if (!(display = al_create_display(SCREEN_W,SCREEN_H)))
    {
        fprintf(stderr,"display not created");
        return -1;
    }
        //Creo la cola de eventos
    if (!(event_line=al_create_event_queue()))
    {
        fprintf(stderr,"Event queue not created");
        al_destroy_display(display);
        return -1;
    }
        // creo el timer
    if (!(timer =al_create_timer(1/FPS)))
    {
        fprintf(stderr,"Timer not created");
        al_destroy_display(display);
        al_destroy_event_queue(event_line);
        return -1;
    }
        // Inicializo los bitmaps
    if (!(all_buttons.b_0.bitmap = al_create_bitmap(all_buttons.b_0.lenght_x, all_buttons.b_0.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        return -1;
    }
    
    if (!(all_buttons.b_1.bitmap = al_create_bitmap(all_buttons.b_1.lenght_x, all_buttons.b_1.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        return -1;
    }

    if (!(all_buttons.b_2.bitmap = al_create_bitmap(all_buttons.b_2.lenght_x, all_buttons.b_2.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        return -1;
    }

    if (!(all_buttons.b_3.bitmap = al_create_bitmap(all_buttons.b_3.lenght_x, all_buttons.b_3.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        return -1;
    }

    if (!(all_buttons.b_4.bitmap = al_create_bitmap(all_buttons.b_4.lenght_x, all_buttons.b_4.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        return -1;
    }

    if (!(all_buttons.b_5.bitmap = al_create_bitmap(all_buttons.b_5.lenght_x, all_buttons.b_5.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        al_destroy_bitmap(all_buttons.b_4.bitmap);
        return -1;
    }

    if (!(all_buttons.b_6.bitmap = al_create_bitmap(all_buttons.b_6.lenght_x, all_buttons.b_6.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        al_destroy_bitmap(all_buttons.b_4.bitmap);
        al_destroy_bitmap(all_buttons.b_5.bitmap);
        return -1;
    }

    if (!(all_buttons.b_7.bitmap = al_create_bitmap(all_buttons.b_7.lenght_x, all_buttons.b_7.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        al_destroy_bitmap(all_buttons.b_4.bitmap);
        al_destroy_bitmap(all_buttons.b_5.bitmap);
        al_destroy_bitmap(all_buttons.b_6.bitmap);
        return -1;
    }

    if (!(all_buttons.b_on.bitmap = al_create_bitmap(all_buttons.b_on.lenght_x, all_buttons.b_on.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        al_destroy_bitmap(all_buttons.b_4.bitmap);
        al_destroy_bitmap(all_buttons.b_5.bitmap);
        al_destroy_bitmap(all_buttons.b_6.bitmap);
        al_destroy_bitmap(all_buttons.b_7.bitmap);
        return -1;
    }

    if (!(all_buttons.b_off.bitmap = al_create_bitmap(all_buttons.b_off.lenght_x, all_buttons.b_off.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        al_destroy_bitmap(all_buttons.b_4.bitmap);
        al_destroy_bitmap(all_buttons.b_5.bitmap);
        al_destroy_bitmap(all_buttons.b_6.bitmap);
        al_destroy_bitmap(all_buttons.b_7.bitmap);
        al_destroy_bitmap(all_buttons.b_on.bitmap);
        return -1;
    }

    if (!(all_buttons.b_blink.bitmap = al_create_bitmap(all_buttons.b_blink.lenght_x, all_buttons.b_blink.lenght_y)))
    {
        fprintf(stderr, "Bitmap not created");
        al_destroy_bitmap(all_buttons.b_0.bitmap);
        al_destroy_bitmap(all_buttons.b_1.bitmap);
        al_destroy_bitmap(all_buttons.b_2.bitmap);
        al_destroy_bitmap(all_buttons.b_3.bitmap);
        al_destroy_bitmap(all_buttons.b_4.bitmap);
        al_destroy_bitmap(all_buttons.b_5.bitmap);
        al_destroy_bitmap(all_buttons.b_6.bitmap);
        al_destroy_bitmap(all_buttons.b_7.bitmap);
        al_destroy_bitmap(all_buttons.b_on.bitmap);
        al_destroy_bitmap(all_buttons.b_off.bitmap);
        return -1;
    }

    al_register_event_source(event_line,al_get_display_event_source(display)); // Registro los eventos de
    al_register_event_source(event_line,al_get_keyboard_event_source());       // la pantalla, el timer
    al_register_event_source(event_line,al_get_mouse_event_source());          // el mouse y el teclado
    al_register_event_source(event_line,al_get_timer_event_source(timer));

    init_screen ((void *) &(all_buttons.b_0), (void *) display,"green","hotpink","white", 11); // Imprimo en pantalla los bitmaps en sus estados iniciales
    al_start_timer(timer);                              // Empiezo el timer
    
    while (!close_display)
    {
        ALLEGRO_EVENT event;
        
        if(al_get_next_event(event_line,&event))
        {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                close_display = true;                       // Cierro la pantalla
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) 
            {
                mouse_x = event.mouse.x;                    // Detecto cuando hace click 
                mouse_y = event.mouse.y;                    //  y paso las coordenadas
                mouse = true;
            }
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN)      // Falta configurarlo tambien
            {
                key_pressed = event.keyboard.keycode;
                keyboard = true;
            }
            else if (event.type == ALLEGRO_EVENT_TIMER)
            {
                if (mouse && !keyboard)
                {
                    mouse = false;
                    button = button_pressed (mouse_x, mouse_y, &(all_buttons.b_0), 11); // me fijo que boton aprete
                    redraw = true;
                }
                else if (!mouse && keyboard)
                {
                   // FALTA AGREGAR LOS CONTROLES DE TECLADO 
                }
            }
        }
        if ( redraw && al_event_queue_is_empty(event_line))
        {
            redraw = false;
            switch (button)
            {
                case B_0 : bit_switch (&(all_buttons.b_0));     //prendo o apago el led
                break;
                case B_1 : bit_switch (&(all_buttons.b_1));
                break;
                case B_2 : bit_switch (&(all_buttons.b_2));
                break;
                case B_3 : bit_switch (&(all_buttons.b_3));
                break;
                case B_4 : bit_switch (&(all_buttons.b_4));
                break;
                case B_5 : bit_switch (&(all_buttons.b_5));
                break;
                case B_6 : bit_switch (&(all_buttons.b_6));
                break;
                case B_7 : bit_switch (&(all_buttons.b_7));
                break;
                case B_ON : set_all(&(all_buttons.b_0), 8) ;    //prendo todos los leds
                break;
                case B_OFF : clr_all (&(all_buttons.b_0),8);    //apago todos los leds
                break;
                case B_BLINK :blink_all(&(all_buttons.b_0),display,8, 10); // parpadean los leds
                break;
                case B_NOT :break;
            }
            print_display(&(all_buttons.b_0),display, 11);
        }
        
    }
    
    al_destroy_display(display);                    // Destuyo todo lo que cree
    al_destroy_event_queue(event_line);
    al_destroy_timer(timer);
    al_destroy_bitmap(all_buttons.b_0.bitmap);
    al_destroy_bitmap(all_buttons.b_1.bitmap);
    al_destroy_bitmap(all_buttons.b_2.bitmap);
    al_destroy_bitmap(all_buttons.b_3.bitmap);
    al_destroy_bitmap(all_buttons.b_4.bitmap);
    al_destroy_bitmap(all_buttons.b_5.bitmap);
    al_destroy_bitmap(all_buttons.b_6.bitmap);
    al_destroy_bitmap(all_buttons.b_7.bitmap);
    al_destroy_bitmap(all_buttons.b_on.bitmap);
    al_destroy_bitmap(all_buttons.b_off.bitmap);
    al_destroy_bitmap(all_buttons.b_blink.bitmap);
    return (0);
}





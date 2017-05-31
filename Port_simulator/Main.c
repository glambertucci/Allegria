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
#include <allegro5/allegro_image.h>
#include "define.h"
#include "operations.h"
#include "struct.h"
#include "init.h"
#include "input_output.h"
#include "secret.h"



#define FPS (60.0)				// Se puede pasar al archivo define.h

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
    element all_buttons [11];
    
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_BITMAP * display_background = NULL;
    ALLEGRO_EVENT_QUEUE * event_line = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_BITMAP * led_on = NULL;
    ALLEGRO_BITMAP * led_off = NULL;
    ALLEGRO_BITMAP * button_flash = NULL;
    ALLEGRO_BITMAP * button_charge = NULL;
    ALLEGRO_BITMAP * button_discharge = NULL;
    ALLEGRO_BITMAP * background1 = NULL;
    ALLEGRO_BITMAP * background2 = NULL;
    ALLEGRO_SAMPLE * led_on_music = NULL;
    ALLEGRO_SAMPLE * back_music = NULL;

 
    init_coord (&(all_buttons[B_0]),true,true,NULL);     // declaro los bitmaps y los
    init_coord (&(all_buttons[B_1]),true,true,NULL);     // estados de los leds
    init_coord (&(all_buttons[B_2]),true,true,NULL);
    init_coord (&(all_buttons[B_3]),true,true,NULL);
    init_coord (&(all_buttons[B_4]),true,true,NULL);
    init_coord (&(all_buttons[B_5]),true,true,NULL);
    init_coord (&(all_buttons[B_6]),true,true,NULL);
    init_coord (&(all_buttons[B_7]),true,true,NULL);
    init_coord (&(all_buttons[B_ON]),false,false,NULL);   
    init_coord (&(all_buttons[B_OFF]),false,false,NULL);
    init_coord (&(all_buttons[B_BLINK]),false,false,NULL);
   
       
     
            
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
    
    if(!al_init_image_addon()) 
    { 
	fprintf(stderr, "failed to initialize image addon !\n");
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
    if (!al_install_audio())					//
    {								
        fprintf(stderr,"Audio not installed");
        return -1;  
    }
    
    if (!al_init_acodec_addon())				// 
    {											
        fprintf(stderr,"Codec not initialized");
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
    if (!(led_on = al_load_bitmap("open_poke.png")) )
    {
        fprintf(stderr, "Image not loaded");
        return -1;
    }
    
    if (!(led_off = al_load_bitmap("close_poke.png")))
    {
        al_destroy_bitmap(led_off);
        fprintf(stderr, "Image not loaded");
        return -1;
    }
    
    if (!(button_flash = al_load_bitmap("flash.png")))
    {
        al_destroy_bitmap(led_off);
        fprintf(stderr, "Image not loaded");
        return -1;
    }
    
    if (!(button_charge = al_load_bitmap("charge.png")))
    {
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(button_flash);
        fprintf(stderr, "Image not loaded");
        return -1;
    }
    
    if (!(button_discharge = al_load_bitmap("discharge.png")))
    {
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(button_flash);
        al_destroy_bitmap(button_charge);
        fprintf(stderr, "Image not loaded");
        return -1;
    }
    all_buttons[B_BLINK].bitmap = button_flash;
    all_buttons[B_ON].bitmap = button_charge;
    all_buttons[B_OFF].bitmap = button_discharge;
    
    if (!(background1 = al_load_bitmap("mapa.png")))
    {
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(button_flash);
        al_destroy_bitmap(button_charge);
        al_destroy_bitmap(button_discharge);
        fprintf(stderr, "Image not loaded");
        return -1;
    }
    
    if (!(background2 = al_load_bitmap("mapa2.png")))
    {
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(button_flash);
        al_destroy_bitmap(button_charge);
        al_destroy_bitmap(button_discharge);
        al_destroy_bitmap(background1);

        fprintf(stderr, "Image not loaded");
        return -1;
    }
    if(!(al_reserve_samples(2)))
    {
        fprintf(stderr,"Samples not reserved");
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(button_flash);
        al_destroy_bitmap(button_charge);
        al_destroy_bitmap(button_discharge);
        al_destroy_bitmap(background1);
        al_destroy_bitmap(background2);
        al_uninstall_audio();
        return -1;
    }
    led_on_music = al_load_sample( "ison.wav" );
    if (!led_on_music)
    {
        if (al_filename_exists("ison.wav"))
            fprintf(stderr,"Existe\n");
        fprintf(stderr,"Sample1 not loaded");
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(button_flash);
        al_destroy_bitmap(button_charge);
        al_destroy_bitmap(button_discharge);
        al_destroy_bitmap(background1);
        al_destroy_bitmap(background2);
        al_uninstall_audio();
        return -1;
    }

    back_music = al_load_sample( "back_music.wav" );
    if (!back_music)
    {
        fprintf(stderr,"back not loaded");
        if (al_filename_exists("back.ogg"))
            fprintf(stderr,"Existe\n");
            al_destroy_bitmap(led_off);
            al_destroy_bitmap(button_flash);
            al_destroy_bitmap(button_charge);
            al_destroy_bitmap(button_discharge);
            al_destroy_bitmap(background1);
            al_destroy_bitmap(background2);
            al_uninstall_audio();

        return -1;
    }

    al_register_event_source(event_line,al_get_display_event_source(display)); // Registro los eventos de
    al_register_event_source(event_line,al_get_keyboard_event_source());       // la pantalla, el timer
    al_register_event_source(event_line,al_get_mouse_event_source());          // el mouse y el teclado
    al_register_event_source(event_line,al_get_timer_event_source(timer));

    display_background = background1;
    
    init_screen ((void *) &(all_buttons[B_0]), (void *) display_background,led_on,led_off, 11); // Imprimo en pantalla los bitmaps en sus estados iniciales
    al_start_timer(timer);                              // Empiezo el timer
    
    al_play_sample(back_music,0.75,0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL); 

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
                    button = button_pressed (mouse_x, mouse_y, &(all_buttons[B_0]), 11); // me fijo que boton aprete
                    redraw = true;
                }
                else if (!mouse && keyboard)
                {
                    keyboard = false;
                    switch (key_pressed)
                    {
                        case ALLEGRO_KEY_B : button = B_BLINK; break;
                        case ALLEGRO_KEY_C : button = B_OFF; break;
                        case ALLEGRO_KEY_S : button = B_ON ; break;
                        case ALLEGRO_KEY_F1 : display_background =background1; 
				    redraw = true;
				    button = B_NOT; 
				    break;
                        case ALLEGRO_KEY_F2 :display_background =background2;
				    redraw = true;
				    button = B_NOT; 
				    break;
                        case ALLEGRO_KEY_PAD_0:
                        case ALLEGRO_KEY_0 : button = B_0; break;
                        case ALLEGRO_KEY_PAD_1:
                        case ALLEGRO_KEY_1 : button = B_1 ; break;
                        case ALLEGRO_KEY_PAD_2:
                        case ALLEGRO_KEY_2 : button = B_2 ; break;
                        case ALLEGRO_KEY_PAD_3:
                        case ALLEGRO_KEY_3 : button = B_3 ; break;
                        case ALLEGRO_KEY_PAD_4:
                        case ALLEGRO_KEY_4 : button = B_4 ; break;
                        case ALLEGRO_KEY_PAD_5:
                        case ALLEGRO_KEY_5 : button = B_5 ; break;
                        case ALLEGRO_KEY_PAD_6:
                        case ALLEGRO_KEY_6 : button = B_6 ; break;
                        case ALLEGRO_KEY_PAD_7:
                        case ALLEGRO_KEY_7 : button = B_7 ; break;
                        case ALLEGRO_KEY_ESCAPE : close_display = true;break;
                        case ALLEGRO_KEY_SPACE : 
				    if (secret_game() == (-1))
                        	    {
                                        fprintf(stderr, "fatal error");
                            		return -1;
                        	    }
                        	    al_set_target_bitmap(al_get_backbuffer(display));
                        default : button = B_NOT; break;
                    }
                    if ( (button != B_NOT) && (close_display != true ) )
                    {
                        redraw = true;
                    }
                }
            }
        }

//        led_on_music = al_load_sample( "ison.wav" );
        
	if ( redraw && al_event_queue_is_empty(event_line))
        {
            redraw = false;
            switch (button)
            {
                case B_0 : bit_switch (&(all_buttons[B_0]));     //prendo o apago el led
                           if ( (&(all_buttons[B_0]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;
                case B_1 : bit_switch (&(all_buttons[B_1]));
                           if ( (&(all_buttons[B_1]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_2 : bit_switch (&(all_buttons[B_2]));
                           if ( (&(all_buttons[B_2]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_3 : bit_switch (&(all_buttons[B_3]));
                           if ( (&(all_buttons[B_3]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_4 : bit_switch (&(all_buttons[B_4]));
                           if ( (&(all_buttons[B_4]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_5 : bit_switch (&(all_buttons[B_5]));
                           if ( (&(all_buttons[B_5]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_6 : bit_switch (&(all_buttons[B_6]));
                           if ( (&(all_buttons[B_6]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_7 : bit_switch (&(all_buttons[B_7]));
                           if ( (&(all_buttons[B_7]))->led_on)
                           al_play_sample(led_on_music,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
                case B_ON : set_all(&(all_buttons[B_0]), 8) ;    //prendo todos los leds
                break;
                case B_OFF : clr_all (&(all_buttons[B_0]),8);    //apago todos los leds
                break;
                case B_BLINK :blink_all(&(all_buttons[B_0]),(void *) display_background,led_on,led_off,8, 10); // parpadean los leds
                break;
                case B_NOT :break;
            }
            print_display(&(all_buttons[B_0]),(void *) display_background,led_on,led_off, 11);
        }
        
    }
    
    al_stop_samples();  


    al_destroy_display(display);                    // Destuyo todo lo que cree
    al_destroy_event_queue(event_line);
    al_destroy_timer(timer);
    al_destroy_bitmap(led_on);
    al_destroy_bitmap(led_off);
    al_destroy_bitmap(all_buttons[B_ON].bitmap);
    al_destroy_bitmap(all_buttons[B_OFF].bitmap);
    al_destroy_bitmap(all_buttons[B_BLINK].bitmap);
    al_destroy_bitmap(background1);
    al_destroy_bitmap(background2);
    al_destroy_sample(led_on_music);
    al_destroy_sample(back_music);
    al_uninstall_audio();
    
    return (0);
}





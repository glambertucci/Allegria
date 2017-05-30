/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: lucas
 *
 * Created on May 25, 2017, 3:26 PM
 */

#include "secret.h"

#define SCREEN_H 700  // Todos estos define tienen que ir con parentesis, y se tiene que poner a la amyoria en secret.h
#define SCREEN_W 750

#define FPS 60.0
#define CUADRADO_SIZE 10
#define CUADRADON_SIZE 100
#define MOVESPEED 3.0
#define MOVESPEEDN 2.0
#define EXTRA_SPACE 20

#define KEY_UP (0)			// estos no
#define KEY_DOWN (1)
#define KEY_LEFT (2)
#define KEY_RIGHT (3)
#define KEY_W (4)
#define KEY_S (5)
#define KEY_A (6)
#define KEY_D (7)
 

int secret_game(void) 
{
    ALLEGRO_DISPLAY * display2 = NULL;
    ALLEGRO_BITMAP * cuadrado_b = NULL;
    ALLEGRO_BITMAP * cuadrado_n = NULL;
    ALLEGRO_FONT * looser_text = NULL;
    ALLEGRO_FONT * small_text = NULL;
    ALLEGRO_TIMER * timer2 = NULL;
    ALLEGRO_EVENT_QUEUE * event_line2 = NULL;
    ALLEGRO_SAMPLE * perdiste = NULL;
    ALLEGRO_SAMPLE * cancion = NULL;
    
    bool key_pressed [8] = {false, false, false, false,false, false, false, false};
    bool close_screen = false;
    bool redraw = false;
    bool lost = false;
    int time = 0;
    
    float cuadrado_b_x = 0;
    float cuadrado_b_y = 0;
    float cuadrado_n_x = SCREEN_W - CUADRADON_SIZE;
    float cuadrado_n_y = SCREEN_H - CUADRADON_SIZE;
    
    unsigned char color = 33;

    al_init_font_addon();
    al_init_ttf_addon();

    if (! (cuadrado_b = al_create_bitmap(CUADRADO_SIZE,CUADRADO_SIZE)))
    {
        fprintf(stderr,"Bitmap not Initialized");
        return -1;
    }
    
    if ( ! (cuadrado_n = al_create_bitmap(CUADRADON_SIZE,CUADRADON_SIZE)))
    {
        fprintf(stderr,"Bitmap not Initialized");
        al_destroy_bitmap(cuadrado_b);
    }
    
    if (! (timer2 = al_create_timer(1/FPS)))
    {
        fprintf(stderr, "Timer not initialized");
        al_destroy_bitmap(cuadrado_n);
        al_destroy_bitmap(cuadrado_b);
        return -1;
    }
    
    if ( ! (display2 = al_create_display(SCREEN_W,SCREEN_H)))
    {
        fprintf(stderr,"Display not initialized");
        al_destroy_bitmap(cuadrado_n);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_timer(timer2);
        return -1;
    }
    
    if (! (event_line2 = al_create_event_queue()))
    {
        fprintf(stderr,"Event Queue not initialized");
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        return -1;
    }
    
    if (!(looser_text = al_load_ttf_font("poke_font.ttf",32,0)))
    {
        fprintf(stderr,"Font not initialized");
        al_destroy_event_queue(event_line2);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        return -1;  
    }
    
    if (!(al_init_primitives_addon()))
    {
        fprintf(stderr,"Primitives not initialized");
        al_destroy_event_queue(event_line2);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        return -1; 
    }

    if(!(al_reserve_samples(2)))
    {
        fprintf(stderr,"Samples not reserved");
        al_destroy_event_queue(event_line2);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        al_uninstall_audio();
        return -1;
    }
    
    perdiste = al_load_sample( "a.wav" );
    if (!perdiste)
    {
        if (al_filename_exists("a.wav"))
            fprintf(stderr,"Existe\n");
        fprintf(stderr,"Sample1 not loaded");
        al_destroy_event_queue(event_line2);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        al_uninstall_audio();
        return -1;
    }
    cancion = al_load_sample( "b.wav" );
    if (!cancion)
    {
        fprintf(stderr,"Sample2 not loaded");
        if (al_filename_exists("b.ogg"))
            fprintf(stderr,"Existe\n");
        al_destroy_sample(perdiste);
        al_destroy_event_queue(event_line2);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        al_uninstall_audio();
        return -1;
    } 
    
    if (!(small_text = al_load_ttf_font("poke_font.ttf",20,0)))
    {
        fprintf(stderr,"Font not initialized");
        al_destroy_sample(perdiste);
        al_destroy_sample(cancion);
        al_destroy_event_queue(event_line2);
        al_destroy_bitmap(cuadrado_b);
        al_destroy_bitmap(cuadrado_n);
        al_destroy_timer(timer2);
        al_destroy_display(display2);
        al_uninstall_audio();
        return -1;  
    }                                                           // Termina de inicializar
    
    al_set_target_bitmap(cuadrado_b);                       // elijo al cuadrado blanco y lo pinto de blanco
    al_clear_to_color(al_map_rgb(255,255,255));
    al_set_target_bitmap(cuadrado_n);                       //Elijo al cuadrado negro y lo pinto de negro
    al_clear_to_color(al_map_rgb(0,0,0));
    al_set_target_bitmap(al_get_backbuffer(display2));       // Vualvo a seleccionar al display
    
    al_register_event_source(event_line2,al_get_display_event_source(display2));  //Activo para que se detecten
    al_register_event_source(event_line2,al_get_timer_event_source(timer2));      //eventos del timer, pantalla 
    al_register_event_source(event_line2,al_get_keyboard_event_source());        // y teclado
    
    al_clear_to_color(al_map_rgb(color,color,color));                           //seteo el mapa en gris
                                                        // inicia el timer
    al_flip_display();
    
    al_draw_text(looser_text,al_color_name("white"),SCREEN_W/2,SCREEN_H/4,ALLEGRO_ALIGN_CENTER,"Square");
    al_draw_text(small_text,al_color_name("white"),SCREEN_W/2,SCREEN_H/2,ALLEGRO_ALIGN_CENTER,"El blanco se mueve con las flechas,");
    al_draw_text(small_text,al_color_name("white"),SCREEN_W/2,(SCREEN_H/2) + 20,ALLEGRO_ALIGN_CENTER,"escapa del negro!");   
    al_flip_display();
    al_rest(4.0);
    al_start_timer(timer2);  
    
    al_play_sample(cancion,1.0,0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);            //Pone la musica principal del juego
    
    while(!close_screen)
    {
        ALLEGRO_EVENT event;
        
        if (al_get_next_event(event_line2,&event))
        {
            if (event.type == ALLEGRO_EVENT_TIMER)          // controla a los cuadrados
            {
                if ( ( key_pressed[KEY_UP] ) && ( cuadrado_b_y >= MOVESPEED ) && ( cuadrado_b_y <= ( SCREEN_H - MOVESPEED) ) )
                    cuadrado_b_y -= MOVESPEED;
                if ( ( key_pressed[KEY_DOWN] ) && ( cuadrado_b_y <= (SCREEN_H - CUADRADO_SIZE - MOVESPEED) ) )
                    cuadrado_b_y += MOVESPEED;
                if ( ( key_pressed[KEY_LEFT] ) && ( cuadrado_b_x >= MOVESPEED ) && ( cuadrado_b_x <= ( SCREEN_W - MOVESPEED) ) )
                    cuadrado_b_x -= MOVESPEED;
                if ( ( key_pressed[KEY_RIGHT] ) && ( cuadrado_b_x <= (SCREEN_W - CUADRADO_SIZE - MOVESPEED) ) )
                    cuadrado_b_x += MOVESPEED;
                
                if (( cuadrado_n_y + CUADRADON_SIZE/2 ) >= ( cuadrado_b_y + CUADRADO_SIZE/2 ) )
                    cuadrado_n_y -= MOVESPEEDN;
                if ( ( cuadrado_n_y + CUADRADON_SIZE/2 ) <= ( cuadrado_b_y + CUADRADO_SIZE/2 ) )
                    cuadrado_n_y += MOVESPEEDN;
                if ( ( cuadrado_n_x + CUADRADON_SIZE/2 ) >= ( cuadrado_b_x + CUADRADO_SIZE/2 ) )
                    cuadrado_n_x -= MOVESPEEDN;
                if ( ( cuadrado_n_x + CUADRADON_SIZE/2 ) <= ( cuadrado_b_x + CUADRADO_SIZE/2 ))
                    cuadrado_n_x += MOVESPEEDN;
                
                
                redraw = true;
            }
            
            else if ((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) )      //cierra el display
                close_screen = true;
            
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN)              //permite que los cuadrados
            {                                                           //cambien de posicion
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP : key_pressed[KEY_UP] = true ; break ;
                    case ALLEGRO_KEY_DOWN : key_pressed[KEY_DOWN] = true ; break ;
                    case ALLEGRO_KEY_LEFT : key_pressed[KEY_LEFT] = true ; break ;
                    case ALLEGRO_KEY_RIGHT : key_pressed[KEY_RIGHT] = true ; break ;
                    case ALLEGRO_KEY_W : key_pressed[KEY_W] = true ; break ;
                    case ALLEGRO_KEY_S : key_pressed[KEY_S] = true ; break ;
                    case ALLEGRO_KEY_A : key_pressed[KEY_A] = true ; break ;
                    case ALLEGRO_KEY_D : key_pressed[KEY_D] = true ; break ;
                }
            }
            
            else if (event.type == ALLEGRO_EVENT_KEY_UP)                // Evita que los cuadrados se
            {                                                           //sigan moviendo infinitamente
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP : key_pressed[KEY_UP] = false ; break ;
                    case ALLEGRO_KEY_DOWN : key_pressed[KEY_DOWN] = false ; break ;
                    case ALLEGRO_KEY_LEFT : key_pressed[KEY_LEFT] = false ; break ;
                    case ALLEGRO_KEY_RIGHT : key_pressed[KEY_RIGHT] = false ; break ;
                    case ALLEGRO_KEY_W : key_pressed[KEY_W] = false ; break ;
                    case ALLEGRO_KEY_S : key_pressed[KEY_S] = false ; break ;
                    case ALLEGRO_KEY_A : key_pressed[KEY_A] = false ; break ;
                    case ALLEGRO_KEY_D : key_pressed[KEY_D] = false ; break ;
                }
            }
        }
        
        if (redraw  && al_event_queue_is_empty(event_line2))               //Reimprime el display con las posiciones
        {                                                                 // actualizadas de los cuadrados 
            redraw = false;
            al_clear_to_color(al_map_rgb(color,color,color));
            al_draw_bitmap(cuadrado_b,cuadrado_b_x,cuadrado_b_y,0);
            al_draw_bitmap(cuadrado_n,cuadrado_n_x,cuadrado_n_y,0);

            al_flip_display();
            
            if ( (cuadrado_b_x >= cuadrado_n_x) && (cuadrado_b_x <= ( cuadrado_n_x + CUADRADON_SIZE - CUADRADO_SIZE)) &&(cuadrado_b_y >= cuadrado_n_y) && (cuadrado_b_y <= ( cuadrado_n_y + CUADRADON_SIZE - CUADRADO_SIZE) ) )
            {
               al_clear_to_color(al_map_rgb(color,color,color));              //Indica que el ucadrado negro ha alcanzado
               al_flip_display();                                             // al blanco y termina el juego
               lost = true;
               al_destroy_sample(cancion);
               al_play_sample(perdiste,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            }
        }
        
        if (lost)                   //muestra la pantalla funal, antes de cerrar el display
        {
            al_draw_rectangle(cuadrado_n_x - EXTRA_SPACE , cuadrado_n_y - EXTRA_SPACE , cuadrado_n_x + EXTRA_SPACE + CUADRADON_SIZE , cuadrado_n_y + EXTRA_SPACE + CUADRADON_SIZE , al_color_name("red") , 5.0 );
            al_draw_text(looser_text,al_color_name("white"),SCREEN_W/2,SCREEN_H/4,ALLEGRO_ALIGN_CENTER,"Perdiste");
            al_flip_display();
            al_rest(4.0);
            close_screen = true;
        }
        
        
    }
    
    
    
    
    
    al_destroy_bitmap(cuadrado_b);          //destruye todo
    al_destroy_bitmap(cuadrado_n);
    al_destroy_display(display2);
    al_destroy_event_queue(event_line2);
    al_destroy_timer(timer2);
    al_destroy_sample(perdiste);
    
    

    return 0;
}


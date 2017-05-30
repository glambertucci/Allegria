#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_

#include "struct.h"			// librerias no estandares para que las funciones compilen y corran
		// sin problemas.

#define LEDON '*'			// representan a los caracteres que se imprimen en terminal, si el led
#define LEDOFF '-'			// esta encendido o apagado.

#ifdef _WIN32
   #error "This program is only targeted at Linux systems"
#endif

bool click_button(int mouse_x, int mouse_y, int button_x, int button_y , int lenght_x, int lenght_y );

int button_pressed (int mouse_x, int mouse_y, element * pointer, int elements);
void print_display (element * elemento, void * background,ALLEGRO_BITMAP * led_on, ALLEGRO_BITMAP * led_off, int elementos);


 #endif 
 // _INPUT_OUTPUT_H_
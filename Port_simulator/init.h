#ifndef _validation_
#define _validation_

#include "struct.h"
#include "define.h"
void init_screen (void * buttons, void * screen,const char * color_led_on,const char * color_button,const char * color_screen, int elementos);

void init_coord (element * elemento ,bool led_on, bool led_enabled ,ALLEGRO_BITMAP * bitmap);
#endif
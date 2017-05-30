#ifndef _validation_
#define _validation_

#include "struct.h"
#include "define.h"
void init_screen (void * buttons, void * background,ALLEGRO_BITMAP * led_on,ALLEGRO_BITMAP * button, int elementos);

void init_coord (element * elemento ,bool led_on, bool led_enabled ,ALLEGRO_BITMAP * bitmap);
#endif
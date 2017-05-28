#ifndef _operations_
#define _operations_

#include "struct.h"
#include "input_output.h"
#include <stdio.h>


void clr_all( element * elemento, int elementos);
void set_all( element * elemento, int elementos);
void blink_all(element * elemento,ALLEGRO_DISPLAY * display,int elementos, int repetir);
void bit_switch (element * elemento);

#endif

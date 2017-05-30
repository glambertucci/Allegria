#include "operations.h"

void blink_all(element * elemento, void * background,ALLEGRO_BITMAP * led_on, ALLEGRO_BITMAP * led_off,int elementos, int repetir)
{
    int counter, count_repeat;
    
    for (count_repeat = 0; count_repeat < repetir ; ++count_repeat)
    {
    
        for (counter = 0 ;counter < elementos; ++ counter)
        {
            bit_switch(elemento + counter);
        }
        print_display(elemento,(void *) background,led_on,led_off, 11);
        al_rest(0.3);
    }
}
void set_all( element * elemento, int elementos)
{
    int counter;
    
    for (counter = 0 ;counter < elementos; ++ counter)
    {
        (elemento + counter)->led_on = true;
    }
}

void clr_all( element * elemento, int elementos)
{
    int counter;
    
    for (counter = 0 ;counter < elementos; ++ counter)
    {
        (elemento + counter)->led_on = false;
    }
}




void bit_switch (element * elemento)
{
    if (elemento->led_on)
    {
        elemento->led_on = false;
    }
    else if (!elemento->led_on)
    {
        elemento->led_on = true;
    }
}
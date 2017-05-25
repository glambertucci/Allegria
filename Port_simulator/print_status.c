#include "print_status.h"

void print_status (void * point, char puerto)
{
	b1_t * point_struct = (b1_t *) point;		//Castea el puntero a void a un bitfield

	putchar( ( point_struct->b7 ? LEDON : LEDOFF ) );	//Imprime el bit mas significativo
	putchar( ( point_struct->b6 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b5 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b4 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b3 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b2 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b1 ? LEDON : LEDOFF ) );			
	putchar( ( point_struct->b0 ? LEDON : LEDOFF ) );	//Imprime el bit menos significativo
	
	if (puerto != 'd')
	{
		putchar('\n');
	}

}


void toggle_print (void * pointer2, int repeat)
{
	int counter_enter, counter_repeat;
	b16_t * pointer = pointer2;
	b1_t * point;
	char array[9] = "11111111";
	void (*funcion) (char puerto, int bit, void * pointer2);

	funcion = bittoggle;

	if (repeat % 2 != 0)
	{
		++repeat;
	}

	for ( counter_repeat = 0 ; counter_repeat < repeat ; ++counter_repeat)
	{ 

		for (counter_enter = 0 ; counter_enter < 50 ; ++counter_enter)
		{
			putchar('\n');
		}

		point = &(pointer->porta.eight_reg);

		printf("\nEstado actual puerto A: ");
		print_status( point , PORTA1 );

		point = &(pointer->portb.eight_reg)	;

		printf("\nEstado actual puerto B: ");
		print_status( point , PORTB1 );			

		sleep(1);

		mask_8bits (PORTA1, array, pointer, funcion);
		mask_8bits (PORTB1, array, pointer, funcion);
	}
}
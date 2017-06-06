#include "operations.h"
#include "Led_print.h"

#define INVERT(a) (7-a)		// Permite invertir el contador para poder ver la posicion del
#define ON (1)
#define OFF (0)


void bitset (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg); break;
		case 'b' : port = &(pointer->portb.eight_reg); break;
	}
	switch (bit)
	{
		case 0 : port->b0 = ON; break;						//bit 0
		case 1 : port->b1 = ON; set_led (LED_1, ON); break;
		case 2 : port->b2 = ON; set_led (LED_2, ON); break;
		case 3 : port->b3 = ON; set_led (LED_3, ON); break;
		case 4 : port->b4 = ON; set_led (LED_4, ON); break;
		case 5 : port->b5 = ON; set_led (LED_5, ON); break;
		case 6 : port->b6 = ON; set_led (LED_6, ON); break;
		case 7 : port->b7 = ON; set_led (LED_7, ON); break;			//bit 7
	}
}

void bitclr (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg); break;
		case 'b' : port = &(pointer->portb.eight_reg); break;
	}

	switch (bit)
	{
		case 0 : port->b0 = OFF; break;						//bit 0
		case 1 : port->b1 = OFF; set_led (LED_1, OFF); break;
		case 2 : port->b2 = OFF; set_led (LED_2, OFF); break;
		case 3 : port->b3 = OFF; set_led (LED_3, OFF); break;
		case 4 : port->b4 = OFF; set_led (LED_4, OFF); break;
		case 5 : port->b5 = OFF; set_led (LED_5, OFF); break;
		case 6 : port->b6 = OFF; set_led (LED_6, OFF); break;
		case 7 : port->b7 = OFF; set_led (LED_7, OFF); break;						//bit 7
	}
}

int bitget (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;
	int result;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg);
		case 'b' : port = &(pointer->portb.eight_reg);
	}

	switch (bit)
	{
		case 0 : result = port->b0 ; break;					//bit 0
		case 1 : result = port->b1 ; break;
		case 2 : result = port->b2 ; break;
		case 3 : result = port->b3 ; break;
		case 4 : result = port->b4 ; break;
		case 5 : result = port->b5 ; break;
		case 6 : result = port->b6 ; break;
		case 7 : result = port->b7 ; break;					//bit 7
	}

	return result;
}

void bittoggle (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg); break;
		case 'b' : port = &(pointer->portb.eight_reg); break;
	}

	switch (bit)
	{
		case 1: if (port->b1) 
			{				
				port->b1 = OFF;
				set_led (LED_1, OFF);
			} 
			else
			{
				port->b1 = ON;
				set_led (LED_1, ON); 
			}			
			break;
		case 2: if (port->b2) 
			{
				port->b2 = OFF;
				set_led (LED_2, OFF);
			}
			else
			{
				port->b2 = ON;
				set_led (LED_2, ON);
			}
			break;
		case 3: if (port->b3)
			{
				port->b3 = OFF;
				set_led (LED_3, OFF);
			}
			else
			{
				port->b3 = ON;
				set_led (LED_3, ON);
			}
			break;
		case 4: if (port->b4)
			{
				port->b4 = OFF;
				set_led (LED_4, OFF);
			}
			else
			{
				port->b4 = ON;
				set_led (LED_4, ON);
			}
			break;
		case 5: if (port->b5)
			{
				port->b5 = OFF;
				set_led (LED_5, OFF);
			}
			else
			{
				port->b5 = ON;
				set_led (LED_5, ON);
			}
			break;
		case 6: if (port->b6)
			{
				port->b6 = OFF;
				set_led (LED_6, OFF);
			}
			else
			{
				port->b6 = ON;
				set_led (LED_6, ON);
			}
			break;
		case 7: if (port->b7)
			{
				port->b7 = OFF;
				set_led (LED_7, OFF);
			}
			else 
			{
				port->b7 = ON;
				set_led (LED_7, ON);
			}
			break;
	}
}


void mask_8bits (char puerto, char * array, void * pointer2, void (*funcion) (char puerto, int bit, void * pointer2))
{
	int counter;

	void * pointer;
	b16_t * aa = pointer2;

	for (counter = 0 ;  ( *(array + counter) != 0 ) || (counter < 8) ; ++counter)		
	{
		if ( *(array + counter) == '1')
		{
			(*funcion ) (puerto,INVERT(counter),pointer2);
		}
	}
}


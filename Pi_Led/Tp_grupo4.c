
#include <stdio.h>
#include "operations.h"
#include "validation.h"
#include "input_output.h"
#include "struct.h"
#include "Led_print.h"


#define PORTA ('a')

#define PORT_LENGTH (7)

#define INITSTATE ('0')
#define LED_1 ('4')
#define LED_2 ("17")
#define LED_3 ("27")
#define LED_4 ("22")
#define LED_5 ("18")
#define LED_6 ("23")
#define LED_7 ("24")



#define NOERRORS (0)
#define ERROR_MASK (1)


int main (void)
{
	char option = 'p', port = PORTA;
	int option_validation = TRUE, status,move_screen;	

	void (*funcion) (char puerto , int bit , void * pointer2); 
	port_16_t portd;
	portd.full_reg= 0;
	
	char * mask_array;
	char short_array[9] = {"00000000"};
	int max_bits, i ,mask_error = NOERRORS;

	//Inicialización
	
	set_led (LED_1, INITSTATE);		
	set_led (LED_2, INITSTATE);
	set_led (LED_3, INITSTATE);
	set_led (LED_4, INITSTATE);
	set_led (LED_5, INITSTATE);
	set_led (LED_6, INITSTATE);
	set_led (LED_7, INITSTATE);


	while ( ( option != ENDOFPROGAM ) && ( port != ENDOFPROGAM ))
	{
            
            for (move_screen = 30; move_screen >=0 ; --move_screen)
                putchar('\n');
                
		printf("\nPor favor ingrese la operación que desee realizar:\n");
		printf("los numeros del 0 al 7 para prender o apagar los leds\n");	
		printf("%c para ingresar una máscara para el encendido de leds\n", MASKON);
		printf("%c para ingresar una máscara para el apagado de leds\n", MASKOFF);
		printf("%c para ingresar una máscara para invertir el estado de los led\n", MASKTOGGLE);
		printf("%c para que los led parpadeen\n", INTERMITENCE);
		printf("%c para apagar todos los led\n", ALLOFF);
		printf("%c para encender todos los led\n", ALLON);
		printf("la tecla ESC para finalizar el programa\n");

		do						//SELECCION DEL USUARIO PARA OPERACION
		{		
			option = get_char();
			
			option_validation = op_valid(option);

			if (option_validation == FALSE)
			{
				printf("\nHa ingresado una opción incorrecta, reingrese por favor: \n");
			}
		} while (option_validation == FALSE);

		switch (option)						//SE ASIGNAN LOS PUNTEROS A FUNCION PARA OPERAR CON MASCARAS
		{
			case MASKON: funcion = &bitset; break;
			case MASKOFF: funcion = &bitclr; break;
			case MASKTOGGLE: funcion = &bittoggle; break;
		}
		
		if ( (option >='0') && (option <='7') )	// para modificaciones de bits 
		{
                    pointer = &(portd.half_reg);
                    bittoggle (port , (int) option - '0', pointer); 
		}

		else if ( (option == MASKON)||(option == MASKOFF)||(option == MASKTOGGLE) ) 	// para modificaciones con mascaras
		{
				mask_array = short_array;
				max_bits = PORT_LENGTH;
				pointer = &(portd.half_reg);

			printf ("\nIngrese la máscara con la que desee operar\n");
			do 
			{
				get_mask (mask_array , max_bits );
				mask_error = check_mask (mask_array, max_bits);

				if (mask_error == ERROR_MASK)
				{
					printf("\nHa ingresado de forma incorrecta la máscara, solo puede ingresar ceros y unos\n");
				}
			} while (mask_error == ERROR_MASK);	

			mask_8bits (port , mask_array, pointer, funcion ) ;

			for ( i = 0 ; i < max_bits-1 ; ++i)
			{
				*(mask_array + i) = '0';
			}

			*(mask_array + i) = 0;
		}

		else if (option == ALLON)
		{
			portd.full_reg= 0xffff;
		}
		else if (option == ALLOFF)
		{
			portd.full_reg= 0;
		}
		else if (option == INTERMITENCE)
		{

			toggle_print (&(portd.half_reg.porta), 6);
		}
                

	}	
	return 0;
}


#include <stdio.h>
#include "operations.h"
#include "validation.h"
#include "input_output.h"
#include "struct.h"
#include "Led_print.h"


#define PORTA ('a')
#define NOERRORS (1)

#define PORT_LENGTH (8)
#define INITSTATE ('0')


int main (void)
{
	char option = 'p', port = PORTA, bit;
	int option_validation = TRUE, status,move_screen;	
	void * pointer; 	

	void (*funcion) (char puerto , int bit , void * pointer2); 
	port_16_t portd;
	portd.full_reg= INITSTATE - 0;
	
	char * mask_array;
	char short_array[9] = {"00000000"};
        char all_one[8] = "1111111";
	int max_bits, i ,mask_error = NOERRORS, errorbit = NOERRORS;

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
                      
		printf("\nPor favor ingrese la operación que desee realizar:\n");
		printf("los numeros del 0 al 7 para prender o apagar los leds\n");	
		printf("%c para ingresar una máscara para el encendido de leds\n", MASKON);
		printf("%c para ingresar una máscara para el apagado de leds\n", MASKOFF);
		printf("%c para ingresar una máscara para invertir el estado de los led\n", MASKTOGGLE);
		printf("%c para que los led parpadeen\n", INTERMITENCE);
		printf("%c para apagar todos los led\n", ALLOFF);
		printf("%c para encender todos los led\n", ALLON);
		printf("%c para saber el estado de un led\n", BITGET);
		printf("la tecla ESC para finalizar el programa\n");

		do						//SELECCION DEL USUARIO PARA OPERACION
		{		
			option = get_char();
			option_validation = op_valid(option);

			if (!option_validation)
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
                    bittoggle (port , (int) (option - '0') , pointer); 
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

				if (!mask_error)
				{
					printf("\nHa ingresado de forma incorrecta la máscara, solo puede ingresar ceros y unos\n");
				}
			} while (!mask_error);	

			mask_bits (port , mask_array, pointer, funcion ) ;

			for ( i = 0 ; i < max_bits-1 ; ++i)
			{
				*(mask_array + i) = '0';
			}

			*(mask_array + i) = 0;
		}

		else if ((option == ALLON) || (option == ALLOFF))
		{
                    switch (option)
                    {
                        case ALLOFF : funcion = bitclr;all_leds(ON); break;
                        case ALLON : funcion = bitset;all_leds(OFF); break;
                    }
                    
                    mask_bits(PORTA,all_one,&(portd.half_reg), funcion);

		}

		else if (option == INTERMITENCE)
		{
			toggle_print (&(portd.half_reg.porta), 6);
		}
		putchar('\n');
		putchar('\n');
	}	
	return 0;
}

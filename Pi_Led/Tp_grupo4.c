
#include <stdio.h>
#include "operations.h"
#include "validation.h"
#include "input_output.h"
#include "struct.h"



#define PORTA ('a')




#define NOERRORS (0)
#define ERROR_MASK (1)


int main (void)
{
	char option = 'p', port = PORTA;
	int option_validation = TRUE, status,move_screen;	

	void (*funcion) (char puerto , int bit , void * pointer2);
	void * pointer; 
	port_16_t portd;
	portd.full_reg= 0;
	
	char * mask_array;
	char short_array[9] = {"00000000"};
	int max_bits, i ,mask_error = NOERRORS;



	while ( ( option != ENDOFPROGAM ) && ( port != ENDOFPROGAM ))
	{
            
            for (move_screen = 30; move_screen >=0 ; --move_screen)
                putchar('\n');
            
                pointer = &(portd.half_reg.porta.eight_reg);
		printf("\nEstado actual puerto A: ");
		print_status(pointer , PORTA);
		printf("\n");
                
		printf("\nPor favor ingrese la operación que desee realizar:\n");
		printf("los numeros del 0 al 7 para prender o apagar los leds\n");	
		printf("%c para ingresar una máscara para el encendido de leds\n", MASKON);
		printf("%c para ingresar una máscara para el apagado de leds\n", MASKOFF);
		printf("%c para ingresar una máscara para invertir el estado de los led\n", MASKTOGGLE);
		printf("%c para que los led parpadeen\n", INTERMITENCE);
		printf("%c para apagar todos los led\n", ALLOFF);
		printf("%c para encender todos los led\n", ALLON);
		printf("la tecla ESC para finalizar el programa\n");

		do
		{																			//SELECCION DEL USUARIO PARA OPERACION
			option = get_char();
			
			option_validation = op_valid(option);

			if (option_validation == FALSE)
			{
				printf("\nHa ingresado una opción incorrecta, reingrese por favor: \n");
			}
		} while (option_validation == FALSE);

		switch (option)											//SE ASIGNAN LOS PUNTEROS A FUNCION PARA OPERAR CON MASCARAS
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
				max_bits = 8;

				pointer = &(portd.half_reg);

			printf ("\nIngrese la máscara con la que desee operar\n");
			do 
			{
				get_mask (mask_array , max_bits );
				for (i=0 ; i < max_bits ; ++i)
				{
					if (i == 0)
					{
						mask_error = NOERRORS;
					}
					if ((*(mask_array + i) != '0') && (*(mask_array + i) != '1'))
					{
						mask_error = ERROR_MASK;

					}
				}
				if (mask_error == ERROR_MASK)
				{
					printf("\nHa ingresado de forma incorrecta la máscara, solo puede ingresar ceros y unos\n");
				}
			} while (mask_error == ERROR_MASK);	

			mask_8bits (port , mask_array, pointer, funcion ) ;

			for ( i = 0 ; i < max_bits -1 ; ++i)
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
	
	
	pointer = &(portd.half_reg.porta.eight_reg);
	printf("\nEstado final puerto A: ");
	print_status(pointer , PORTA);
	printf("\n");
		

	return 0;
}

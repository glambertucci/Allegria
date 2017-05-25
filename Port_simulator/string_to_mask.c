#include "string_to_mask.h"


// Estas funcion hace potencias.
static int power (int power, int base);

int string_to_mask (void * string)
{
	int counter, counter2, position;
	int decimal_mask = 0;

	char * array = (char *) string;

	for (counter = INICIO ; *(array + counter) != TERMINADOR ; ++counter)				// Este for se encarga de contar cuantos elementos tiene
	{																					// el string
	}

	position = counter -1;																// pongo la ultima posicion de arreglo

	for (counter2 = INICIO ; counter2 < counter ; ++counter2,--position)				// Este for se fija en que posiciones de memoria hay un uno 
	{																					// y transforma el string a una mascara en decimal
		if ( *(array + position ) == UNO)
		{
			decimal_mask = decimal_mask + power(counter2, DOS);
		}
	}

	return decimal_mask;
}


static int power (int power, int base)									
{
	int result = 1;

	while (power > 0)
	{
		result = result * base;
		--power;
	}

	return result;
}
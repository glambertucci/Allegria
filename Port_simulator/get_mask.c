
#include "get_mask.h"

static int LetterCounter ( char * point, char terminador_a, char terminador_b);	

void get_mask (char * string_return, int max_bits)
{
	int counter, counter_return, leave = 0, tecla, lenght;

	char string_short [ 9 ]  = {1,1,1,1,1,1,1,1,0} ; 
	char string_long [ 17 ]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}; 

	char * string; 

	switch (max_bits)
	{
		case 8 : string = string_short ; break ;
		case 16 : string = string_long ; break ;
	}

	for (counter = 0 ; ( *(string + counter) != 0 ) && ( leave == 0) ; ++ counter)	// copia lo que se ingresa a un string temporal
	{
		if (  ( (tecla = getchar()) != '\n' ) )
		{ 	
			*(string + counter) = tecla;
		}
		else
		{
			leave = 1;
		}
	}

	lenght = LetterCounter(string , 1,0);

	for (counter_return = ( max_bits - lenght ) , counter = 0 ;  ( *(string + counter) != 0 ) ; ++counter_return, ++ counter)
	{ 	
		if ( *(string + counter) == '1' )
		{ 
			*(string_return + counter_return) = '1';
		}
	}

}

static int LetterCounter ( char * point, char terminador_a, char terminador_b)								
{
	int letter;
	
	for ( letter = 0 ; ( *(point + letter) != terminador_a ) && ( *(point + letter) != terminador_b ) ; ++letter )
	{	
	}
	return letter;
}

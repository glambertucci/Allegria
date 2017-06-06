#include "validation.h"
#include "Led_print.h"

int op_valid (char input)
{
	int value;
	switch(input)
	{
            case '0': 
            case '1': 
            case '2': 
            case '3': 
            case '4': 
            case '5': 
            case '6': 
            case '7': 
            case 'c': 
            case 's': 
            case 'b': 
            case 'n': 
            case 'f': 
            case 't':
	    case 'g':
            case 27 : 
                value = TRUE; 
                break;
		default : value = FALSE; break;
	}
	return value; 
}

int check_mask (char * mask_array, int max_bits)
{
	int i, mask;
	for (i=0 ; i < max_bits ; ++i)
	{
		if (i == 0)
		{
			mask = TRUE;
		}
		if ((*(mask_array + i) != '0') && (*(mask_array + i) != '1'))
		{
			mask = FALSE;
		}
	}
	return mask;
}

int bit_validation(char bit)
{
	int in_put = TRUE;
	if ( (bit >= '0') && (bit <= '6') )
	{
		in_put = TRUE;
	}
	else
	{
		in_put = FALSE;
	}
	return in_put;
}

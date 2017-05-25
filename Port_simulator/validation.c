#include "validation.h"


int op_valid (char input)
{
	int value;
	switch(input)
	{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case 'c': case 's': case 'b': case 'f': case 27: value = TRUE; break;
		default : value = FALSE; break;
	}
	return value; 
}
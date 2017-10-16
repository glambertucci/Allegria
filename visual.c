#include "general.h"
void welcome_print(void)
{

	printf("Welcome to Calculator \n");
	printf("---------------------\n");
	printf("Type [number][op][number] (without the brackets)\n");
	printf("General commands:\n");
	printf("c2 => enable only letter operators \n");
	printf("c1 => enable only symbol operators \n");
	printf("c0 => enable all operators \n");
	printf("e  => terminate the program \n");

	printf("Basic commands : Add(+),Substract(-),Multiply(*),Divide(/) \n"); 
	printf("Logic commands : AND(&),OR(|),XOR(^)\n");				
}

void read_line (char *str,int *sz)
{ 
	int i = 0;
	char aux_var;
	*sz = 0;
	while((aux_var = getchar()) != '\n'){
		if (i < MAX_STR_SZ){ // we can't store them, there is not enough memory
			str[i] = aux_var;
		}
		i++;
	}
	str[i] = '\0';
	
	*sz = i; // we return total characters inserted no matter we did't add extra ones
}
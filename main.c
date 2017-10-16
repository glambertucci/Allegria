#include <stdio.h>
#include <math.h> // See overview
#include "logic.h"
#include "visual.h"
#include "general.h"
/////////////////////////////////
//// TP8 - ADVANCED POINTERS ////
//// ----------------------- ////
//// ==> MESTANZA, Joaquin   ////
//// ==> NOWIK, Ariel        ////
//// ==> REGUEIRA, Marcelo   ////////////////////////////////////////////
//// --------------------------------------------------------------- ////
//// The following code is a calculator that allows the user to      ////
//// make four (4) basic operations (Add, Substract, Multiply,       ////
//// Divide) and three (3) logic operations (AND, OR, XOR).          ////
//// To call de operations, the user can make use of the first       ////
//// letter of the operation (both uppercase and lowercase letters   ////
//// are valid) or the corresponding symbol. 						 ////
//// The user also can change the mode of calling operations, there  ////
//// are three (3) cases: Only Symbols, Only Letters, Both letters   ////
//// and symbols. 													 ////
//// The instructions are displayed at the beigining of the program. ////
//// NOTE: math.h was only used for Not-A-Number case, because if    ////
//// the result = NAN, the condition (result != result) its true,    ////
//// and its is necessary for a simple code flow; if not, the        ////
//// general operation of the program needs to be changed.           ////
//// --------------------------------------------------------------- ////
/////////////////////////////////////////////////////////////////////////




//// GLOBAL VARIABLES ////
//// ---------------- ////
int cnt_op; // which mode is enabled
int operators[ASCII]; // ASCII -> index
float (*actions[MAX_OP])(float, float);

int enabled_chars[ASCII]; // enabled characters codes

int letters[letters_sz] = 
{'a','b','c','d','e',
 'f','g','h','i','j',
 'k','l','m','n','o',
 'p','q','r','s','t',
 'u','v','w','x','y','z',
 'A','B','C','D','E',
 'F','G','H','I','J',
 'K','L','M','N','O',
 'P','Q','R','S','T',
 'U','V','W','X','Y','Z'};
//// ---------------- ////

int main()
{
	set(operators,ASCII,ERR); // fill operators table with default ERR
	set_operations_symbol(ALL_ENABLED);

	cnt_op = 0;

	config_operations();

	welcome_print();

	int end = 0;
	
	while (!end){
		char input_line[MAX_STR_SZ];
		int sz;

		printf("==>");
		read_line(input_line,&sz); 
		
		char *ans;
		double n_ans;

		process_command(input_line,sz,&ans,&n_ans);

		if (ans[0] == 'e'){
			end = 1;
		}else{
			if (ans[0] == CHAR_CODE_SUCCESS){
				printf("%f \n",n_ans);
			}else{
				printf("%s \n",ans);
			}
		}
	}
}



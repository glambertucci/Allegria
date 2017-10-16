void set_operations_symbol(int mode);
//// set_operations_symbol: sets the array of valid chars.
//// to use at calling operations.
//// 	Input: mode (defines SYMBOL_MODE / LETTER_MODE / ALL_ENABLED)
////	Output: (none)
void config_operations(void);
//// config_operations: sets an array of pointers to functions, 
//// calling add_operation.
////	Input/Output: (none)
//// -------------- ////
void process_command(char *input,int sz,char **ans,double *n_ans);
//// process_command: calls read_command_operation for changing actual 
//// valid operators, or calls read_number_operation for doing operations.
////	Input: pointer to string with keyboard entry word, size of the word, double
////           pointer to answer char, pointer to double number (in case of doing an operation)
////	Output: (none)
void set(int arr[] , int n,int v); 
//// set: set all array values to input v.
////	Input: pointer to array, size of array, value to set
////	Output: (none)
void set_custom(int arr[], int indexes[],int ind_sz, int value);
//// set_custom: sets indexes[i] elements of arr with value, i >=0.
////	Input: array to set elements, array whose elements are the index of the
////		   elements of arr to modify, size of indexes array, value to set 
////		   in arr elements.
////	Output: (none) 
//// ------------------- ////
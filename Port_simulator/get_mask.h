#ifndef _get_mask
#define _get_mask

// get_mask : Esta funcion crea la mascara que ingresa el usuario
//
// - char * string : Es un puntero a un arreglo (de 9 0 17 elementos) de char QUE DEBE VENIR INICIALIZADO CON '0' 
// - int max_bits  : Es el numero maximo de bits de registro al que se le aplica la mascara (7 o 15)
void get_mask (char * string, int max_bits);

#include <stdio.h>



#endif
#ifndef _string_to_mask_
#define _string_to_mask_

// string_to_mask : Esta funcion transforma un string en una mascara. El string debe estar en binario.
//
// - void * string : Es el string a transformar.
int string_to_mask (void * string);

#define UNO '1'
#define DOS (2)
#define INICIO (0)
#define TERMINADOR (0)

#include <stdio.h>

#endif
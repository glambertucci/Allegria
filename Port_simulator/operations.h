#ifndef _operations_
#define _operations_

#include "struct.h"
#include "print_status.h"
#include <stdio.h>
#define INVERT(a) (7-a)		// Permite invertir el contador para poder ver la posicion del
#define ON (1)
#define OFF (0)


// funcion bitset : Esta funcion prende un bit de un registro
//
// - char puerto 	 : Indica que registro se debe modificar
// - int bit 		 : Indica que bit debe ser modificado (0-7)
// - b16_t * pointer : Es un puntero que apunta a estructura que contiene los puertos A y B
void bitset (char puerto, int bit, void * pointer2);

// funcion bitclr : Esta funcion apagar un bit de un registro
//
// - char puerto 	 : Indica que registro se debe modificar
// - int bit 		 : Indica que bit debe ser modificado (0-7)
// - b16_t * pointer : Es un puntero que apunta a estructura que contiene los puertos A y B
void bitclr (char puerto, int bit, void * pointer2);

// funcion bittoggle : Esta funcion invierte el estado de  un bit de un registro
//
// - char puerto 	 : Indica que registro se debe modificar
// - int bit 		 : Indica que bit debe ser modificado (0-7)
// - b16_t * pointer : Es un puntero que apunta a estructura que contiene los puertos A y B
void bittoggle (char puerto, int bit, void * pointer2);


int bitget (char puerto, int bit, void * pointer2);

//funcion mask_8bits : Realiza las operaciones de prender/apagar bits.

void mask_8bits (char puerto, char * array, void * pointer, void (*funcion) (char puerto, int bit, void * pointer2));


// funcion port_d_func : Realiza las funciones con el puerto D
void port_d_func (b16_t * pointer, int bit, void (*funcion) (char puerto, int bit, b16_t * pointer) );



#endif

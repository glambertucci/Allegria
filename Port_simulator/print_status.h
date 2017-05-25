#ifndef _print_status_
#define  _print_status_

#include "struct.h"
#include <stdio.h>
#include <unistd.h>
#include "operations.h"

#define PORTA1 'a'
#define PORTB1 'b'

// print_status : Esta funcion imprime bit a bit un registro de 8 bits
// - void * point : es un puntero a void que apunta a una estructura (bitfield) de 8 bits 
// - char puerto : Indica que puerto se va a imprimir

void print_status (void * point, char puerto);

// toggle_print : Es una funcion que hace parpadear a un puerto
// - void * point : Es un puntero que contiene al puerto a imprimir
// - int repeat : Indica cuantas veces se va a repetir

void toggle_print (void * pointer2, int repeat);

#define LEDON '*'
#define LEDOFF '-'





#endif



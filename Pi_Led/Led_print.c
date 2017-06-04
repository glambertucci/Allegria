/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Led_print.c
 * Author: lucas
 * 
 * Created on June 1, 2017, 7:03 PM
 */

#include "Led_print.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
void export(char * pin);
void output_set(char * pin);
void state_set(char * pin, char led_state);
void set_led ( void * pin, char led_state );
void print_led (char led, char led_state);


void print_led (char led, char led_state)
{
    char * real_pin;
    
    
    switch (led)
    {
	case B_1 : real_pin = "4" ;break;
	case B_2 : real_pin = "17" ;break;
	case B_3 : real_pin = "27" ;break;
	case B_4 : real_pin = "22" ;break;
	case B_5 : real_pin = "18" ;break;
	case B_6 : real_pin = "23" ;break;
	case B_7 : real_pin = "24" ;break;
    }
    
    set_led(real_pin,led_state);
}



void set_led ( void * pin, char led_state )
{
    export( (char *)pin);
    output_set((char *)pin);
    state_set((char *)pin,led_state);
}


void export(char * pin)
{
	FILE *handle_export;
	int nWritten;
	if ((handle_export =  fopen("/sys/class/gpio/export","w")) == NULL)
	{	
   	printf("Cannot open EXPORT File. Try again later.\n");
   	exit(1);
	}
	nWritten=fputs(pin,handle_export); 
	if (nWritten==-1)
	{
   		printf ("Cannot EXPORT PIN . Try again later.\n");
   		exit(1);
	}	
	else
    		printf("EXPORT File opened succesfully \n");
		
   fclose(handle_export);  // Be carefull do this for EACH pin !!!

}

void output_set(char * pin)
{
    FILE * handle_direction;
    int nWritten;

    char * part1 = "/sys/class/gpio/gpio";
    char * part3 = "/direction";
    char full_address [100];
	
    strcpy(full_address, part1 );
    strcat(full_address, pin);
    strcat(full_address, part3);
	
    if ((handle_direction = fopen(full_address,"w")) == NULL)
    {
	printf("Cannot open DIRECTION File");
	exit(1);
    }
// Set pin Direction
				
    if ((nWritten=fputs("out",handle_direction))==-1)
    {	
	printf("Cannot open DIRECTION pin. Try again later.\n");
	exit(1);
    }
    else
    {	
	printf("DIRECTION File for PIN opened succesfully\n");
    }
		
    fclose(handle_direction); // Be carefull do this for EACH pin !!!
}


void state_set(char * pin, char led_state)
{
    FILE * handle;

    char * part1 = "/sys/class/gpio/gpio";
    char * part3 = "/value";
    char full_address [100];
	
    strcpy(full_address, part1);
    strcat(full_address, pin);
    strcat(full_address, part3);

    if ((handle = fopen(full_address,"w")) == NULL)
    {
    	printf("Cannot open device. Try again later.\n");
    	exit(1);
    }
    else
    {
        printf("Device successfully opened\n");
    }

    if(fputc(led_state ,handle)==-1) // Set pin low
    {
	printf("Clr_Pin: Cannot write to file. Try again later.\n");
	exit(1);
    }
    else
	printf("Write to file %s successfully done.\n",full_address);

    fclose(handle);
}



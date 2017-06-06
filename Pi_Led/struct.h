#ifndef _struct_
#define _struct_

typedef struct 			// Un puerto de 8 bits visto bit a bit
{
	char b0 :1;
	char b1 :1;
	char b2 :1;
	char b3 :1;
	char b4 :1;
	char b5 :1;
	char b6 :1;
	char b7 :1;

} b1_t;


typedef union			// Union de las dos formas de ver a un registro de 8 bits
{
	char  full_reg;
	b1_t  eight_reg;

}port_8_t;

typedef struct 				// Un puerto de 16 bits visto de a 8 bits
{
	port_8_t portb ;
	port_8_t porta ;

} b16_t;

typedef union				// Union de las formas de mostrar un registro de 16 bits
{
	int full_reg :16;
	b16_t half_reg;

} port_16_t;

#define B_0 ('0')
#define B_1 ('1')
#define B_2 ('2')
#define B_3 ('3')
#define B_4 ('4')
#define B_5 ('5')
#define B_6 ('6')
#define B_7 ('7')
#define MASKON ('n')
#define MASKOFF ('f')
#define MASKTOGGLE ('t')
#define INTERMITENCE ('b')
#define ALLOFF ('c')
#define ALLON ('s')
#define BITGET ('g')
#define ENDOFPROGAM 27


#define LED_1 ("4")
#define LED_2 ("17")
#define LED_3 ("27")
#define LED_4 ("22")
#define LED_5 ("18")
#define LED_6 ("23")
#define LED_7 ("24")
#endif

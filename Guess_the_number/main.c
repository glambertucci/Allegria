#include <stdio.h>
#include <time.h>
#include <stdlib.h>



#define MAX_NUM 10
#define MAX_TIME 20
#define PI 3.14159265359
 
int main ()
{
	 
	//MANEJO DEL TIEMPO
	unsigned int x_seconds=0;   
	unsigned int x_milliseconds=0;
	unsigned int totaltime=0,time_in_secs=0;
        int time_left=0;
        // VARIABLES UTILES
        int safe_print=10;  //Asegura que no se imprima muchas veces el mensaje del tiempo
        char start_game;    //el getchar que perimte iniciar el juego
        //VARIABLES  DE JUEGO
        int win_number;     
        char guess;
        int end_game=1;
        
        
        //MENSAJES
        char* msg_welcome="Ingrese cualquier caracter para comenzar\nTendra";
        char *msg_welcome2="segundos para adivinar un numero entre los numeros 0 y";
        char * msg_welcome3="Una ves ingresado el numero presione enter";
        char* msg_time_left="Te quedan ";
        char *msg_wrong="Equivocado, intente nuevamente";
        char* msg_congrats="Felicitaciones, ha ganado";
        char* msg_lost="El tiempo termino, usted ha perdido";
        
        srand (time(NULL)*PI);
        
        win_number= rand()%MAX_NUM;
        
            printf("%s %d %s %d\n%s \n",msg_welcome, MAX_TIME , msg_welcome2, MAX_NUM,msg_welcome3);
            
            start_game=get_char();
                          
            clock_t x_startTime,x_countTime;
            
            time_in_secs=MAX_TIME; 
 
 
            x_startTime=clock();  // comienza reloj
            
            time_left=time_in_secs-x_seconds;   // inicio el tiempo restante

            while (((time_left>0)) && (guess!=win_number)) 
                {

                        x_countTime=clock();    //actualizo el timer
                        x_milliseconds=x_countTime-x_startTime;
                        x_seconds=(x_milliseconds/(CLOCKS_PER_SEC));

                        time_left=time_in_secs-x_seconds; 

                        if (!(time_left%1))
                        {
                            if (!(x_seconds==safe_print))
                            {
                            safe_print=x_seconds;
                            printf(" \n%s: %d s\n",msg_time_left, time_left);
                            }
                        }
                        if (kbhit())
                        {
                        guess = getchar(); 
                        guess-='0';
                        }
                       
                }
            if(guess==win_number)
            {
                printf("\n%s\n",msg_congrats);
            }
            else
            {
                printf( "\n%s\n",msg_lost);
            }
           end_game=0;
                
      
        
return 0;
}

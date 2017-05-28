#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "get_char.h"
#include "nonblock.h"

#define MAX_NUM 10
#define MAX_TIME 5
 
int main ()
{
	 
	 
	unsigned int x_seconds=0;
	unsigned int x_milliseconds=0;
	unsigned int totaltime=0,time_in_secs=0;
        int time_left=0;
        int caution=10;
        int win_number;
        char start_game;
        char guess;
        int end_game=1;
        char* msg_welcome="Ingrese cualquier caracter para comenzar\nTendra";
        char *msg_welcome2="segundos para adivinar un numero entre los numeros 0 y";
        char* msg_time_left="Te quedan ";
        char* msg_congrats="Felicitaciones, ha ganado";
        char* msg_lost="El tiempo termino, usted ha perdido";
        
        srand (time(NULL)*3.14);
        
        win_number= rand()%MAX_NUM;
        
            printf("%s %d %s %d \n",msg_welcome, MAX_TIME , msg_welcome2, MAX_NUM);
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
                            if (!(x_seconds==caution))
                            {
                                caution=x_seconds;
                            printf(" \n%s: %d s\n",msg_time_left, time_left);
                            }
                        }
                        guess = get_char();
                        guess-='0';

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
 //Intento dos
 /*#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#define TOTAL_TIME 999999999999999999
#define MAX_NUM 10
int main(void)
{
    int win_number;
    int wined=1;
    bool exit = false;
    int time_left;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
        if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
        if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
        timer = al_create_timer(1.0);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
        
        event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
            al_destroy_timer(timer);
		return -1;
	}
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
       
        srand (time(NULL)*3.14);
        
        win_number= rand()%MAX_NUM+1;
	
	time_left = TOTAL_TIME;
        
        al_start_timer(timer);
        while (!exit)
        {
            ALLEGRO_EVENT ev;
            if (al_get_next_event(event_queue,&ev))
            {
                if (ev.type == ALLEGRO_EVENT_TIMER)
                {
                    --time_left;
                    printf("Te quedan %d",time_left);
		    if (time_left == 0)
		    	exit = true;
                }
                else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    if ( ( ev.keyboard.keycode - '0') == win_number)
                    {
                        wined=0;
			exit = true;
                    }    
                }
            }
        }
        if (wined==0)
        {
            printf("Capo de la life");
        }
        else 
        {
            printf("putovich");
        }
        al_destroy_timer(timer);
}*/

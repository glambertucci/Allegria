/*#include <stdio.h>
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
*/
 //Intento dos
 #include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>

//cancer 

#include "get_char.h"
#include "nonblock.h"
//
#define TOTAL_TIME 7
#define MAX_NUM 9
int main(void)
{
    int win_number;
    bool wined=false;
    bool exit = false;
    int time_left;
    int guess=0;
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
        printf("win number: %d",win_number);
        al_start_timer(timer);
        while (!exit)
        {
            ALLEGRO_EVENT ev;
            if (al_get_next_event(event_queue,&ev))
            {
                if (ev.type == ALLEGRO_EVENT_TIMER)
                {
                    --time_left;
                    printf("\nTe quedan %d\n",time_left);
		    if (time_left == 0)
		    	exit = true;
                }
                //CANCER QUE "funca" peor que el orginal
              // guess = get_char() -'0';
                //
                if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                  
                    switch (ev.keyboard.keycode)
                    {                        
                        case ALLEGRO_KEY_0: guess = 0; break;
                        case ALLEGRO_KEY_PAD_0: guess = 0; break;
                        case ALLEGRO_KEY_1: guess = 1; break;
                        case ALLEGRO_KEY_PAD_1: guess = 1; break;
                        case ALLEGRO_KEY_2: guess = 2; break;
                        case ALLEGRO_KEY_PAD_2: guess = 2; break;
                        case ALLEGRO_KEY_3: guess = 3; break;
                        case ALLEGRO_KEY_PAD_3: guess = 3; break;
                        case ALLEGRO_KEY_4: guess = 4; break;
                        case ALLEGRO_KEY_PAD_4: guess = 4; break;
                        case ALLEGRO_KEY_5: guess = 5; break;
                        case ALLEGRO_KEY_PAD_5: guess = 5; break;
                        case ALLEGRO_KEY_6: guess = 6; break;
                        case ALLEGRO_KEY_PAD_6: guess = 6; break;
                        case ALLEGRO_KEY_7: guess = 7; break;
                        case ALLEGRO_KEY_PAD_7: guess = 7; break;
                        case ALLEGRO_KEY_8: guess = 8; break;
                        case ALLEGRO_KEY_PAD_8: guess = 8; break;
                        case ALLEGRO_KEY_9: guess = 9; break;
                        case ALLEGRO_KEY_PAD_9: guess = 9; break;
                    }    
                  
                }
                  if (guess == win_number)
            {
                wined = true;
                exit = true;
            }
            }
          
        }
        if (wined==1)
        {
            printf("\nCapo de la life\n");
        }
        else 
        {
            printf("\nputovich\n");
        }
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
}

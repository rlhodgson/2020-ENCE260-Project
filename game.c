/**
    @file game.c
    @author Matthew Bond, Rachel Hodgson
    @date 07 October 2020
    @brief Main game program
 
 */

#include <stdlib.h>

#include "paddle.h"
#include "pio.h"
#include "system.h"
#include "display.h"
#include "navswitch.h"
#include "../fonts/font3x5_1.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "timer.h"
#include "task.h"
#include "ball.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "prescale.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 1000

#define BALL_RATE 2

#define NAV_LOOP_RATE 1000

typedef struct Pos_state_s {
	int row_s;
	int col_s;
} Pos_state;


void game_over(void) {
	tinygl_text("Game Over");
}


int main (void)
{
	
	uint16_t ball_tick = 0;
    uint16_t nav_tick = 0;
    

    int row = 0;
    int col = 1;
    int rowinc = 1;
    int colinc = 1;
    
    
    system_init ();

    pacer_init (LOOP_RATE);
    
    int direction = 0;
    int check = 1;
    int state = 0;
    
	/* Initialising the system, navswitch and paddle modules */
    paddle_initial();
    
	/* Initialising tinygl and relevant tinygl functions */
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);
	tinygl_point_t ball;
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    paddle_initial_points();
    
    ir_uart_init();
    
    
    Pos_state recieved = {0, 0};


    while (1)
    {
		
		
		pacer_wait ();
		
		ball_tick++;
		
			
		if (ball_tick >= LOOP_RATE / BALL_RATE) {
				
			ball_tick = 0;
			
			
			
			if (state == 0) {
				if (ir_uart_read_ready_p()!= 0) {
					
					recieved.row_s = ir_uart_getc();
					recieved.col_s = ir_uart_getc();
					
					row = recieved.row_s;
					col = recieved.col_s;
					state = 1;
					
					
					ball = ball_set_high(row, col, ball);

					
				} 
			}
				
			if (state == 1) {
				
				if (col == 0) {
					
					ball = ball_set_low(row, col, ball);
					col = 1;
					colinc = colinc * -1;
					ir_uart_putc(row);
					ir_uart_putc(col);
					state = 0;
				}
				
				else {
				
					
			
					ball = ball_set_low(row, col, ball);
					

					if (col == 4) {
						
						check = check_ball_paddle(ball);
					}

						
					if (check == 1) {
						
						// move ball
					
						col += colinc;
						row += rowinc;
						
						// check ball is within the right place

						if (row > 6 || row < 0)
						{
							// in future we woukd start the other screen if the row was < 0
							row -= rowinc * 2;
							rowinc = -rowinc;
						}

						if (col > 4 || col < 0)
						{
							// check if there has been a collision between ball and paddle, if so then continue
							col -= colinc * 2;
							colinc = -colinc;
						}
					
				
						ball = ball_set_high(row, col, ball);
						
						
					} else {
						ball = ball_set_low(row, col, ball);
						return 0;

					}
				}
			}
		} 
		
			
			
		nav_tick++;
        if (nav_tick >= LOOP_RATE / NAV_LOOP_RATE) {
			
			nav_tick = 0;
			navswitch_update ();
			
			if (navswitch_push_event_p (NAVSWITCH_PUSH))
			{
				state = 1;

			}
			
			/* If switch pushed down, move the paddle to the right */
			if (navswitch_push_event_p (NAVSWITCH_NORTH) && check_paddle_north() == 1)
			{
				north_paddle(direction);

			}
			
			/* If switch pushed down, move the paddle to the left */
			if (navswitch_push_event_p (NAVSWITCH_SOUTH) && check_paddle_south() == 1)
			{
				south_paddle(direction);

			}
			
		}
		
		tinygl_update ();
			
			
		}

		
		
}

        

        
		
		
		
		
    

    
    
    
    
    
    
    
    
    
   
    

    





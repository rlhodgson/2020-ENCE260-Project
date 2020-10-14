/**
    @file game.c
    @author Matthew Bond, Rachel Hodgson
    @date 15 October 2020
    @brief Main game program
 
 */

#include <stdlib.h>
#include "paddle.h"
#include "pio.h"
#include "system.h"
#include "display.h"
#include "navswitch.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "tinygl.h"
#include "ball.h"
#include "ir_uart.h"

/* Define polling rate in Hz.  */
#define LOOP_RATE 1000

#define BALL_RATE 2

#define NAV_LOOP_RATE 1000

#define MESSAGE_RATE 10

/* Struct definition for state variables */
typedef struct Pos_state_s {
    
	int row_s;
	int col_s;
} Pos_state;

/* Sets the matrix to allow for W and L to be displayed */
void set_game_over(void) {
    
    tinygl_clear();
    tinygl_init (1);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (1);
}

/* Main program loop */
int main (void)
{
	
	uint16_t ball_tick = 0;
    uint16_t nav_tick = 0;
    
    // initialisers for ball movement
    int row = 0;
    int col = 1;
    int rowinc = 1;
    int colinc = 1;
    
    system_init ();

    pacer_init (LOOP_RATE);
    
    // Initialiser for direction of paddle movement, check for paddle hit or miss and the state of the game
    int direction = 0;
    int check = 1;
    int state = 0;
    int data_received = 0;
    
    
	// Initialising the system, navswitch and paddle modules
    paddle_initial();
    paddle_initial_points();
    ir_uart_init();
    
	// Initialising tinygl and relevant tinygl functions
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);
   
	tinygl_point_t ball;

    // Variable to received IR communications
    Pos_state recieved = {0, 0};

    // Main loop
    while (1)
    {
		pacer_wait ();
		
		ball_tick++;
		
		if (ball_tick >= LOOP_RATE / BALL_RATE) {
				
			ball_tick = 0;
			
            //check game state
			if (state == 0) {
				if (ir_uart_read_ready_p()!= 0) {
                    
                    data_received = ir_uart_getc();
					
					if (data_received == 20) {
					
						recieved.row_s = ir_uart_getc();
						recieved.col_s = ir_uart_getc();
						
						row = recieved.row_s;
						col = recieved.col_s;
						state = 1;
						
						ball = ball_set_high(row, col, ball);
                        
					} else if (data_received == 30){
                        
						ball = ball_set_low(row, col, ball);
                        
                        // Turn on blue LED for winner
                        PORTC |= (1 << 2);
                        
                        set_game_over();
                        
                        // Display W for winner
                        tinygl_text("W\0");
                        
                        while (1) {
                            tinygl_update ();
                        }
                        
						break;
                    }
                }
            }
				
			if (state == 1) {
				
                // If the ball is at the top of the board
				if (col == 0) {
					
					ball = ball_set_low(row, col, ball);
					col = 1;
					colinc = colinc * -1;
					ir_uart_putc(20);
					ir_uart_putc(row);
					ir_uart_putc(col);
					state = 0;
				}
				
				else {
                    
					ball = ball_set_low(row, col, ball);
					
                    // If it is at the bottom, check if it hit the paddle
					if (col == 4) {
						
						check = check_ball_paddle(ball);
					}

                    // If it hit the paddle then continue as normal
					if (check == 1) {
											
						col += colinc;
						row += rowinc;
						
						// check ball is within the right place
						if (row > 6 || row < 0)
						{
							row -= rowinc * 2;
							rowinc = -rowinc;
						}

						if (col > 4 || col < 0)
						{
							col -= colinc * 2;
							colinc = -colinc;
						}
				
						ball = ball_set_high(row, col, ball);
						
						
					} else {
						ir_uart_putc(30);
                        
						ball = ball_set_low(row, col, ball);
						
                        set_game_over();
                        
                        // Display L for loser
                        tinygl_text("L\0");
                        
                        while (1) {
                            tinygl_update ();
                        }
                        
                        break;
					}
				}
			}
		} 
		
		nav_tick++;
        if (nav_tick >= LOOP_RATE / NAV_LOOP_RATE) {
			
			nav_tick = 0;
			navswitch_update ();
			
            // Check if navswitch was pushed
			if (navswitch_push_event_p (NAVSWITCH_PUSH))
			{
				state = 1;

			}
			
			// If switch pushed down, move the paddle to the right
			if (navswitch_push_event_p (NAVSWITCH_NORTH) && check_paddle_north() == 1)
			{
				north_paddle(direction);

			}
			
			// If switch pushed down, move the paddle to the left
			if (navswitch_push_event_p (NAVSWITCH_SOUTH) && check_paddle_south() == 1)
			{
				south_paddle(direction);

			}
			
		}
		
		tinygl_update ();
			
		}
}

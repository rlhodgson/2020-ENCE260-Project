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
#include "ledmat.h"
#include "navswitch.h"
#include "../fonts/font3x5_1.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "timer.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 900


int main (void){
	
	int direction = 0;
    
    /* Initialising the system, navswitch and paddle modules */
	system_init ();
	navswitch_init ();
    paddle_initial();
    
    /* Initialising tinygl and relevant tinygl functions */
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);
    
    /* Set the initial parameters */
    paddle_initial_points();
    
    while (1)
    {

        /* Check if the switch has been pressed */
        navswitch_update ();

        /* If switch pushed up, move the paddle to the right */
        if (navswitch_push_event_p (NAVSWITCH_NORTH) && check_paddle_north() == 1)
        {
			north_paddle(direction);

        }
        
        /* If switch pushed down, move the paddle to the left */
        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && check_paddle_south() == 1)
        {
            south_paddle(direction);

        }

        tinygl_update ();
    }
    return 0;


}

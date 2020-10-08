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
#include "task.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 900
#define BUTTON_POLL_RATE 100

static void navswitch_task (__unused__ void *data)
{
    int direction = 0;
    navswitch_update ();
    
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



int main (void){
	
    
    /* Initialising the system, navswitch and paddle modules */
	system_init ();
    paddle_initial();
    
    /* Initialising tinygl and relevant tinygl functions */
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);
    
    /* Set the initial parameters */
    paddle_initial_points();
    
    
    
    
    task_t tasks[] =
    {
        {
            .func = navswitch_task,
            .period = LOOP_RATE / BUTTON_POLL_RATE,
            .data = 0
        },
    };


    system_init ();

    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
    
    return 0;


}


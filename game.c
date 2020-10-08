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


/* Define polling rate in Hz.  */
#define NAV_LOOP_RATE 900
#define BALL_LOOP_RATE 10
#define BUTTON_POLL_RATE 100


// Random stuff I tried earlier
/*typedef struct ballFlash_s {
    int row;
    int col;
    int rowinc;
    int colinc;
} ballFlash;

typedef struct state_s {
    int playing;
} state;*/



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

int check_collision(int row_num)
{
    
    // return 1 if a collision has occured
    // checks if the row of the call is the same as the row of the paddle, i think
    
    int paddle1 = pos_first();
    int paddle2 = pos_second();
    int paddle3 = pos_third();

    
    int collision = 0;
    
    if (row_num == paddle1 || row_num == paddle2 || row_num == paddle3) {
        collision = 1;
    }
    
    return collision;
}


static void ball_task (void* data)
{
    //state* game = (state*) data;
    int col = 0;
    int row = 0;
    int rowinc = 1;
    int colinc = 1;
    int game_state = 1;
    
    //pacer_init (BALL_LOOP_RATE);
    
    while (game_state == 1) {
        
        //pacer_wait (); //think we need something to wait for a bit
        
        //set the relevant point
        tinygl_point_t ballpoint = tinygl_point(col, row);
        
        //make it low to begin with
        tinygl_draw_point(ballpoint, 0);
        
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

        if (col < 0)
        {
            col -= colinc * 2;
            colinc = -colinc;
        }
        
        // check if there has been a collision between ball and paddle, if so then continue
        if (col > 4 && (check_collision(row) == 1))
        {
            col -= colinc * 2;
            colinc = -colinc;
        } else if (col > 4 && (check_collision(row) == 0)) {
            game_state = 0;
            // else attempt to stop, doesn't work
            
        }
        
        // then when it's all good light up the ball
        ballpoint = tinygl_point(col, row);
        tinygl_draw_point(ballpoint, 1);
        

        tinygl_update ();
    }
            
}


int main (void) {
    
   task_t tasks[] =
    {
        {
            .func = navswitch_task,
            .period =  TASK_RATE / NAV_LOOP_RATE,
            .data = 0
        },
        {
            .func = ball_task,
            .period =  TASK_RATE / BALL_LOOP_RATE,
            .data = 0
        }

    };
    
    system_init ();
    ledmat_init ();
    
    
    /* Initialising the system, navswitch and paddle modules */
    paddle_initial();
    
    /* Initialising tinygl and relevant tinygl functions */
    tinygl_init (NAV_LOOP_RATE);
    tinygl_font_set (&font3x5_1);
    
    /* Set the initial parameters */
    paddle_initial_points();
    

    task_schedule (tasks, 2);
    return 0;


}
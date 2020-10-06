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
	system_init ();
	navswitch_init ();
	
    paddle_initial();
    
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);
    
    paddle_initial_points();
    
    while (1)
    {

        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH) && check_paddle_north() == 1)
        {
			north_paddle(direction);

        }
        
        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && check_paddle_south() == 1)
        {
            south_paddle(direction);

        }

        tinygl_update ();
    }
    return 0;


}

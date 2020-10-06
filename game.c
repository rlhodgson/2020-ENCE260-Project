#include <stdlib.h>

//#include "paddle.h"

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



void point_init (tinygl_point_t pos) {

	tinygl_draw_point (pos, 1);

}


void point_add (tinygl_point_t pos, int direction) {
     
    tinygl_point_t prev_pos;
    if (direction == 1) {
		prev_pos = tinygl_point (pos.x, pos.y + 1);
	}
	if (direction == 2) {
		prev_pos = tinygl_point (pos.x, pos.y - 1);
	}

    tinygl_draw_point (pos, 1);
    tinygl_draw_point (prev_pos, 0);
}


void point_update (tinygl_point_t pos1, tinygl_point_t pos2, tinygl_point_t pos3, int direction) {
	

	if (direction == 1) {
		point_add (pos1, direction);
		point_add (pos2, direction);
		point_add (pos3, direction);
	}
	if (direction == 2) {
		point_add (pos3, direction);
		point_add (pos2, direction);
		point_add (pos1, direction);
	}
}


int main (void){
//void start_paddle() {

	
	
	system_init ();
	
	navswitch_init ();
	
	int direction = 0;
	
    tinygl_point_t pos = tinygl_point (4, 2);
    tinygl_point_t pos_2 = tinygl_point (4, 3);
    tinygl_point_t pos_3 = tinygl_point (4, 4);
    

    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);


    point_init (pos);
    point_init (pos_2);
    point_init (pos_3);

    while (1)
    {

        navswitch_update ();
        
        
        if (navswitch_push_event_p (NAVSWITCH_NORTH) && pos_3.y >= TINYGL_HEIGHT/2)
        {

            pos.y--;
            pos_2.y--;
            pos_3.y--;
            direction = 1;
            point_update(pos, pos_2, pos_3, direction);

        }
        
        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && pos.y <= TINYGL_HEIGHT/2)
        {

            pos.y++;
            pos_2.y++;
            pos_3.y++;
            direction = 2;
            point_update(pos, pos_2, pos_3, direction);

        }


        tinygl_update ();
    }
    return 0;


}

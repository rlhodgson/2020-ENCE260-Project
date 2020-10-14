/**
    @file ball.c
    @author Matthew Bond, Rachel Hodgson
    @date 12 October 2020
    @brief Ball module, contains movement functions for the ball
 
 */

#include "tinygl.h"
#include "system.h"
#include "../fonts/font3x5_1.h"
#include "pio.h"
 
/* Turns the 'ball' off, sets the LED to low */
tinygl_point_t ball_set_low(int row, int col, tinygl_point_t ball) {
    
	//set the relevant point  
	ball = tinygl_point(col, row);
			
	//make it low to begin with
	tinygl_draw_point (ball, 0);
	
	return ball;
}

/* Turns the 'ball' on, sets the LED to high */
tinygl_point_t ball_set_high(int row, int col, tinygl_point_t ball) {
	
	//set the relevant point  
	ball = tinygl_point(col, row);
			
	//make it low to begin with
	tinygl_draw_point (ball, 1);
	
	return ball;
}

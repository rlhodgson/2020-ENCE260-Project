/**
    @file paddle.c
    @author Matthew Bond, Rachel Hodgson
    @date 07 October 2020
    @brief Paddle module, contains movement functions for the paddle
 
 */

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "pio.h"
#include "../fonts/font3x5_1.h"

/* Define the paddle as a structure with the 3 relevant position aspects */
typedef struct paddle_s Paddle_str;
struct paddle_s {
	tinygl_point_t pos, pos_2, pos_3;
}paddle;

/* Initialise the paddle positions as individual points */
Paddle_str paddle_initial(void) {
	

	paddle.pos = tinygl_point (4, 2);
	paddle.pos_2 = tinygl_point (4, 3);
	paddle.pos_3 = tinygl_point (4, 4);
	

	
	return paddle;
}

/* Light up the initial paddle on the LED matrix */
void paddle_initial_points(void) {
	
	tinygl_draw_point (paddle.pos, 1);
	tinygl_draw_point (paddle.pos_2, 1);
	tinygl_draw_point (paddle.pos_3, 1);
	
    
}

/* Add a new paddle point */
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

/* Update the  paddle positions to the relevant directions */
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

/* Move paddle one to the left by updating the positions by 1 */
void north_paddle(int direction) {
	
	paddle.pos.y--;
	paddle.pos_2.y--;
	paddle.pos_3.y--;
	direction = 1;
	point_update(paddle.pos, paddle.pos_2, paddle.pos_3, direction);
	
}

/* Move paddle one to the right by updating the positions by 1 */
void south_paddle(int direction) {
	
	paddle.pos.y++;
	paddle.pos_2.y++;
	paddle.pos_3.y++;
	direction = 2;
	point_update(paddle.pos, paddle.pos_2, paddle.pos_3, direction);
	
}

/* Check to make sure the paddle is within the matrix length before moving left */
int check_paddle_north(void) {
	
	
	if (paddle.pos_3.y >= TINYGL_HEIGHT/2) {
		return 1;
	} else {
		return 0;
	}
}
	
/* Check to make sure the paddle is within the matrix length before moving right */
int check_paddle_south(void) {
	
	
	if (paddle.pos.y <= TINYGL_HEIGHT/2) {
		return 1;
	} else {
		return 0;
	}
}
	




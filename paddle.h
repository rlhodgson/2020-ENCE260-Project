/**
    @file paddle.h
    @author Matthew Bond, Rachel Hodgson
    @date 07 October 2020
    @brief Paddle module, contains movement functions for the paddle
 
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "tinygl.h"

/* Define the paddle as a structure with the 3 relevant position aspects */

typedef struct paddle_s Paddle_str;
struct paddle_s {
	tinygl_point_t pos, pos_2, pos_3;
}paddle;


//void point_init (tinygl_point_t pos);

/* Initialise the paddle positions as individual points */
Paddle_str paddle_initial(void);

/* Light up the initial paddle on the LED matrix */
void paddle_initial_points(void);

/* Add a new paddle point */
void point_add (tinygl_point_t pos, int direction);

/* Update the  paddle positions to the relevant directions */
void point_update (tinygl_point_t pos1, tinygl_point_t pos2, tinygl_point_t pos3, int direction);

/* Move paddle one to the left by updating the positions by 1 */
void north_paddle(int direction);

/* Move paddle one to the right by updating the positions by 1 */
void south_paddle(int direction);

/* Check to make sure the paddle is within the matrix length before moving left */
int check_paddle_north(void);

/* Check to make sure the paddle is within the matrix length before moving right */

int check_paddle_south(void);

int pos_first(void);

int pos_second(void);

int pos_third(void);

int check_ball_paddle(tinygl_point_t ball);


#endif

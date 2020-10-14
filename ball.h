/**
    @file ball.h
    @author Matthew Bond, Rachel Hodgson
    @date 12 October 2020
    @brief Ball module, contains movement functions for the ball
 
 */

#ifndef BALL_H
#define BALL_H

#include "tinygl.h"

/* Turns the 'ball' off, sets the LED to low */
tinygl_point_t ball_set_low(int row, int col, tinygl_point_t ball);

/* Turns the 'ball' on, sets the LED to high */
tinygl_point_t ball_set_high(int row, int col, tinygl_point_t ball);

#endif

/**
    @file ball.h
    @author Matthew Bond, Rachel Hodgson
    @date 12 October 2020
    @brief Ball module, contains movement functions for the ball
 
 */


#ifndef BALL_H
#define BALL_H

#include "tinygl.h"


//void ball_init();
tinygl_point_t ball_set_low(int row, int col, tinygl_point_t ball);
tinygl_point_t ball_set_high(int row, int col, tinygl_point_t ball);





#endif

#ifndef PADDLE_H
#define PADDLE_H

#include "tinygl.h"

typedef struct paddle_s Paddle_str;
struct paddle_s {
	tinygl_point_t pos, pos_2, pos_3;
}paddle;


//void point_init (tinygl_point_t pos);

Paddle_str paddle_initial(void);

void paddle_initial_points(void);

void point_add (tinygl_point_t pos, int direction);

void point_update (tinygl_point_t pos1, tinygl_point_t pos2, tinygl_point_t pos3, int direction);

void north_paddle(int direction);

void south_paddle(int direction);

int check_paddle_north(void);

int check_paddle_south(void);


#endif

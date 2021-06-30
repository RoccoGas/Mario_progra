#ifndef __DRAWING_FUNCTIONS__
#define __DRAWING_FUNCTIONS__

#include "allegro.h"
#include "sprites.h"

#include <stdio.h>

struct Vf2d {
	double x;
	double y;
};

struct Rectangle {
	struct Vf2d pos;
	struct Vf2d size;
};

//bool mouse_vs_rect_mouse_state(ALLEGRO_MOUSE_STATE mouseState, struct Rectangle r); // si el mouse esta "sobre" el rectangula devuelve true
void draw_world(struct Camera camera, int map[], ALLEGRO_BITMAP* tiles[]);
void draw_mario(struct Mario mario);
void make_mario_jump(struct Mario* mario);
void make_mario_move_right(struct Mario* mario);
void make_mario_move_left(struct Mario* mario);
void update_mario(struct Mario* mario, ALLEGRO_KEYBOARD_STATE keyboardState);

#endif // __DRAWING_FUNCTIONS__

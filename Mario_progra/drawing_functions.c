
#include "drawing_functions.h"
#include "level.h"
#include "header.h"

#include <stdio.h>

//bool mouse_vs_rect_mouse_state(ALLEGRO_MOUSE_STATE mouseState, struct Rectangle r) { // si el mouse esta "sobre" el rectangula devuelve true
//	return (mouseState.x >= r.pos.x && mouseState.y >= r.pos.y && mouseState.x < r.pos.x + r.size.x && mouseState.y < r.pos.y + r.size.y);
//}

void draw_world(struct Camera camera, int map[], ALLEGRO_BITMAP* tiles[]){ // una mierda no funciona
	if (camera.posX < DISPLAY_WIDTH / 2) {
		camera.posX = DISPLAY_WIDTH / 2;
	}

	for (unsigned int j = 0; j < OCEAN_FLOOR; j += BLOCK_UNIT) {
		for (unsigned int i = 0; i <= DISPLAY_WIDTH; i += BLOCK_UNIT) {
			al_draw_bitmap(tiles[WATER], (camera.posX - (DISPLAY_WIDTH / 2)) + i, j, NO_FLAGS);
		}
	}
	for (unsigned int j = OCEAN_FLOOR + 1; j <= DISPLAY_HEIGHT; j += BLOCK_UNIT) {
		for (unsigned int i = 0; i <= DISPLAY_WIDTH; i += BLOCK_UNIT) {
			al_draw_bitmap(tiles[GROUND], (camera.posX - (DISPLAY_WIDTH / 2)) + i, j, NO_FLAGS);
		}
	}
}

void draw_mario(struct Mario mario) {
	al_draw_bitmap(mario.bitmap, mario.posX, mario.posY, NO_FLAGS);
}

void make_mario_jump(struct Mario* mario) {
	mario->state = JUMPING;
	mario->velY = -20.0f;
	mario->frameCount = 0;
}

void make_mario_move_right(struct Mario* mario) {
	mario->state = MOVING_RIGHT;
	mario->velX = 2.0f;

}

void make_mario_move_left(struct Mario* mario) {
	mario->state = MOVING_LEFT;
	mario->velX = -2.0f;
}

void update_mario(struct Mario* mario, ALLEGRO_KEYBOARD_STATE keyboardState) {

	if (al_key_down(&keyboardState, ALLEGRO_KEY_D)) {
		mario->velX += 0.25;
	}

	if (al_key_down(&keyboardState, ALLEGRO_KEY_A)) {
		mario->velX -= 0.25f;
	}

	
	mario->velY += 0.25f; // Gravedad

	mario->posX += mario->velX;
	mario->posY += mario->velY; // actualizar posicion

	mario->velX *= 0.9f;
	mario->velY *= 0.9f;

	if (mario->posY + MARIO_HEIGHT >= OCEAN_FLOOR ) {
		mario->posY = OCEAN_FLOOR - MARIO_HEIGHT;
	}
}
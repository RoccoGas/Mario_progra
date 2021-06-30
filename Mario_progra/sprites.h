#ifndef __SPRITES__
#define __SPRITES__

#include "allegro.h"
#include "header.h"

enum MARIO_STATES_E{STANDING, MOVING_LEFT, MOVING_RIGHT, JUMPING};

#define MARIO_HEIGHT 64
#define MARTIO_WIDTH 64

struct Mario {
	float	posX;
	float	posY;

	float velX;
	float velY;

	unsigned char frameCount;

	enum MARIO_STATES_E state;

	//bool isJumping;

	ALLEGRO_BITMAP* bitmap;

}; 

struct Camera {
	float posX;
	float posY;
};

struct Squid {
	float posX;
	float posY;
};

struct Fish {
	float posX;
	float posY;
};



#endif // __SPRITES__	 

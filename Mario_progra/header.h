
#ifndef __HEADER__
#define __HEADER__

enum ERROR_OPTIONS_E { NO_ERROR_START_GAME, RESUME_GAME, QUIT_GAME, QUIT_TO_MENU, BAD_ASSET, BAD_DISPLAY, BAD_QUEUE, BAD_TIMER };

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 960

#define BLOCK_UNIT 16

#define GRID_WIDTH (DISPLAY_WIDTH/BLOCK_UNIT)
#define GRID_HEIGHT (DISPLAY_HEIGHT/BLOCK_UNIT)

#define MAP_WIDTH 400
#define MAP_HEIGHT GRID_HEIGHT

#define OCEAN_FLOOR (DISPLAY_HEIGHT - (4 * BLOCK_UNIT))

#define JUMP_dX 20
#define JUMP_dY	20

#define GRAVITY 5

#define NO_FLAGS 0 

#define TIMER_FPS(n)	(1.0/n)

#endif // !__HEADER__

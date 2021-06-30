
#include "allegro.h"
#include "menu.h"
#include "header.h"
#include "drawing_functions.h"
#include "level.h"

#include <stdio.h>


int main(int argc, char* argv[]) {

    if (!initialize_allegro()) {
        printf("Unable to start because allegro was not properly initialized...");
        return -1;
    }

    //---------------------------- Start Menu -------------------------------//

start_menu:
    /*switch (start_menu()) {
    case NO_ERROR_START_GAME:
        printf("No errors so far! Starting game...\n");
        break;

    case QUIT_GAME:
        printf("Exiting game\n");
        return 0;
        break;

    case BAD_ASSET:
    case BAD_DISPLAY:
    case BAD_QUEUE:
    case BAD_TIMER:
        printf("Aborted execution because of an error in the main menu\n");
        return -1;
        break;
    }*/

    switch (level_one()) {
    case NO_ERROR_START_GAME:
        printf("No errors so far! Continuing game...\n");
        break;
    case QUIT_TO_MENU:
        printf("Going to main menu...\n");
        goto start_menu;

    case QUIT_GAME:
        printf("Exiting game\n");
        return 0;
        break;

    case BAD_ASSET:
    case BAD_DISPLAY:
    case BAD_QUEUE:
    case BAD_TIMER:
        printf("Aborted execution because of an error in level 1\n");
        return -1;
        break;
    }



    
    destroy_allegro();
	return  0;
}

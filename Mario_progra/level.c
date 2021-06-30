
#include "menu.h"
#include "allegro.h"
#include "header.h"
#include "level.h"
#include "sprites.h"
#include "drawing_functions.h"

#include <stdio.h>

enum ERROR_OPTIONS_E level_one() {
    printf("[LEVEL 1]\n");

    al_reserve_samples(1);

    ALLEGRO_BITMAP* bitmapWater;
    ALLEGRO_BITMAP* bitmapGround;
    ALLEGRO_BITMAP* tiles[2]; //donde cargo las texturas
    ALLEGRO_FONT* font;
    ALLEGRO_SAMPLE* musicSample;
    ALLEGRO_SAMPLE_INSTANCE* music;



    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;

    const char* bitmapGroundFilepath = "assets/level/ground.jpg";
    const char* bitmapWaterFilepath = "assets/level/water.jpg";
    const char* fontFilepath = "assets/level/mario_font.ttf";
    const char* musicSampleFilepath = "assets/level/jolly_rogger_bay.wav";


    //---------------------- Mario, camera, level Init---------------------------//
    struct Mario mario;
    const char* marioFilepath = "assets/level/mario.png";
    mario.posX = 20.0f;
    mario.posY = 20.0f;

    mario.velX = 0.0f;
    mario.velY = 0.0f;

    mario.state = STANDING;
    mario.frameCount = 0;
    mario.bitmap = al_load_bitmap(marioFilepath);

    if (mario.bitmap == NULL) {
        fprintf(stderr, "Failed to load %s\n", marioFilepath);
        return BAD_ASSET;
    }

    struct Camera camera;
    camera.posX = 0;
    camera.posY = 0;

    int map[MAP_WIDTH * MAP_HEIGHT];

    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//

    bitmapGround = al_load_bitmap(bitmapGroundFilepath);
    if (bitmapGround == NULL) {
        fprintf(stderr, "Failed to load %s\n", bitmapGroundFilepath);
        return BAD_ASSET;
    }

    bitmapWater = al_load_bitmap(bitmapWaterFilepath);
    if (bitmapWater == NULL) {
        fprintf(stderr, "Failed to load %s\n", bitmapWaterFilepath);
        return BAD_ASSET;
    }

    font = al_load_font(fontFilepath, MENU_FONT_SIZE, NO_FLAGS);
    if (font == NULL) {
        fprintf(stderr, "Failed to load %s\n", fontFilepath);
        return BAD_ASSET;
    }

    musicSample = al_load_sample(musicSampleFilepath);
    if (musicSample == NULL) {
        fprintf(stderr, "Failed to load %s\n", musicSampleFilepath);

    }

    music = al_create_sample_instance(musicSample);

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (display == NULL) {
        fprintf(stderr, "Failed to create menu display of width %u and height %u\n ", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        return BAD_DISPLAY;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stderr, "Failed to create menu event queue\n");
        return BAD_QUEUE;
    }

    timer = al_create_timer(TIMER_FPS(MENU_FPS));
    if (timer == NULL) {
        fprintf(stderr, "Failed to create menu timer of %u FPS\n", MENU_FPS);
        return BAD_TIMER;
    }

    tiles[WATER] = bitmapWater;
    tiles[GROUND] = bitmapGround;

    //---------------------- Registro eventos, comienzo el timer, nombro ventana, empiezo musica, cargo bitmaps a GPU ------------------------//

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    al_set_window_title(display, "Rocco's Mario - Level 1");

    al_attach_sample_instance_to_mixer(music, al_get_default_mixer());
    al_set_sample_instance_playmode(music, ALLEGRO_PLAYMODE_LOOP);
  //  al_play_sample_instance(music);  //  DESCOMENTAR !!!!!!!

    al_convert_bitmap(tiles[WATER]);
    al_convert_bitmap(tiles[GROUND]);
    al_convert_bitmap(mario.bitmap);

    al_convert_memory_bitmaps();

    //-------------------------- Game loop ---------------------------//

    bool running = true;
    enum ERROR_OPTIONS_E menuOption = NO_ERROR_START_GAME;
    unsigned int pauseMoment;

    while (running) {
        al_get_next_event(queue, &event);
        al_get_keyboard_state(&keyboardState);
        al_get_mouse_state(&mouseState);
        

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: // EXIT
            running = false;
            menuOption = QUIT_GAME;
            break;

        case ALLEGRO_EVENT_TIMER: //FRAME
            draw_world(camera, map, tiles);
            update_mario(&mario, keyboardState);
            draw_mario(mario);


            al_flip_display();
            break;

        case ALLEGRO_EVENT_KEY_DOWN: //PRESS KEY
            switch (event.keyboard.keycode) {

            case ALLEGRO_KEY_ESCAPE:
            case ALLEGRO_KEY_P:
                pauseMoment = al_get_sample_instance_position(music);
                al_set_sample_instance_playing(music, false);

                menuOption = pause_menu(display);
                al_flush_event_queue(queue); //Tengo q vaciar el queue y agregar delays xq si no se pausa de nuevo apenas se cerraba
                al_rest(0.25f);

                al_set_sample_instance_position(music, pauseMoment);
                al_set_sample_instance_playing(music, true);

                if (menuOption == QUIT_TO_MENU || menuOption == QUIT_GAME) {
                    running = false;
                }
                break;
            case ALLEGRO_KEY_W:
            case ALLEGRO_KEY_SPACE:
                make_mario_jump(&mario);
                break;
            case ALLEGRO_KEY_D:
                make_mario_move_right(&mario);
                break;
            case ALLEGRO_KEY_A:
                make_mario_move_left(&mario);
                break;
            defualt:
                break;
            }
        default:
            break;
        }


    }

    al_stop_sample_instance(music);

    al_destroy_bitmap(bitmapWater);
    al_destroy_bitmap(bitmapGround);
    al_destroy_bitmap(mario.bitmap);
    al_destroy_sample(musicSample);
    al_destroy_sample_instance(music);
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [LEVEL 1]\n");

    return menuOption;
}
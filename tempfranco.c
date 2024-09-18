#include "tempfranco.h"
#include"GENERAL.h"
#include<ncurses.h>




//conditional compilation
#ifdef WINDOWS
#define SLEEP(t) (sleep((t)))
#else
#define SLEEP(t) (napms((t)))
#endif



//default settings
#define SNAKE_LENGTH 1
#define SNAKE_HEAD '@'
#define SNAKE_BODY 'O'
#define LIFE 10
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define FRUIT_CH 'F'
#define TIMESTEP 200
#define BORDER_CHAR '#'
#define TIME_MAX 30



/*THIS WORKS AS MAIN GAME LOOP*///Game loop

void GameLoop(game_settings_t * game){
    //initial settings
    bool game_over=0;
   	SetupFront(game);//initializes ncurses mode
    SetupBack(game);
}
void SetupBack(game_settings_t * game){

}
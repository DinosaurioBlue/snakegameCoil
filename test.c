#include"GENERAL.h"
#include"BACKEND.h"
#include"FRONTEND.h"
#include<stdio.h>
#include<ncurses.h>
int main (void){
    //initializing game
    game_settings_t myGame;
    game_settings_t * game = &myGame;

    
    //calling to game loop
    GameLoop(game);
    printf("The game finished perfectly\n");
    getchar();

    
    return 0;
}
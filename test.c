#include"GENERAL.h"
#include"BACKEND.h"
#include"FRONTEND.h"

int main (void){
    //initializing game
    game_settings_t myGame;
    game_settings_t * game = &myGame;

    
    //calling to game loop
    GameLoop(game);
    SetupBack(game);
    SetupFront(game);

    //need to clean ncurses mode 
    KillScreen();
    return 0;
}
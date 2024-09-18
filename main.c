//includes 
#include"frontend.h"
#include"backend.h"
//main function
int main (void){
    game_settings_t game;
    game_settings_t * p2game=&game;
    startGame(p2game);
    kill_game();
       return 0;
}

//includes 
#include"snake.h"
#include"menu.h"
//main function
int main (void){
    game_settings_t game;
    game_settings_t * p2game=&game;
    snakeGame(p2game);
    kill_game();
       return 0;
}

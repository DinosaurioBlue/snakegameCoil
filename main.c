//includes 
#include"snake.h"
#include"menu.h"
//main function
int main (void){
    //creating the game and it's pointer
    game_settings_t game;
    game_settings_t * p2game=&game;
    snakeGame(p2game);
       return 0;
}

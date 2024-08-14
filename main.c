#include"snake.h"
#include"menu.h"
int main (void){

    game_settings my_game;
    menu(&my_game);
   int score = game_loop(&my_game);
    update_score();

    return 0;
}
#include"snake.h"
#include"menu.h"
int main (void){

    game_settings my_game;
    menu(&my_game);
    game_setup(&my_game);
    game_loop(&my_game);
    kill_game();
    update_score();

    return 0;
}
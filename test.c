#include"snake.h"
#include"menu.h"

int main (void){
    game_settings_t game;
    game_settings_t * p2game;
    p2game = &game;
    configureGame(p2game,"goku");
    return 0;
}

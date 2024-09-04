//includes 
#include"snake.h"
#include"menu.h"
//main function
int main (void){
    //creating the game and it's pointer
    game_settings_t game;
    game_settings_t * p2game=&game;
    //then the game is started 
    start_game(p2game);
    kill_game();
    
    printf("your score was %d\n",game.score);

    startGame();



   return 0;
}

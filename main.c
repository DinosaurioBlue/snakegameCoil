#include"snake.h"
#include"menu.h"
int main (void){
    initscr();
    /*game_settings my_game;
    menu(&my_game);
   int score = start_game(&my_game);
    update_score(score);*/
    print_borders(10,10);
    getch();
    endwin();
    return 0;
}
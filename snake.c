#include"snake.h"



void game_setup(game_settings * game){
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0); // Hide the cursor

}
int game_loop(game_settings * game){
    int score;
    int game_over=0;
    game_setup(game);
    //here we have to add all the variables that we are going to use, like the snake array
    while(!game_over){//this is the loop that i told you about


    
    }
    kill_game();



    return score;

}
void kill_game (void){
    endwin();
}
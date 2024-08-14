#include"snake.h"

void game_setup(game_settings * game){
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0); // Hide the cursor

}


void kill_game (void){
    endwin();
}
void print_borders(int height,int width){
    int i,j;
    for(i=0;i<=height;++i){
        for(j=0;j<width;++j){
            if(!(i==0||i==height)){
                mvprintw(i,j,"#");
                mvprintw(i,width-1,"#");
                j=width;
            }
            else{
                mvprintw(i,j,"#");
            }
        }
    }

}
void print_score(int score, int board_height){
    
}


/*THIS WORKS AS MAIN GAME LOOP*/
int start_game(game_settings * game){
    int score;
    int game_over=0;
    game_setup(game);
    //here we have to add all the variables that we are going to use, like the snake array
    while(!game_over){//this is the loop that i told you about


    
    }
    kill_game();



    return score;

}

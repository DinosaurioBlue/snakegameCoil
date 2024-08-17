#include"snake.h"
/*THIS WORKS AS MAIN GAME LOOP*/

void start_game(game_settings_t * game){

    //initial settings_t
    game->score=0;
    game->life =3;
    int game_over=0;
   	game_setup();

    //initializing snake
    static snake_t snake;
    static snake_t * p2snake = &snake;
    InitializeSnake(p2snake,game);





    //game loop
    while(!game_over){
        draw(game,p2snake);
        
        //print_snake(p2snake);
        
        
        
        refresh();
        napms(100);
    }
    //game over ==1
    clear();
    mvprintw(0,0,"game over papichulo");
    refresh();
    getch();
    //free heap space
    mem_free(snake.pos);

  
    

}


void game_setup(void){
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0); // Hide the cursor

}


void kill_game (void){
    endwin();
}
void draw(game_settings_t* game,snake_t*snake){
    clear();//erasing screen
    int i;
    //printing borders
    for (i = 0; i < game->board_width + 2; i++) {
        mvprintw(0, i, "#");
        mvprintw(game->board_height + 1, i, "#");
    }
    for (i = 0; i < game->board_height + 2; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, game->board_width + 1, "#");
    }
    //printing score and life
    mvprintw(game->board_height+4,0,"your score is:%d",game->score);
    mvprintw(game->board_height+5,0,"your lifes are:%d",game->life);

    //printing snake
    mvprintw(snake->pos[0].y,snake->pos[0].x,"%c",game->snake_head);
    for(i=1;i<snake->length;++i){
        mvprintw(snake->pos[i].y,snake->pos[i].x,"%c",game->snake_body);
    }
}


void InitializeSnake(snake_t *snake, game_settings_t * game) {//initializes snake
    snake->length= game->snake_length;
    snake->pos = (vector_t*)malloc(MALLOCSIZE*sizeof(vector_t));
    (snake->pos[0]).x = (game->board_height)/2;
    (snake->pos[0]).y = (game->board_width)/2;
    snake->dir.x=1;
    snake->dir.y=0;

}
void mem_free(void * snake_body){//deallocates memory from heap
    free(snake_body);
}

#include"snake.h"
/*THIS WORKS AS MAIN GAME LOOP*/

void start_game(game_settings_t * game){

    //initial settings
    game->score=0;
    game->life =3;
    int game_over=0;
   	game_setup();

    //initializing snake
    static snake_t snake;
    static snake_t * p2snake = &snake;
    InitializeSnake(p2snake,game);
    fruit(game);
    game->score=0;




    //GAME LOOP
    while(!game_over){
        movement(p2snake, game);
        collisionscheck(p2snake, game, &game_over);
        draw(game, p2snake);
        #ifdef WINDOwS
        Sleep(game.speed);  // delay
        #else
        napms(game->speed);
        #endif
        
    }
    getch();
    endgame(game,p2snake);
}


void game_setup(void){
    #ifndef WINDOWS
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0); // Hide the cursor
    #else
    CLEAR();
    #endif

}


void kill_game (void){
    #ifndef WINDOWS
    endwin();
    #endif
}
void draw(game_settings_t* game,snake_t*snake){
    clear();//erasing screen
    int i;
    //printing borders
    #ifndef WINDOWS
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
    
    //printing fruit
    mvprintw(game->fruit_y, game->fruit_x, "%c", game->fruit_ch);  



    #else//windows draw's function
    for (i = 0; i < game->board_width + 2; i++) {
        gotoxy(i, 0);
        printf("#");
        gotoxy(i, game->board_height + 1);
        printf("#");
    }
    for (i = 0; i < game->board_height + 2; i++) {
        gotoxy(0, i);
        printf("#");
        gotoxy(game->board_width + 1, i);
        printf("#");
    }

    // Printing score and life
    gotoxy(0, game->board_height + 3);
    printf("Score: %d", game->score);
    gotoxy(0, game->board_height + 4);
    printf("Lives: %d", game->life);

    // Printing snake
    gotoxy(snake->pos[0].x, snake->pos[0].y);
    printf("%c", game->snake_head);
    for(i=1; i<snake->length; ++i){
        gotoxy(snake->pos[i].x, snake->pos[i].y);
        printf("%c", game->snake_body);
    }

    // Printing fruit
    gotoxy(game->fruit_x, game->fruit_y);
    printf("%c",game->fruit_ch);
    #endif
}


void InitializeSnake(snake_t *snake, game_settings_t * game) {//initializes snake
    snake->length= game->snake_length;
    snake->pos = (vector_t*)malloc(MALLOCSIZE * sizeof(vector_t));
    if (snake->pos == NULL) {
        perror("Failed to allocate memory for snake");
        exit(EXIT_FAILURE);
    }
    (snake->pos[0]).x = (game->board_height)/2;
    (snake->pos[0]).y = (game->board_width)/2;
    snake->dir.x=1;
    snake->dir.y=0;
    

}
void mem_free(void *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

void fruit(game_settings_t *game) {
    srand((unsigned int)time(NULL));  // Seed the random number generator
    game->fruit_x = rand() % game->board_width+1;
    game->fruit_y = rand() % game->board_height+1;
}
void endgame(game_settings_t * game,snake_t * snake){
    CLEAR();
    #ifdef WINDOWS
    gotoxy(0,0);
    printf("Game Over! Your score was %d\n", game->score);
    #else
    mvprintw(0,0,"Game Over! Your score was %d\n", game->score);
    refresh();
    #endif
    getch();
    mem_free(snake->pos);
}
void movement(snake_t *snake, game_settings_t *game) {
    // Handling user input for movement
    int ch;
    #ifdef WINDOWS
    
    if(kbhit()) {
        ch = getch();
        switch(ch) {
            case 'w': snake->dir.x = 0; snake->dir.y = -1; break;
            case 's': snake->dir.x = 0; snake->dir.y = 1; break;
            case 'a': snake->dir.x = -1; snake->dir.y = 0; break;
            case 'd': snake->dir.x = 1; snake->dir.y = 0; break;
        }
    }
    #else
    halfdelay(1);
    ch = getch();
        switch(ch) {
            case 'w': snake->dir.x = 0; snake->dir.y = -1; break;
            case 's': snake->dir.x = 0; snake->dir.y = 1; break;
            case 'a': snake->dir.x = -1; snake->dir.y = 0; break;
            case 'd': snake->dir.x = 1; snake->dir.y = 0; break;
        }

    #endif
    
    // Update snake position
    for(int i = snake->length - 1; i > 0; --i) {
        snake->pos[i] = snake->pos[i - 1];
    }
    snake->pos[0].x += snake->dir.x;
    snake->pos[0].y += snake->dir.y;
}
void collisionscheck(snake_t *snake, game_settings_t *game, int *game_over) {
    // Check for wall collisions
    if(snake->pos[0].x <= 0 || snake->pos[0].x >= game->board_width + 1 || 
       snake->pos[0].y <= 0 || snake->pos[0].y >= game->board_height + 1) {
        *game_over = 1;
    }

    // Check for self-collision
    for(int i = 1; i < snake->length; i++) {
        if(snake->pos[0].x == snake->pos[i].x && snake->pos[0].y == snake->pos[i].y) {
            *game_over = 1;
        }
    }

    // Check if fruit is eaten
    if(snake->pos[0].x == game->fruit_x && snake->pos[0].y == game->fruit_y) {
        game->score += 10;
        snake->length += 1;
        fruit(game);
    }
}
#ifdef WINDOWS
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif
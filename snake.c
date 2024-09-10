#define DEVELOPING 1
#ifdef DEVELOPING
#define NAME "jorge"
#define SNAKE_LENGTH 1
#define SNAKE_HEAD '@'
#define SNAKE_BODY 'O'
#define LIFE 3
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define FRUIT_CH 'F'
#define TIMESTEP 120
#define BORDER_CHAR '#'
#endif


#include"snake.h"



/*THIS WORKS AS MAIN GAME LOOP*/

void snakeGame(game_settings_t * game){

    //initial settings
    int game_over=0;
   	game_setup(game);

    //initializing snake
    static snake_t snake;
    static snake_t * p2snake = &snake;
    InitializeSnake(p2snake,game);
    fruit(game);
    //GAME LOOP
    while(!game_over){
        movement(p2snake, game);
        collisionscheck(p2snake, game, &game_over);
        draw(game, p2snake);
        #ifdef WINDOWS
        Sleep(game->timestep);  // delay
        #else
        #endif

    }
    endgame(game,p2snake);
}


void game_setup(game_settings_t * game){
    #ifndef WINDOWS
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0); // Hide the cursor
    #else
    CLEAR();
    #endif

    game->score =0;

    //THIS MUST BE DELETED ONCE MENU IS DONE
    game->board_height = BOARD_HEIGHT;
    game->board_width = BOARD_WIDTH;
    game->fruit_ch=FRUIT_CH;
    game->life= LIFE;
    game->snake_body= SNAKE_BODY;
    game->snake_head=SNAKE_HEAD;
    game->snake_length= SNAKE_LENGTH;
    game->timestep= TIMESTEP;
    game->user_name = NAME;
    game->board_char = BORDER_CHAR
    //TILL HERE
;


}


void kill_game (void){
    #ifndef WINDOWS
    endwin();
    #endif
}
void draw(game_settings_t* game,snake_t*snake){
    CLEAR();//erasing screen
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
        printf("%c",);
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
    snake->pos = (vector_t*)malloc((snake->length) * sizeof(vector_t));
    if (snake->pos == NULL) {
        perror("Failed to allocate memory for snake");
        exit(EXIT_FAILURE);
    }
    (snake->pos[0]).x = (game->board_height)/2;
    (snake->pos[0]).y = (game->board_width)/2;
    snake->dir.x=1;
    snake->dir.y=0;


}
void resize(snake_t * snake){
snake->pos=(vector_t*)realloc(snake->pos,snake->length*sizeof(vector_t));
 if (snake->pos == NULL) {
        perror("Failed to allocate memory for snake");
        exit(EXIT_FAILURE);
    }

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
void endgame(game_settings_t * game,snake_t * snake){//end messagge and deallocates memory
    CLEAR();
    #ifdef WINDOWS
    gotoxy(0,0);
    printf("Game Over! Your score was %d\n", game->score);
    Sleep(2000);
    #else
    mvprintw(0,0,"Game Over! Your score was %d\n", game->score);
    refresh();
    napms(2000);
    #endif
    mem_free(snake->pos);

}
void movement(snake_t *snake, game_settings_t *game) {
    // Handling user input for movement
    int ch;
    #ifdef WINDOWS

    if(kbhit()) {//this is to make the game not to be paused every time it gets here
        ch = getch();
        
        if(ch=='w' && snake->dir.y !=1) {
            snake->dir.x = 0; snake->dir.y = -1;
        }
        else if(ch=='s'&& snake->dir.y !=-1) {
            snake->dir.x = 0; snake->dir.y = 1;
        }
        else if(ch=='a'&& snake->dir.x !=1) {
            snake->dir.x = -1; snake->dir.y = 0;
        }
        else if(ch=='d'&& snake->dir.x !=-1) {
            snake->dir.x = 1; snake->dir.y = 0;
        }
    }
    #else
   timeout(200);//this is to make the game not to be paused every time it gets here
    ch = getch();
    if(ch=='w' && snake->dir.y !=1) {
        snake->dir.x = 0; snake->dir.y = -1;
    }
    else if(ch=='s'&& snake->dir.y !=-1) {
        snake->dir.x = 0; snake->dir.y = 1;
    }
    else if(ch=='a'&& snake->dir.x !=1) {
        snake->dir.x = -1; snake->dir.y = 0;
    }
    else if(ch=='d'&& snake->dir.x !=-1) {
        snake->dir.x = 1; snake->dir.y = 0;
    }

    #endif

    // Update snake position
    for(int i = snake->length - 1; i > 0; --i) {
        snake->pos[i] = snake->pos[i - 1];
    }
    snake->pos[0].x += snake->dir.x;
    snake->pos[0].y += snake->dir.y;
}
void collisionscheck(snake_t *snake, game_settings_t *game, int * game_over) {

    // Check for wall collisions
    if(snake->pos[0].x <= 0 || snake->pos[0].x >= game->board_width + 1 ||
       snake->pos[0].y <= 0 || snake->pos[0].y >= game->board_height + 1) {
        collision(game, snake, game_over);
    }

    // Check for self-collision
    for(int i = 1; i < snake->length; i++) {
        if(snake->pos[0].x == snake->pos[i].x && snake->pos[0].y == snake->pos[i].y) {
            collision(game, snake, game_over);
        }
    }

    // Check if fruit is eaten,
    if(snake->pos[0].x == game->fruit_x && snake->pos[0].y == game->fruit_y) {
        yummy(game,snake);//what happens if a fruit is eaten??read below
    }



}
void collision(game_settings_t * game, snake_t * snake, int * game_over){

     if(game->life>1){//checks if you sill have lifes and sets the snake as new
            --(game->life);
            (game->snake_length)=SNAKE_LENGTH;
            free(snake->pos);
            InitializeSnake(snake,game);
            game->score-=20;
            if(game->score<0){//this make the socre not to be negative
                game->score =0;
            }
        }
        else{
            *game_over=1;
        }
}

void yummy(game_settings_t * game, snake_t * snake){
    game->score += 10;//updates score
    snake->length += 1;//updates lenght
    resize(snake);//resizes
    fruit(game);
    if(game->timestep>50){
        game->timestep-=10;//makes the game faster until the timestep is 50ms
    }

}
#ifdef WINDOWS//ncurses has this function integrated in mvprintw
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

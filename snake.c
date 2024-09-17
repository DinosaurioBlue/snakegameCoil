//default settings
#define SNAKE_LENGTH 1
#define SNAKE_HEAD '@'
#define SNAKE_BODY 'O'
#define LIFE 3
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define FRUIT_CH 'F'
#define TIMESTEP 200
#define BORDER_CHAR '#'
#define TIME_MAX 30


/*Here it changes wether you are in linux or windows*/
#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")
void gotoxy(int x, int y);
#else
#include<ncurses.h>
#define CLEAR() clear()
#endif
//general inlcudes
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#define LOWCASE(c) ('a'<=(c) && (c)<='z' ? (c) : ((c)+'A'-'a') )




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
        movement(p2snake, game, &game_over);
        collisionscheck(p2snake, game, &game_over);
        draw(game, p2snake);


    }
    endgame(game,p2snake);
}


void game_setup(game_settings_t * game){
    #ifndef WINDOWS
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    curs_set(0); // Hide the cursor
    nodelay(stdscr,TRUE);
    #else
    CLEAR();
    #endif

    game->score =0;

    
    if(!game->configured){
        game->board_height = BOARD_HEIGHT;
        game->board_width = BOARD_WIDTH;
        game->board_char = BORDER_CHAR;
        game->fruit_ch=FRUIT_CH;
        game->life= LIFE;
        game->snake_body= SNAKE_BODY;
        game->snake_head=SNAKE_HEAD;
        game->snake_length= SNAKE_LENGTH;
        game->timestep= TIMESTEP;
        
    }



}


void kill_game (void){
    #ifndef WINDOWS
    endwin();
    curs_set(1);
    #endif
}
void draw(game_settings_t* game,snake_t*snake){
    CLEAR();//erasing screen
    int i;
    //printing borders
    #ifndef WINDOWS
    for (i = 0; i < game->board_width + 2; i++) {
        mvprintw(0, i, "%C",game->board_char);
        mvprintw(game->board_height + 1, i, "%C",game->board_char);
    }
    for (i = 0; i < game->board_height + 2; i++) {
        mvprintw(i, 0, "%C",game->board_char);
        mvprintw(i, game->board_width + 1, "%C",game->board_char);
    }
    //printing score and life
    mvprintw(game->board_height+4,0,"your score is:%d",game->score);
    mvprintw(game->board_height+5,0,"your lifes are:%d",game->life);

    //printing snake
    mvprintw(snake->pos[0].y,snake->pos[0].x,"%C",game->snake_head);
    for(i=1;i<snake->length;++i){
        mvprintw(snake->pos[i].y,snake->pos[i].x,"%C",game->snake_body);
    }

    //printing fruit
    mvprintw(game->fruit_y, game->fruit_x, "%C", game->fruit_ch);



    #else//windows draw's function
    for (i = 0; i < game->board_width + 2; i++) {
        gotoxy(i, 0);
        printf("%C",);
        gotoxy(i, game->board_height + 1);
        printf("%C",game->board_char);
    }
    for (i = 0; i < game->board_height + 2; i++) {
        gotoxy(0, i);
        printf("%C",game->board_char);
        gotoxy(game->board_width + 1, i);
        printf("%C",game->board_char);
    }

    // Printing score and life
    gotoxy(0, game->board_height + 3);
    printf("Score: %d", game->score);
    gotoxy(0, game->board_height + 4);
    printf("Lives: %d", game->life);

    // Printing snake
    gotoxy(snake->pos[0].x, snake->pos[0].y);
    printf("%C", game->snake_head);
    for(i=1; i<snake->length; ++i){
        gotoxy(snake->pos[i].x, snake->pos[i].y);
        printf("%C", game->snake_body);
    }

    // Printing fruit
    gotoxy(game->fruit_x, game->fruit_y);
    printf("%C",game->fruit_ch);
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
    curs_set(1);
    #endif
    mem_free(snake->pos);
    

}
void movement(snake_t *snake, game_settings_t *game, int * game_over) {

    int ch;
    #ifdef WINDOWS

    if(kbhit()) {//this is to make the game not to be paused every time it gets here
        sleep(game->timestep);     
    }
    #else
   napms(game->timestep);
   #endif
    ch = getch();
    static int previous;
    if(ch!=previous){
        switch(ch) {
    case 'W':
    case 'w':
        if (snake->dir.y != 1) {
            snake->dir.x = 0;
            snake->dir.y = -1;
        }
        break;
    case 'S':
    case 's':
        if (snake->dir.y != -1) {
            snake->dir.x = 0;
            snake->dir.y = 1;
        }
        break;
    case 'A':
    case 'a':
        if (snake->dir.x != 1) {
            snake->dir.x = -1;
            snake->dir.y = 0;
        }
        break;
    
    case 'D':
    case 'd':
        if (snake->dir.x != -1) {
            snake->dir.x = 1;
            snake->dir.y = 0;
        }
        break;
    case 'Q':
    case 'q':
        *game_over = 1;
        break;
    case ERR:
        break;
    default:
        fflush(stdin);
        break;
        }
    }
    else{
        fflush(stdin);
    }
    previous = ch;



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
            if(game->score>=20){//this make the score not to be negative
                game->score-=20;
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
    if(game->timestep>TIME_MAX){
        game->timestep-=10;//makes the game faster until the timestep is 50ms
    }

}
#ifdef WINDOWS//ncurses has this function integrated in mvprintw. moves the cursor to x,y coordinates
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

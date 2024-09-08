#ifndef SNAKE_H
#define SNAKE_H
//includes and struct definitions


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

//struct definitions
typedef struct {
    const char * user_name;
    int snake_length;
    char snake_head;
    char snake_body;
    int score;
    int life;
    unsigned char board_height;
    unsigned int board_width;
    int fruit_x;
    int fruit_y;
    char fruit_ch;
    int timestep;
} game_settings_t;


typedef struct
{
    unsigned int x;
    unsigned int y;
}vector_t;

typedef struct {
    vector_t * pos;
    vector_t dir;
    int length;
} snake_t;


void snakeGame (game_settings_t * game);//main game loop
void game_setup (game_settings_t * game);//
void kill_game(void);//end ncurses mode
void draw(game_settings_t* game, snake_t* snake);//draws everything
void InitializeSnake(snake_t *snake, game_settings_t * game);//initializes snake position and size
void mem_free(void * snake_body);//deallocates memory
void movement(snake_t *snake, game_settings_t *game);//changes snake direction and possition
void collisionscheck(snake_t *snake, game_settings_t *game, int *game_over);//checks if you colide with yourself or a wall
void fruit(game_settings_t *game);//randomly generates a food
void gotoxy(int x, int y);//a funciton that moves where you are going to print. in ncurses is integrates in mvprintw(...)
void endgame(game_settings_t * game,snake_t * snake);//final things to the game
void resize(snake_t * snake);//whenever the snakes eats the fruit
#endif

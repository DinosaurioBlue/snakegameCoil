#ifndef SNAKE_H
#define SNAKE_H

//includes and struct definitions



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

#define MALLOCSIZE 25

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
    int speed;
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


void start_game (game_settings_t * game);
void game_setup (void);
void kill_game(void);
void draw(game_settings_t* game, snake_t* snake);
void InitializeSnake(snake_t *snake, game_settings_t * game);
void mem_free(void * snake_body);
void movement(snake_t *snake, game_settings_t *game);
void collisionscheck(snake_t *snake, game_settings_t *game, int *game_over);
void fruit(game_settings_t *game);
void manage_lives(game_settings_t *game, int *game_over);
void gotoxy(int x, int y);
void endgame(game_settings_t * game,snake_t * snake);
#endif
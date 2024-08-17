#ifndef SNAKE_H
#define SNAKE_H

//includes and struct definitions

#include<ncurses.h> 
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

//function declarations in order of the program
void start_game (game_settings_t * game);
void game_setup (void);
void kill_game(void);
void draw(game_settings_t*game,snake_t*snake);
void InitializeSnake(snake_t *snake,game_settings_t * game);
void mem_free(void * snake_body);


#endif

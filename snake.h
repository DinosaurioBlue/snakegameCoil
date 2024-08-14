#ifndef SNAKE_H
#define SNAKE_

//includes and struct definitions
#include<ncurses.h> 
typedef struct {
    const char * user_name;
    int snake_length;
    char snake_head;
    char snake_body;
    int score;
    unsigned char board_height;
    unsigned int board_width;
} game_settings;
typedef struct vector
{
    unsigned int x;
    unsigned int y;
};

//function declarations
void game_setup (game_settings * game);
int start_game (game_settings * game);
void kill_game(void);
void print_borders(int height,int width);
void print_score(int score, int board_height);



#endif
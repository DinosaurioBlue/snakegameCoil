#ifndef SNAKE_H
#define SNAKE_
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
void game_setup (game_settings * game);
int game_loop (game_settings * game);
void kill_game(void);




#endif
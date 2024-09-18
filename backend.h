#ifndef BACKEND
#define BACKEND


typedef struct {
    char snake_head;
    char snake_body;
    char board_char;
    char fruit_ch;
    unsigned int score;
    unsigned int life;
    unsigned int snake_length;
    unsigned int board_height;
    unsigned int board_width;
    unsigned int fruit_x;
    unsigned fruit_y;
    unsigned int timestep;
    unsigned int configured;
} game_settings_t;

typedef struct
{
    unsigned int x;
    unsigned int y;
}vector_t;

typedef struct {
    vector_t * pos;
    vector_t dir;
    unsigned int length;
} snake_t;





#endif
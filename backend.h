#ifndef BACKEND_H
#define BACKEND_H
//struct definitions
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

// Snake game mechanics
void initialize_game();
void update_game_state();
int check_game_over();
Position* get_snake();
int get_snake_length();
Position get_food();
void place_food();

// Score management
void increase_score();
int get_score();

#endif

#ifndef BACKEND_H
#define BACKEND_H

typedef struct {
    int x, y;
} Position;

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

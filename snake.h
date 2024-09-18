#ifndef SNAKE_H
#define SNAKE_H


void snakeGame (game_settings_t * game);//main game loop
void game_setup (game_settings_t * game);//
void kill_game(void);//end ncurses mode
void draw(game_settings_t* game, snake_t* snake);//draws everything
void InitializeSnake(snake_t *snake, game_settings_t * game);//initializes snake position and size
void mem_free(void * snake_body);//deallocates memory
void movement(snake_t *snake, game_settings_t *game, int * game_over);//changes snake direction and possition
void collisionscheck(snake_t *snake, game_settings_t *game, int *game_over);//checks if you colide with yourself or a wall
void fruit(game_settings_t *game);//randomly generates a food
void gotoxy(int x, int y);//a funciton that moves where you are going to print. in ncurses is integrates in mvprintw(...)
void endgame(game_settings_t * game,snake_t * snake);//final things to the game
void resize(snake_t * snake);//whenever the snakes eats the fruit
void collision(game_settings_t * game, snake_t * snake, int * game_over);
void yummy(game_settings_t * game, snake_t * snake);
#endif

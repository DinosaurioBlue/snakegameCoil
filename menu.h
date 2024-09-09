#ifndef MENU
#define MENU

void startGame(void);
void checkPlayer(void);
void signUp(void);
void login(void);
void top_score(void);
int comparePlayer(const void *a, const void *b);
void snakeGame (game_settings_t * game);
void kill_game(void);


#define NAME_MAX 30
#define MAX_PLAYERS 150


typedef struct{
	char user[NAME_MAX];
	int score;
}player_t;



#endif

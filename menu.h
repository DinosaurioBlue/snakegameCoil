#ifndef MENU
#define MENU

void startGame(game_settings_t *);
void checkPlayer(game_settings_t *);
void signUp(game_settings_t *);
void login(game_settings_t *);
void top_score(game_settings_t *);
int comparePlayer(const void *a, const void *b);
void snakeGame (game_settings_t *);
void kill_game(void);

#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")
void gotoxy(int x, int y);
#else
#include<ncurses.h>
#define CLEAR() clear()
#endif

#define NAME_MAX 30
#define MAX_PLAYERS 150


typedef struct{
	char user[NAME_MAX];
	int score;
}player_t;



#endif

#ifndef MENU
#define MENU

void startGame(game_settings_t *);
void checkPlayer(game_settings_t *);
void signUp(game_settings_t *);
void login(game_settings_t *);
void top_score(game_settings_t *);
int comparePlayer(const void *a, const void *b);
void configureGame (game_settings_t * game);
void cleanStdin(void);
#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")
void gotoxy(int x, int y);
#else
#include<termios.h>
#define CLEAR() system("clear");
#endif

#define NAME_MAX 30
#define MAX_PLAYERS 150


typedef struct{
	char user[NAME_MAX];
	int score;
}player_t;



#endif

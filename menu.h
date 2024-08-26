#ifndef MENU
#define MENU

void startGame(void);
void checkPlayer(void);
void signUp(void);
void login(void);
void top_score(void);
int comparePlayer(const void *a, const void *b);

#define NAME_MAX 30
#define MAX_PLAYERS 150


typedef struct{
	char user[NAME_MAX];
	int score;
}player_t;



#endif

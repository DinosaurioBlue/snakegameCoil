#ifndef TOPSCORE
#define TOPSCORE

void top_score(void);
int comparePlayer(const void * a, const void * b);

#define MAX_PLAYERS 150
#define NAME_MAX 30

typedef struct{
	char user[NAME_MAX];
	int score;
}player_t;



#endif
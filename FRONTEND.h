/*Here theres all related to user interface*/
#ifndef FRONTEND_H
#define FRONTEND_H
#include "GENERAL.h"



void Draw(game_settings_t* game,snake_t*snake);
input_t GetInput(void);
void CleanStdin(void);
void SetupFront (game_settings_t * game);
void KillScreen (void);
void PrintScreen(const char *string);
void ReceiveEnter(void);
char ReceiveChar(int num_chars, ...);
void ReceiveStr(char *str);
void startGame(game_settings_t * game);
void PrintTopscores(game_settings_t *game, int cantPlayers);
void ConfigurationPlayer(game_settings_t * game);
int EndGame(game_settings_t * game);









#endif

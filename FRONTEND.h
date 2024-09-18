/*Here theres all related to user interface*/
#ifndef FRONTEND_H
#define FRONTEND_H
#include "GENERAL.h"



void Draw(game_settings_t* game,snake_t*snake);

input_t GetInput(void);
void CleanStdin(void);
void SetupFront (void);









#endif

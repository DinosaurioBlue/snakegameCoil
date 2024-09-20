#ifndef BACKEND_H
#define BACKEND_H
#include"GENERAL.h"

//snake function
void GameLoop(game_settings_t * game);
void SetupBack(game_settings_t* game);
void InitializeSnake(snake_t *snake, game_settings_t * game);
void SpawnFruit(game_settings_t *game);
void MoveSnake(snake_t * snake, game_settings_t * game, bool * gameOver);
void FreeMem(void *ptr);
void Resize(snake_t * snake);
void CheckCollision(snake_t * snake, game_settings_t * game, bool * gameOver);
void HasCollide(game_settings_t * game, snake_t * snake, bool * gameOver);
void Growth(game_settings_t * game, snake_t * snake);
void TimeScoreInc(game_settings_t * game);



//menu functions
int StartMenu(game_settings_t *game);
int CheckPlayer(game_settings_t *game);
int SignupPlayer(game_settings_t *game);
int LoginPlayer(game_settings_t *game);
void TopScores(game_settings_t *game);
int ComparePlayer(const void * a, const void * b);
int AskConfiguration(game_settings_t *game);
void ConfigureGame(game_settings_t *game);
void UpdateScore(game_settings_t *game);
bool PlayAgain(game_settings_t *game);

#endif


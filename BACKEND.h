#ifdef BACKEND_H
#define BACKEND_H

void StartMenu(game_settings_t *game);
void CheckPlayer(game_settings_t *game);
void SignupPlayer(game_settings_t *game);
void LoginPlayer(game_settings_t *game);
void TopScores(game_settings_t *game);
int comparePlayer(const void * a, const void * b);
void AskConfiguration(game_settings_t *game);
void ConfigureGame(game_settings_t *game);

#endif


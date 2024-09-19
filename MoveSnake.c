/*Esta funcion es llamada desde el GameLoop(funcion principal de backend). lo que hace es modificar la direccion*/

void MoveSnake(snake_t * snake, game_settings_t * game, bool * gameOver){

	input_t direction = GetInput();//receiving a direction
	switch (direction)
	{
	case UP: if (snake->dir.y != 1) {
            snake->dir.x = 0;
            snake->dir.y = -1;
        }
		break;
	case DOWN: if (snake->dir.y != -1) {
            snake->dir.x = 0;
            snake->dir.y = 1;
        }
		break;
	case LEFT: if (snake->dir.x != 1) {
            snake->dir.x = -1;
            snake->dir.y = 0;
        }
		break;
	case RIGHT: if (snake->dir.x != -1) {
            snake->dir.x = 1;
            snake->dir.y = 0;
        }
		break;
	case QUIT: *gameOver = 1;
		break;
	case PAUSE: 
		while(GetInput()!=PAUSE);
		break;
	case RESTART:{ 
			game->restarted =1;
			FreeMem(snake->pos);//we free dinamic memory, bad things could happen if not
			SetupBack(game);//will set the snake to it's initial setting
			InitializeSnake(snake, game);
			SpawnFruit(game);
			
		}
		break;
	default:
		break;

}

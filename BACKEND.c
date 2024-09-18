/*This source code makes all the backend, user doesn't see nothingh from here*/

//general includes
#include"GENERAL.h"
#include"BACKEND.h"
#include"FRONTEND.h"
#include<stdlib.h>
#include<time.h>





//conditional compilation
#ifdef WINDOWS
#define SLEEP(t) (sleep((t)))
#include<conio.h>
#include<windows.h>
#else
#define SLEEP(t) (napms((t)))
#include<ncurses.h>
#endif



//default settings
#define SNAKE_LENGTH 1
#define LIFE 10
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define TIMESTEP 200
#define TIME_MAX 30
#define NAME_MAX 50



/*THIS WORKS AS MAIN GAME LOOP*///Game loop

void GameLoop(game_settings_t * game){
    //initial settings
    bool game_over=0;
   	SetupFront(game);//initializes ncurses mode
    SetupBack(game);
	static snake_t snake;
    static snake_t * p2snake = &snake;
    InitializeSnake(p2snake,game);
    SpawnFruit(game);
    //GAME LOOP
    while(!game_over){
        MoveSnake(p2snake, game, &game_over);
        CheckCollision(p2snake, game, &game_over);
        Draw(game, p2snake);
		SLEEP(game->timeStep);


    }
    EndGame(game,p2snake);








}
/********************************************************************************
 * 					end of Main game loop
 * 
 * *****************************************************************************/
void SetupBack(game_settings_t * game){
    game->score =0;

	static game_settings_t initialSetting;
	if(!game->restarted){
		initialSetting = *game;
	}
	else{ 
		*game = initialSetting;
		game->restarted=0;
		}

    if(!game->configured){//default settings
        game->boardHeight = BOARD_HEIGHT;
        game->boardWidth = BOARD_WIDTH;
        game->life= LIFE;
        game->snakeLength= SNAKE_LENGTH;
        game->timeStep= TIMESTEP;
        
    }
	
	




}
void InitializeSnake(snake_t *snake, game_settings_t * game) {

	//dinamic memory allocation
    snake->length= game->snakeLength;
    snake->pos = (vector_t*)malloc((snake->length) * sizeof(vector_t));
    if (snake->pos == NULL) {
        perror("Failed to allocate memory for snake");
        exit(EXIT_FAILURE);
    }
	//We design a specific spawn for the snake
    (snake->pos[0]).x = (game->boardHeight)/2;
    (snake->pos[0]).y = (game->boardWidth)/2;
    snake->dir.x=1;
    snake->dir.y=0;


}

void SpawnFruit(game_settings_t *game) {
    srand((unsigned int)time(NULL));  // Seed the random number generator
    game->fruitCoord.x = rand() % game->boardWidth+1;
    game->fruitCoord.y= rand() % game->boardWidth+1;
}

void MoveSnake(snake_t * snake, game_settings_t * game, int * gameOver){

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
	case PAUSE: while(GetInput()!=PAUSE);
		break;
	case RESTART:{ 
			game->restarted =1;
			FreeMem(snake->pos);//we free dinamic memory, bad things could happen if not
			SetupBack(game);//will set the snake to it's initial setting
			InitializeSnake(snake, game);
			
		}
		break;
	default:
		break;
	}



	
	//update each tail part
    for(int i = snake->length - 1; i > 0; --i) {
        snake->pos[i] = snake->pos[i - 1];
    }
    snake->pos[0].x += snake->dir.x;
    snake->pos[0].y += snake->dir.y;

}
void FreeMem(void *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}
void Resize(snake_t * snake){
snake->pos=(vector_t*)realloc(snake->pos,snake->length*sizeof(vector_t));
 if (snake->pos == NULL) {
        perror("Failed to allocate memory for snake");
        exit(EXIT_FAILURE);
    }

}
void CheckCollision(snake_t *snake, game_settings_t *game, int * gameOver) {

    // Check for wall collisions
    if(snake->pos[0].x <= 0 || snake->pos[0].x >= game->boardWidth + 1 ||
       snake->pos[0].y <= 0 || snake->pos[0].y >= game->boardHeight + 1) {
        HasColide(game, snake, gameOver);
    }

    // Check for self-collision
    for(int i = 1; i < snake->length; i++) {
        if(snake->pos[0].x == snake->pos[i].x && snake->pos[0].y == snake->pos[i].y) {
            Hascolide(game, snake, gameOver);
        }
    }

    // Check if fruit is eaten,
    if(snake->pos[0].x == game->fruitCoord.x && snake->pos[0].y == game->fruitCoord.y) {
        Growth(game,snake);//what happens if a fruit is eaten??read below
    }



}
void HasCollide(game_settings_t * game, snake_t * snake, int * gameOver){

     if(game->life>1){//checks if you sill have lifes and sets the snake as new
            --(game->life);
            (game->snakeLength)=SNAKE_LENGTH;
            FreeMem(snake->pos);
            InitializeSnake(snake,game);
            if(game->score>=20){//this make the score not to be negative
                game->score-=20;
            }
        }
        else{
            *gameOver=1;
        }

}
void Growth(game_settings_t * game, snake_t * snake){
    game->score += 10;//updates score
    snake->length += 1;//updates lenght
    Resize(snake);//resizes
    SpawnFruit(game);
    if(game->timeStep>TIME_MAX){
        game->timeStep -=10;//makes the game faster until the timestep is 50ms
    }

}

void EndGame(game_settings_t * game,snake_t * snake){//end messagge and deallocates memory
    CLEAR();
    #ifdef WINDOWS
    gotoxy(0,0);
    printf("Game Over! Your score was %d\n", game->score);
    Sleep(2000);
    #else
    mvprintw(0,0,"Game Over! Your score was %d\n", game->score);
    refresh();
    napms(2000);
    curs_set(1);
    #endif
    mem_free(snake->pos);
    

}


/********************************************************************************************************************************************
*				here we separate game from the rest
*
*
*
*********************************************************************************************************************************************/



//function that starts the menu
void StartMenu(game_settings_t *game){
	char x;
	game->configured = 0;
	//funcion q imprime
	if(1){//funcione q pide char)
		
		CheckPlayer(game);
	}
}



//function that goes to the selected option of the menu
void CheckPlayer(game_settings_t *game){
	//funcion q imprime 
	char x;
	x=funcion1();//funcion q pide char
	if(x == 'l' || x == 'L'){
		cleanStdin();
		LoginPlayer(game);
	}
	else if(x == 's' || x == 'S'){
		cleanStdin();
		SignupPlayer(game);
	}
	else if(x == 't' || x == 'T'){
		cleanStdin();
		TopScores(game);		
	}
	else{
		//funcion q imprime 
		CleanStdin();
		//stays in menu
		checkPlayer(game);
	}
	AskConfiguration(game);
}



//function fo a new player to sign up
void SignupPlayer(game_settings_t *game){
	char trash[500];
	int found = 0;
	FILE* pFile;//pointer to a file
	FILE* ptrCheck;
	game->userName=//funcion que pide string
	
	ptrCheck = fopen("history.txt", "r");//pointer to check if the username already exists
	if(ptrCheck == NULL){
		perror("Error opening file");
	}
	
	else{
		while(fgets(trash, sizeof(trash), ptrCheck) != NULL){
		//stores the text that reads in the .txt and then compares it to the player's name 
			if(strstr(trash, game->userName) != NULL){
				found = 1;//user found
			}
		}
		fclose(ptrCheck);
	}
	
	if(found != 1){
		pFile = fopen("history.txt", "a+"); //opens file
		if(pFile == NULL){ //checks if the file exists
			perror("Error opening file");
		}
	
		fprintf(pFile, "USER:%s SCORE:0\n", game->userName); 
		//writes the username and the score into the file 
		fclose(pFile);//closes the file 
	}
	else{
		//funcion q imprime
		CheckPlayer(game);
	
	}

}




void LoginPlayer(game_settings_t *game){
	char buffer[500]; 
	int log = 0;
	FILE *ptr = fopen("history.txt", "r");
	
	if(ptr == NULL){
		perror("Error opening file");
	} 
	else{
		//funcion que imprime
		game->userName=ReceiveStr();//funcion que pide string
		
		
		
		
		while(fgets(buffer, sizeof(buffer), ptr) != NULL){
			//stores the text that reads in the .txt and then compares it to the player name 
			if(strstr(buffer, game->userName) != NULL){
				log = 1;//user found
			}
		}
		
		fclose(ptr);
	}
	if(log){
		//funcion que imprime 
		AskConfiguration(game);
	}
	else{
		//funcion que imprime
		CheckPlayer(game);
	}
}


//Function to display players in order from the highiest score to the lowest
void TopScores(game_settings_t *game){
	char *score;
	char buffer[500];
	int count = 0, i, x;
	FILE *pScan = fopen("history.txt", "r");
	
	CLEAR();
	if(pScan == NULL){
		perror("Error opening file");
	} 	
	
	while(fgets(buffer, sizeof(buffer), pScan) != NULL){
		//set pointers to the user part and the score part
		game->userName = strstr(buffer, "USER:");
		game->score = strstr(buffer, "SCORE:");
		
		if(game->userName != NULL && game->score!= NULL) {
		//copies the name of the player. USER: = 5. Sets the pointer to the first character of the name
			sscanf(game->userName + 5, "%s", game->userName); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			sscanf(score + 6, "%d", game->score);
			count++;
		}
	}
	
	
	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(game->userName, count, sizeof(game_settings_t), ComparePlayer());

	//llamar funcion de frontend
	//PrintTopScores(game, count)
}


//function to compare two elements (scores) to use qsort function 



//function that determines whether the playes wants to configure the game or not  
void AskConfiguration(game_settings_t *game){
	bool x;
	x=AskPlayer(game);
	
	if(x){
		ConfigureGame(game);	
	}
	else if(x==0){
		SnakeGame(game);
		UpdateScore(game);
	}
	else{
		//funcion que imprime 
		AskConfiguration(game);
	}
}



void ConfigureGame(game_settings_t *game){
	int flag=0, temp;
	ConfigurationPlayer(game);
	SnakeGame(game);
	UpdateScore(game);
}










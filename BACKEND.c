/*This source code makes all the backend, user doesn't see nothingh from here*/

//general includes
#include"GENERAL.h"
#include"BACKEND.h"
#include"FRONTEND.h"
#include<stdlib.h>
#include<time.h>
#include<string.h>





//conditional compilation
#ifdef WINDOWS
#define SLEEP(t) (sleep((t)))
#include<conio.h>
#include<windows.h>
#else
#define SLEEP(t) (napms((t)))
#include<ncurses.h>
#include<termios.h>
#define CLEANING() system("clear")//termios.h
#define CLEAR() clear()//ncurses.h
#endif



//default settings
#define SNAKE_LENGTH 1
#define LIFE 10
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define TIMESTEP 200
#define TIME_MAX 30
#define NAME_MAX 50
#define SCORE_DIVIDER 20
#define SCORE_TIME_INC 1
#define SCORE_EATING 10
#define SCORE_COLLIDE 10
#define MIN_TIMESTEP 20
#define SPEED_INCREASMENT 20


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
		TimeScoreInc(game);
		SLEEP(game->timeStep);


    }
    EndGame(game);
	FreeMem(snake.pos);








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
void CheckCollision(snake_t *snake, game_settings_t *game, bool * gameOver) {

    // Check for wall collisions
    if(snake->pos[0].x <= 0 || snake->pos[0].x >= game->boardWidth + 1 ||
       snake->pos[0].y <= 0 || snake->pos[0].y >= game->boardHeight + 1) {
        HasCollide(game, snake, gameOver);
    }

    // Check for self-collision
    for(int i = 1; i < snake->length; i++) {
        if(snake->pos[0].x == snake->pos[i].x && snake->pos[0].y == snake->pos[i].y) {
            HasCollide(game, snake, gameOver);
        }
    }

    // Check if fruit is eaten,
    if(snake->pos[0].x == game->fruitCoord.x && snake->pos[0].y == game->fruitCoord.y) {
        Growth(game,snake);//what happens if a fruit is eaten??read below
    }



}
void HasCollide(game_settings_t * game, snake_t * snake, bool * gameOver){

     if(game->life>1){//checks if you sill have lifes and sets the snake as new
            --(game->life);
            (game->snakeLength)=SNAKE_LENGTH;
            FreeMem(snake->pos);
            InitializeSnake(snake,game);
            if(game->score >= MIN_TIMESTEP){//this make the score not to be negative
                game->score-=SPEED_INCREASMENT;
            }
        }
        else{
            *gameOver=1;
        }

}
void Growth(game_settings_t * game, snake_t * snake){
	game->score += SCORE_EATING;
    snake->length += 1;//updates lenght
    Resize(snake);//resizes
    SpawnFruit(game);
    if(game->timeStep>TIME_MAX){
        game->timeStep -=10;//makes the game faster until the timestep is 50ms
    }

}
void TimeScoreInc(game_settings_t * game){//updating score regarding timestep
	static int cont;
	cont++;
	if(!(cont%SCORE_DIVIDER)){//when the cont is divisible by SCORE_DIVIDER
							  //it increases the score by one
		game->score += 1;
	}

}



/********************************************************************************************************************************************
*				here we separate game from the rest
*
*
*
*********************************************************************************************************************************************/



//function that starts the menu
void StartMenu(game_settings_t *game){
	game->configured = 0;
	char msg[]="SNAKE GAME  \nPress ENTER to start...\n";
	PrintScreen(msg);
	ReceiveEnter();		
	CheckPlayer(game);
}




//function that goes to the selected option of the menu
void CheckPlayer(game_settings_t *game){
	char msg[]=("[T] TOP SCORES\n[L] LOG IN\n[S] SIGN IN\n");
	char x;	
	PrintScreen(msg);
	x=ReceiveChar(6, 'l', 'L', 's', 'S', 't', 'T');
	if(x == 'l' || x == 'L'){
		CleanStdin();
		LoginPlayer(game);
	}
	else if(x == 's' || x == 'S'){
		CleanStdin();
		SignupPlayer(game);
	}
	else{
		CleanStdin();
		TopScores(game);		
	}
	AskConfiguration(game);
}



//function fo a new player to sign up
void SignupPlayer(game_settings_t *game){
	char trash[500];
	int found = 0;
	FILE* pFile;//pointer to a file
	FILE* ptrCheck;
	char msg[100]="Enter your name: ";
	PrintScreen(msg);
	ReceiveStr(game->userName);
		
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
		CLEANING();
		strcpy(msg, "Name already used. Try again!\n");
		PrintScreen(msg);
		CheckPlayer(game);
	}
	AskConfiguration(game);

}




void LoginPlayer(game_settings_t *game){
	char buffer[500]; 
	int log = 0;
	char msg[100];
	FILE *ptr = fopen("history.txt", "r");
	
	if(ptr == NULL){
		perror("Error opening file");
	} 
	else{
		strcpy(msg, "Enter yout username: ");
		PrintScreen(msg);
		ReceiveStr(game->userName);
				
		while(fgets(buffer, sizeof(buffer), ptr) != NULL){
			//stores the text that reads in the .txt and then compares it to the player name 
			if(strstr(buffer, game->userName) != NULL){
				log = 1;//user found
			}
		}
		
		fclose(ptr);
	}
	if(log){
		strcpy(msg, "Welcome back!\n");
		PrintScreen(msg); 
		AskConfiguration(game);
	}
	else{
		strcpy(msg, "User not found. Try again!\n");
		PrintScreen(msg);
		CheckPlayer(game);
	}
}


//Function to display players in order from the highiest score to the lowest
void TopScores(game_settings_t *game){
	char *score;
	char buffer[500];
	int count = 0;
	FILE *pScan = fopen("history.txt", "r");
	
	CLEANING();
	if(pScan == NULL){
		perror("Error opening file");
	} 	
	
	while(fgets(buffer, sizeof(buffer), pScan) != NULL){
		//set pointers to the user part and the score part
		game->userName = strstr(buffer, "USER:");
		game->score = strstr(buffer, "SCORE:");
		
		if(game->userName != NULL && game->score!= 0) {
		//copies the name of the player. USER: = 5. Sets the pointer to the first character of the name
			sscanf(game->userName + 5, "%s", game->userName); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			sscanf(game->score + 6, "%d", &(game->score));
			count++;
		}
	}	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(game->userName, count, sizeof(game_settings_t), ComparePlayer);
	
	PrintTopscores(game, count);
}


//function to compare two elements (scores) to use qsort function 
int ComparePlayer(const void *a, const void *b) {
    // Cast the pointers to game_settings_t
    game_settings_t *playerA = (game_settings_t *)a;
    game_settings_t *playerB = (game_settings_t *)b;

    // Compare scores in descending order (higher score first)
    return playerB->score - playerA->score;
}




//function that determines whether the playes wants to configure the game or not  
void AskConfiguration(game_settings_t *game){
	char x;
	char msg[]="Would you like to configure the game?\n[Y]\n[N]\n";
	PrintScreen(msg);
	x=ReceiveChar(4, 'n', 'N', 'y', 'Y');
	
	if(x=='y' || x=='Y'){
		ConfigureGame(game);	
	}
	else{
		GameLoop(game);
		UpdateScore(game);
	}
}



void ConfigureGame(game_settings_t *game){
	ConfigurationPlayer(game);
	GameLoop(game);
	UpdateScore(game);
}


void UpdateScore(game_settings_t *game){
	char buffer[200];
	char *scorePosition;
	int old_score;
	int score = game->score;
	unsigned long int position;
	FILE *pChange = fopen("history.txt", "r+");
	
	if(pChange == NULL){
		perror("Failed to open file");
	}
	
//Read each line and update the player's score if it's higher than the old one
	while(fgets(buffer, sizeof(buffer), pChange) != NULL){
		if(strstr(buffer, game->userName) != NULL){
			scorePosition = strstr(buffer, "SCORE:");
			if(scorePosition){ 
			//reads the player's old score
				sscanf(scorePosition + 6 , "%d", &old_score); 
				if(score > old_score){  
					position = ftell(pChange);  
					//sets the pointer in the right position to change the player's score
					fseek(pChange, position - strlen(buffer) + (scorePosition - buffer) + 6, SEEK_SET);
					//changes to new score
					fprintf(pChange, "%-4d\n", score);
				}	
			}
		}
	}
	
	fclose(pChange);
}
	





bool PlayAgain(game_settings_t *game){
	char x;
	bool flag=0;
	char msg[]=("Do you wanna play again?\n[Y]\n[N]\n");
	PrintScreen(msg);
	x=ReceiveChar(4, 'y', 'Y', 'n', 'N');
	CLEANING();
	if(x=='n' || x=='N'){
		flag=0;
	}
	else{
		flag=1;
	}
	return flag;
}







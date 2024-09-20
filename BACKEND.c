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
#define LIFE 3
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30
#define TIMESTEP 200
#define TIME_MAX 30
#define NAME_MAX 50
#define SCORE_DIVIDER 20
#define SCORE_TIME_INC 1
#define SCORE_EATING 10
#define SCORE_COLLIDE 10
#define MIN_TIMESTEP 50
#define SPEED_INCREASMENT 20
#define MAX_PLAYERS 100


//define new structure
typedef struct {
    char userName[NAME_MAX];
    int score;
} player_t;

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
	FreeMem(snake.pos);
    EndGame(game);
	

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
    game->fruitX = (rand() % (game->boardWidth - 2)) + 1;  // Spawn between 1 and boardWidth - 2
    game->fruitY = (rand() % (game->boardHeight - 2)) + 1; // Spawn between 1 and boardHeight - 2
}
	


void MoveSnake(snake_t * snake, game_settings_t * game, bool * gameOver){

	input_t direction;
	while((direction= GetInput())!=NO_KEY)
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
    if(snake->pos[0].x == game->fruitX && snake->pos[0].y == game->fruitY) {
        Growth(game,snake);//what happens if a fruit is eaten??read below
    }



}
void HasCollide(game_settings_t * game, snake_t * snake, bool * gameOver){

     if(game->life>1){//checks if you sill have lifes and sets the snake as new
            --(game->life);
            (game->snakeLength)=SNAKE_LENGTH;
            FreeMem(snake->pos);
            InitializeSnake(snake,game);
            if(game->score >=SCORE_DIVIDER){//this make the score not to be negative
                game->score-=SCORE_COLLIDE;
            }
			else{
				game-> score =0;
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








//function that goes to the selected option of the menu
int CheckPlayer(game_settings_t *game){
	char msg[]=("[T] TOP SCORES\n[L] LOG IN\n[S] SIGN IN\n");
	char x;	
	PrintScreen(msg);
	x=ReceiveChar(6, 'l', 'L', 's', 'S', 't', 'T');
	if(x == 'l' || x == 'L'){
		CLEANING();
		LoginPlayer(game);
	}
	else if(x == 's' || x == 'S'){
		CLEANING();
		SignupPlayer(game);
	}
	else{
		CLEANING();
		TopScores(game);
	}
	return 0;
}



//function fo a new player to sign up
void SignupPlayer(game_settings_t *game){
	char trash[500];
	int found = 0;
	FILE* pFile;//pointer to a file
	FILE* ptrCheck;
	char msg[100]="Enter your name: ";
	PrintScreen(msg);
	
	game->userName = malloc(NAME_MAX * sizeof(char));
    if (game->userName == NULL) {
        perror("Failed to allocate memory for username");
        exit(EXIT_FAILURE);
       }
	
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
				break;
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
	free(game->userName);//free allocated memory

}



//function for a player that has already played to log in 
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
		
		game->userName = malloc(NAME_MAX * sizeof(char)); 
        if (game->userName == NULL) {
            perror("Failed to allocate memory for username");
            exit(EXIT_FAILURE);
        }
        
		ReceiveStr(game->userName);
				
		while(fgets(buffer, sizeof(buffer), ptr) != NULL){
			//stores the text that reads in the .txt and then compares it to the player name 
			if(strstr(buffer, game->userName) != NULL){
				log = 1;//user found
				break;
			}
		}
		
		fclose(ptr);
	}
	if(log){
		CLEANING();
		strcpy(msg, "Welcome back!\n");
		PrintScreen(msg); 
		AskConfiguration(game);
	}
	else{
		CLEANING();
		strcpy(msg, "User not found. Try again!\n");
		PrintScreen(msg);
		CheckPlayer(game);
	}
	free(game->userName);//free allocated memory
}


//Function to display players in order from the highiest score to the lowest
void TopScores(game_settings_t *game){
	char buffer[500];
	player_t players[MAX_PLAYERS];
	int count = 0;
	FILE *pScan = fopen("history.txt", "r");
	
	CLEANING();
	if(pScan == NULL){
		perror("Error opening file");
	} 	
	
	while(fgets(buffer, sizeof(buffer), pScan) != NULL){
		//set pointers to the user part and the score part
		char *userPtr = strstr(buffer, "USER:");
		char *scorePtr = strstr(buffer, "SCORE:");
		
		if(userPtr != NULL && scorePtr!= NULL) {
		//copies the name of the player. USER: = 5. Sets the pointer to the first character of the name
			sscanf(userPtr + 5, "%s", players[count].userName); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			sscanf(scorePtr + 6, "%d", &players[count].score);
			count++;
		}
	}	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(players, count, sizeof(player_t), ComparePlayer);
	
	PrintTopscores(game, count);
}


//function to compare two elements (scores) to use qsort function 
int ComparePlayer(const void *a, const void *b) {
    // Cast the pointers 
    const player_t *playerA = (const player_t *)a;
    const player_t *playerB = (const player_t *)b;
    return playerB->score - playerA->score;
}




//function that determines whether the playes wants to configure the game or not  
bool AskConfiguration(game_settings_t *game){
	char x;
	bool y;
	char msg[]="Would you like to configure the game?\n[Y]\n[N]\n";
	PrintScreen(msg);
	x=ReceiveChar(4, 'n', 'N', 'y', 'Y');
	
	if(x=='y' || x=='Y'){
		CLEANING();
		ConfigureGame(game);	
	}
	else{
		CLEANING();
		GameLoop(game);
		UpdateScore(game);
	}
	return 0;
}		/*y=PlayAgain(game);
		if(y){
			GameLoop(game);
			UpdateScore(game);
			CLEANING();
		}
		else{
    		EndGame(game);
    	}		
	}
}*/



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
	CleanStdin();
	char x;
	bool flag=1;
	char msg[]=("Do you wanna play again?\n[Y]\n[N]\n");
	PrintScreen(msg);
	x=ReceiveChar(4, 'y', 'Y', 'n', 'N');
	CLEANING();
	if(x=='n' || x=='N'){
		flag=0;
	}
	return flag;
}







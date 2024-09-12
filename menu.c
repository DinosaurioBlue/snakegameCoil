//startGame function is the first thing before loggin in/signing up 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"snake.h"
#include"score.h"
#include"menu.h"
#include"snake.h"
#include "input.h"
#define MIN_SIZE 4
#define MAX_SIZE 64
#define MAX_SNAKE 15
#define MIN_SNAKE 1
#define MIN_LIFE 1
#define MAX_LIFE 5
#define MIN_TIME 1
#define MAX_TIME 300


#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")
void gotoxy(int x, int y);
#else
#include<termios.h>
#define CLEAR() system("clear");
#endif

void startGame(game_settings_t * game){
	char x;
	game->configured =0;
	CLEAR();
	//the player will only be allowed to play if they press ENTER 	
	printf("SNAKE GAME  \nPress ENTER to start...\n");
	
	int temp=0;
	while(!temp){
		x = getchar();
		if(x==('\n')){
			temp =1;
		}
		else{
			printf("Please enter ENTER\n");
			cleanStdin();
		}
	}
	checkPlayer(game);
	

	
	
}
	
void checkPlayer(game_settings_t *game){
	char x;

	printf("[T] TOP SCORES\n");
	printf("[L] LOG IN\n");
	printf("[S] SIGN IN\n");
	
	
	x = getchar();
	
	if(x == 'l' || x == 'L'){
		cleanStdin();
		login(game);
	}
	else if(x == 's' || x == 'S'){
		cleanStdin();
		signUp(game);
	}
	else if(x == 't' || x == 'T'){
		cleanStdin();
		top_score(game);		
	}
	else{
		printf("Invalid option, try again\n");
		cleanStdin();
		//stays in menu
		checkPlayer(game);
	}	
	

}


//this function signs up new players
void signUp(game_settings_t *game){
	char trash[500];
	char player[NAME_MAX];
	int found = 0;
	FILE* pFile;//pointer to a file
	FILE* ptrCheck;

	
	printf("Enter your name: "); //asks for the username
	fgets(player, sizeof(player), stdin);
	player[strcspn(player, "\n")] = '\0'; // Remove newline character
	
	ptrCheck = fopen("history.txt", "r");//pointer to check if the username already exists
	if(ptrCheck == NULL){
		perror("Error opening file");
	}
	
	else{
		while(fgets(trash, sizeof(trash), ptrCheck) != NULL){
			//stores the text that reads in the .txt and then compares it to the player's name 
			if(strstr(trash, player) != NULL){
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
	
		fprintf(pFile, "USER:%s SCORE:0\n", player); 
		//writes the username and the score into the file 
		fclose(pFile);//closes the file 
	}
	
	else{
		printf("Name already used. Try again! \n");
		//goes to menu again
		checkPlayer(game);
	}

	askConfig(game, player);
}




//this function checks if the player already exists and they log in 
void login(game_settings_t *game){
	char player[NAME_MAX];
	char buffer[500]; 
	int log = 0;
	FILE *ptr = fopen("history.txt", "r");
	
	if(ptr == NULL){
		perror("Error opening file");
	} 
	
	else{
		printf("Enter your username: ");
		fgets(player, sizeof(player), stdin);
		
		//get rid of 'enter' in the player's username
		for(int i = 0; i < NAME_MAX; i++){
			if(player[i] == '\n'){
				//printf("encontre un enter!\n");
				player[i] = 0;
				//break;
			}
		}
		
		while(fgets(buffer, sizeof(buffer), ptr) != NULL){
			//stores the text that reads in the .txt and then compares it to the player name 
			if(strstr(buffer, player) != NULL){
				log = 1;//user found
			}
		}
		
		fclose(ptr);
	}
	
	if(log){
		printf("Welcome back %s\n", player);
		askConfig(game, player);
	}
	else{
		printf("User not found. Try again!\n");
		checkPlayer(game);
	}
	
	
}


/*Function to display players in order from the highiest score to the lowest*/
void top_score(game_settings_t *game){
	player_t player[NAME_MAX];
	char *name;
	char *score;
	char buffer[500];
	int count = 0, i, x;
	FILE *pScan = fopen("history.txt", "r");
	
	if(pScan == NULL){
		perror("Error opening file");
	} 	
	
	while(fgets(buffer, sizeof(buffer), pScan) != NULL){
		//set pointers to the user part and the score part
		name = strstr(buffer, "USER:");
		score = strstr(buffer, "SCORE:");
		
		if(name != NULL && score!= NULL) {
			//copies the name of the player. USER: = 5. Sets the pointer to the first character of the name
			sscanf(name + 5, "%s", player[count].user); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			sscanf(score + 6, "%d", &player[count].score);
			count++;
		}
	}
	
	
	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(player, count, sizeof(player_t), comparePlayer);
	
	//prints the player with their score in descending order
	printf("TOP SCORES: \n");
	for(i=0; i<count; i++){
		printf("%s  ->  %d\n", player[i].user, player[i].score);
	}
	printf("\n\nPress ENTER to exit\n");
	//waits for user to press enter	
	if((x=getchar()) == '\n'){		
		//then goes to menu again 
		CLEAR();
		checkPlayer(game);
	}
	
}

//function to compare two elements (scores) to use qsort function 
int comparePlayer(const void * a, const void * b){
	//converts two void pointers to type player_t 
	player_t *pA = (player_t *)a;
	player_t *pB = (player_t *)b;
	return (pB->score - pA->score);
}


//function to configure game settings
void configureGame (game_settings_t * game, char player[]){
	CLEAR();
	cleanStdin();//clearing screen and stdin

	//configurate the board
	printf("height of the board:\n");
	game->board_height=receiveInt(MIN_SIZE,MAX_SIZE);

	printf("width of the board: (recommended 1.5 times the height\n");
	game->board_width=receiveInt(MIN_SIZE,MAX_SIZE);

	cleanStdin();
	printf("Border of the board: \n");
	game->board_char=receiveChar();

	CLEAR();

	//configurate snake
	printf("How long would you like your snake to be?\n");
	cleanStdin();
	game->snake_length=receiveInt(MIN_SNAKE,MAX_SNAKE);
	
	cleanStdin();
	printf("Character of the head of the snake:\n");
	game->snake_head = receiveChar();
	
	printf("Character of the body of the snake:\n");
	cleanStdin();
	game->snake_body = receiveChar();

	CLEAR();

	//general settings
	printf("Character of the food:\n");
	cleanStdin();
	game->fruit_ch = receiveChar();

	printf("How many lives would you like to have?\n");
	cleanStdin();
	game->life=receiveInt(MIN_LIFE,MAX_LIFE);

	printf("How long would you like the timesteps to be?\n");
	cleanStdin();
	game->snake_length=receiveInt(MIN_TIME,MAX_TIME);


	//end of configuration
	CLEAR();
	cleanStdin();
	//a flag so the game knows that its configurated, otherwise it would use default settings
	game->configured =1;
	snakeGame(game);
	updateScore(game, player);
		
}

void askConfig(game_settings_t*game, char player[]){
	int x;
	printf("Would you like to configure the game?\n");
	printf("[Y]\n[N]\n");
	
	x=getchar();
	if(x=='Y' || x== 'y'){
		CLEAR();
		configureGame(game, player);
		
	}
	else if(x=='N' || x== 'n'){
		CLEAR();
		snakeGame(game);
		updateScore(game, player);
	}
	else{
		printf("Invalid option, try again!\n");
		CLEAR();		
		askConfig(game, player);
	}
}





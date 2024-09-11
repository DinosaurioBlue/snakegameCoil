//startGame function is the first thing before loggin in/signing up 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"snake.h"
#include"score.h"
#include"menu.h"
#include"snake.h"
#define MIN_SIZE 4
#define MAX_SIZE 64
#define MAX_SNAKE 15
#define MIN_SNAKE 1
#define MIN_LIFE 1
#define MAX_LIFE 5
#define MIN_TIME 1
#define MAX_TIME 200

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
	
	
	x = getchar();
	
	/*while(x != '\n' ){
		printf("Press ENTER to start\n");
		x = getchar();
	}*/
	if(x == '\n'){
		checkPlayer(game);
	}
	cleanStdin();
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
	int flag =0;
	int * temp = (int*)malloc(sizeof(int));
	
	CLEAR();
	
	//Configurate board
	printf("how tall would you like the board to be?\n");
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
			cleanStdin();
		}
		else if((temp<MIN_SIZE)||(temp>MAX_SIZE)){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
		}
		else{
			game->board_height = *(temp);
			flag++;
		}
	}
	flag = temp =0;//restarting values
	printf("how wide would you like the board to be?\n");//wide
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
			cleanStdin();
		}
		else if((temp<MIN_SIZE)||(temp>MAX_SIZE)){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
		}
		else{
			game->board_width = *(temp);
			flag++;
		}
		
		
	}
	printf("what character would you like your board to use?\n");//border character
	cleanStdin();
	temp = getchar();
	game->board_char = (char)(*(temp));	

	//configure snake
	CLEAR();
	printf("what character would you like the head of snake to be?\n");//snake head
	cleanStdin();
	temp = getchar();
	game->snake_head = (char)(*(temp));	

	printf("what character would you like the body of snake to be?\n");//snake body
	cleanStdin();
	temp = getchar();
	game->snake_body= (char)(*(temp));

	printf("how long would you like your snake to be?\n");//initial snake size
	flag = temp =0;//restarting values
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_SNAKE,MAX_SNAKE);
			cleanStdin();
		}
		else if((temp<MIN_SNAKE)||(temp>MAX_SNAKE)){
			printf("please enter an integer from %d to %d\n",MIN_SNAKE,MAX_SNAKE);
		}
		else{
			game->snake_length = *(temp);
			flag++;
		}
	}
	



	//configure foood
	CLEAR();
	printf("what character would you like the food to be?\n");//food apearrence
	cleanStdin();
	temp = getchar();
	game->fruit_ch= (char)(*(temp));

	//general game settings	
	printf("how many lifes would you like to have?\n");//initial lifes
	flag = temp =0;//restarting values
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_LIFE,MAX_LIFE);
			cleanStdin();
		}
		else if((temp<MIN_LIFE)||(temp>MAX_LIFE)){
			printf("please enter an integer from %d to %d\n",MIN_LIFE,MAX_LIFE);
		}
		else{
			game->life = *(temp);
			flag++;
		}
	}
	
	printf("how many many miliseconds would you like the timestep to be?\n");//time step
	flag = temp =0;//restarting values
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_TIME,MAX_TIME);
			cleanStdin();
		}
		else if((temp<MIN_TIME)||(temp>MAX_TIME)){
			printf("please enter an integer from %d to %d\n",MIN_TIME,MAX_TIME);
		}
		else{
			game->timestep = *(temp);
			flag++;
		}
	}

	game->configured =1;
	cleanStdin();
	snakeGame(game);
	updateScore(game, player);
		
}
void cleanStdin(void){
	int temp;
	while((temp = getchar())!='\n' && temp !=EOF);//clear the buffer
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





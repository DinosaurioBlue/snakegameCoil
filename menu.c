//startGame function is the first thing before loggin in/signing up 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"snake.h"
#include"score.h"
#include"menu.h"

void startGame(game_settings_t * game){
	char x;
	
	//the player will only be allowed to play if they press ENTER 	
	printf("SNAKE GAME  \nPress ENTER to start...\n");
	fflush(stdout);
	
	
	x = getchar();
	while(x != '\n' ){
		printf("Press ENTER to start\n");
		fflush(stdout);
		x = getch();
	}
	if(x == '\n'){
		checkPlayer(game);
	}
}
	
void checkPlayer(game_settings_t *game){
	char x;

	printf("[T] TOP SCORES\n");
	printf("[L] LOG IN\n");
	printf("[S] SIGN IN\n");
	fflush(stdout);	
	
	x = getchar();
	
	if(x == 'l' || x == 'L'){
		login(game);
	}
	else if(x == 's' || x == 'S'){
		signUp(game);
	}
	else if(x == 't' || x == 'T'){
		top_score(game);		
	}
	else{
		printf("Invalid option, try again\n");
		fflush(stdout);
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
	fflush(stdout);
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
		fflush(stdout);
		//goes to menu again
		checkPlayer(game);
	}

	//game logics
	snakeGame(game);
	updateScore(game, player);
	kill_game();	

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
		printf("Enter yout username: ");
		fflush(stdout);
		fgets(player, sizeof(player), stdin);
		player[strcspn(player, "\n")] = '\0';
		
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
		fflush(stdout);
	}
	else{
		printf("User not found. Try again!\n");
		fflush(stdout);
		checkPlayer(game);
	}
	
	snakeGame (game);
	updateScore(game, player);
	kill_game();
			
}


/*Function to display players in order from the highiest score to the lowest*/
void top_score(game_settings_t *game){
	player_t player[NAME_MAX];
	char *name;
	char *score;
	char buffer[500];
	int count = 0, i;
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
	fflush(stdout);
	for(i=0; i<count; i++){
		printf("%s  ->  %d\n", player[i].user, player[i].score);
	}
	fflush(stdout);

	printf("\n\nPress ENTER to exit\n");
	fflush(stdout);
	
	//waits for user to press enter	
	while(getch() != '\n');
	
	//then goes to menu again 
	checkPlayer(game);
	
}

//function to compare two elements (scores) to use qsort function 
int comparePlayer(const void * a, const void * b){
	//converts two void pointers to type player_t 
	player_t *pA = (player_t *)a;
	player_t *pB = (player_t *)b;
	return (pB->score - pA->score);
}









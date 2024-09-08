//startGame function is the first thing before loggin in/signing up 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"score.h"
#include"menu.h"

//void snakeGame (game_settings_t * game);//main game loop
//void kill_game(void);//end ncurses mode
/*
#include<termios.h>
*
*system("clear");
*/

/*#include<windows.h
*
*system("cls");
*/
/*Here it changes wether you are in linux or windows
*#ifdef WINDOWS
*#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")
void gotoxy(int x, int y);
#else
#include<termios.h>
#define CLEAR() system("clear")
#endif
*/
void startGame(void){
	char x;
	
		//the player will only be allowed to play if they press ENTER 	
	printf("SNAKE GAME  \nPress ENTER to start...\n");
	
	x = getchar();
	while(x != '\n' ){
		print("Press ENTER to start\n");
		x = getchar();
	}
	if(x == '\n'){
		checkPlayer();
	}
}
	
void checkPlayer(void){
	char x;

	print("Press 't' to see the scores\n");
	print("Press 'l' if you already played\n");
	print("Press 's' if you are new here\n");
	x = getchar();
	
	if(x == 'l'){
		login();
	}
	else if(x == 's'){
		signUp();
	}
	else if(x == 't'){
		top_score();		
	}
	else{
		printf("Invalid option, try again\n");
		//stays in menu
		checkPlayer();
	}	

}


//this function signs up new players
void signUp(void){
	char trash[500];
	char player[NAME_MAX];
	int found = 0;
	FILE* pFile;//pointer to a file
	FILE* ptrCheck;

	
	printf("Enter your name: "); //asks for the username
	getstr(player);
	
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
		print("Name already used. Try again! \n");
		//goes to menu again
		checkPlayer();
	}
	
	
	/*
	PLAY FUNCTION
	SCORE OF PLAYER
	*/
	
	
	/*updateScore(520, player);*/
	
}




//this function checks if the player already exists and they log in 
void login(void){
	char player[NAME_MAX];
	char buffer[500]; 
	int log = 0;
	FILE *ptr = fopen("history.txt", "r");
	
	if(ptr == NULL){
		perror("Error opening file");
	} 
	
	else{
		printf("Enter yout username: ");
		getstr(player);
		
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
	}
	else{
		print("User not found. Try again!\n");
		checkPlayer();
	}
	
	/*
	PLAY FUNCTION
	SCORE OF PLAYER
	*/
	
	updateScore(120, player);
	
	
}


/*Function to display players in order from the highiest score to the lowest*/
void top_score(void){
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
		
		if((name != NULL) && (score!= NULL)) {
			//copies the name of the player. USER: = 5. Sets the pointer to the first character of the name
			scanf(name + 5, "%s", player[count].user); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			scanf(score + 6, "%d", &player[count].score);
			count++;
		}
	}
	
	
	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(player, count, sizeof(player_t), comparePlayer);
	
	clear();
	//prints the player with their score in descending order
	printf("TOP SCORES: \n");
	for(i=0; i<count; i++){
		printf("%s  ->  %d\n", player[i].user, player[i].score);
	}

	printf("\n\nPress ENTER to exit\n");
	
	//waits for user to press enter	
	while(getchar() != '\n');
	
	//then goes to menu again 
	checkPlayer();
	
}

//function to compare two elements (scores) to use qsort function 
int comparePlayer(const void * a, const void * b){
	//converts two void pointers to type player_t 
	player_t *pA = (player_t *)a;
	player_t *pB = (player_t *)b;
	return (pB->score - pA->score);
}












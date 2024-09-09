//startGame function is the first thing before loggin in/signing up 
#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include"score.h"
#include"menu.h"

#ifdef WINDOWS
	#include<windows.h>
	#include<conio.h>
	#define CLEAR() system("cls")
	void gotoxy(int x, int y);
#else
	#include<termios.h>
	#define CLEAR() system("clear")
#endif


void startGame(game_settings_t * game){
	char x;
	
	//initializes ncurses screen
	initscr();
	noecho();
	cbreak();
	
	//the player will only be allowed to play if they press ENTER 	
	printw("SNAKE GAME  \nPress ENTER to start...\n");
	refresh();
	//drawTitle();
	
	x = getch();
	while(x != '\n' ){
		printw("Press ENTER to start\n");
		x = getch();
	}
	if(x == '\n'){
		checkPlayer();
	}
}
	
void checkPlayer(void){
	char x;

	printw("[t] TOP SCORES\n");
	printw("[l] LOG IN\n");
	printw("[s] SIGN IN\n");
	x = getch();
	
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
		printw("Invalid option, try again\n");
		refresh();
		//satays in menu
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

	
	printw("Enter your name: "); //asks for the username
	refresh();
	echo();
	getstr(player);
	noecho();
	
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
		printw("Name already used. Try again! \n");
		refresh();
		//goes to menu again
		checkPlayer();
	}

	snakeGame (&game);
	updateScore(520, player);
	kill_game();

	
	
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
		printw("Enter yout username: ");
		refresh();
		echo();
		getstr(player);
		noecho();
		
		while(fgets(buffer, sizeof(buffer), ptr) != NULL){
			//stores the text that reads in the .txt and then compares it to the player name 
			if(strstr(buffer, player) != NULL){
				log = 1;//user found
			}
		}
		
		fclose(ptr);
	}
	
	if(log){
		printw("Welcome back %s\n", player);
		refresh();
	}
	else{
		printw("User not found. Try again!\n");
		refresh();
		checkPlayer();
	}
	
	snakeGame (&game);
	updateScore(120, player);
	kill_game();
	
		
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
			sscanf(name + 5, "%s", player[count].user); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			sscanf(score + 6, "%d", &player[count].score);
			count++;
		}
	}
	
	
	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(player, count, sizeof(player_t), comparePlayer);
	
	clear();
	//prints the player with their score in descending order
	printw("TOP SCORES: \n");
	for(i=0; i<count; i++){
		printw("%s  ->  %d\n", player[i].user, player[i].score);
	}
	refresh();

	printw("\n\nPress ENTER to exit\n");
	refresh();
	
	//waits for user to press enter	
	while(getch() != '\n');
	
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









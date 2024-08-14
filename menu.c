//startGame function is the first thing before loggin in 
#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include"score.h"
#include"menu.h"
#include"topscore.h"

char x;

void startGame(void){

	
	//initializes ncurses screen
	initscr();
	noecho();
	cbreak();
	
	//the player will only be allowed to play if they press ENTER 	
	printw("SNAKE GAME  \nPress ENTER to start...\n");
	refresh();
	
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
	printw("Press 't' to see the scores\n");
	printw("Press 'l' if you already played\n");
	printw("Press 's' if you are new here\n");
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
		printw("Name already used. Choose another player: \n");
		refresh();
		signUp();
	}
	
	
	/*
	PLAY FUNCTION
	SCORE OF PLAYER
	*/
	
	
	updateScore(520, player);
	
}




//this function checks if the player already exists and they log in with previous score
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
	
	if(log!=0){
		printw("Welcome back %s\n", player);
		refresh();
	}
	else{
		printw("User not found. Please, try again\n");
		refresh();
		checkPlayer();
	}
	
	/*
	PLAY FUNCTION
	SCORE OF PLAYER
	*/
	
	updateScore(5568, player);
	
	
}












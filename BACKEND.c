/*This source code makes all the backend, user doesn't see nothingh from here*/

//general includes
#include"GENERAL.h"
#include"BACKEND.h"
#include"FRONTEND.h"
#include<stdio.h>
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
}
void SetupBack(game_settings_t * game){
    game->score =0;

    if(!game->configured){
        game->boardHeight = BOARD_HEIGHT;
        game->boardWidth = BOARD_WIDTH;
        game->life= LIFE;
        game->snakeLength= SNAKE_LENGTH;
        game->timeStep= TIMESTEP;
        
    }



}




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
		cleanStdin();
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
		AskConfiguration(game, game->userName);
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




//function to compare two elements (scores) to use qsort function 
int comparePlayer(const void * a, const void * b){
	//converts two void pointers to type player_t 
	player_t *pA = (player_t *)a;
	player_t *pB = (player_t *)b;
	return (pB->score - pA->score);
}



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










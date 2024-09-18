#include<stdio.h>


//function that starts the menu
void StartMenu(game_settings_t *game){
	char x;
	game->configured = 0;
	//funcion q imprime
	if(//funcione q pide char){
		CheckPlayer(game_settings_t *game);
	}
}



//function that goes to the selected option of the menu
void CheckPlayer(game_settings_t *game){
	//funcion q imprime 
	x=//funcion q pide char
	if(x == 'l' || x == 'L'){
		cleanStdin();
		LoginPlayer(game_settings_t *game);
	}
	else if(x == 's' || x == 'S'){
		cleanStdin();
		SignupPlayer(game_settings_t *game);
	}
	else if(x == 't' || x == 'T'){
		cleanStdin();
		TopScores(game_settings_t *game);		
	}
	else{
		//funcion q imprime 
		cleanStdin();
		//stays in menu
		checkPlayer(game_settings_t *game);
	}
	AskConfiguration(game_settings_t *game, game->userName);
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
		CheckPlayer(game_settings_t *game);
	
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
		game->userName=//funcion que pide string
		
		//get rid of 'enter' in the player's username
		for(int i = 0; i < NAME_MAX; i++){
			if(game->userName[i] == '\n'){
				game->userName[i] = 0;
			}
		}
		
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
		AskConfiguration(game_settings_t *game, game->userName);
	}
	else{
		//funcion que imprime
		CheckPlayer(game_settings_t *game);
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
			sscanf(name + 5, "%s", game->userName); 
			//copies the score of the player. SCORE: = 6. Sets the pointer to the number 
			sscanf(score + 6, "%d", game->score);
			count++;
		}
	}
	
	
	
	fclose(pScan);	
	
	
	//sort players by score
	qsort(game->userName, count, sizeof(game_settings_t), ComparePlayer);

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










/*Function that updates a user's score if he got a higher one*/

#include<stdio.h>
#include<string.h>
#include"score.h"


void updateScore(int score, const char *player){
	char buffer[200];
	char *scorePosition;
	int old_score;
	unsigned long int position;
	FILE *pChange = fopen("history.txt", "r+");
	
	if(pChange == NULL){
		perror("Failed to open file");
	}
	
//read each line and if it encounters the name of the player it changes their score to the udated one (only if they got a better one)
	while(fgets(buffer, sizeof(buffer), pChange) != NULL){
		if(strstr(buffer, player) != NULL){
			position = ftell(pChange);
			scorePosition = strstr(buffer, "SCORE:");
			sscanf(scorePosition, "%d", old_score);  
			if(scorePosition){ 
			//sets the pointer in the right position to change the player's score 
				fseek(pChange, position - strlen(buffer) + (scorePosition - buffer) + 6, SEEK_SET);
				if(score > old_score){    
					fprintf(pChange, "%-4d\n", score);
				}	
			}
		}
	}
	
	fclose(pChange);
}
	




	
	
	
	
	
	
	
	
	


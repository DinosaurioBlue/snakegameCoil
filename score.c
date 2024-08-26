/*Function that updates a user's score if he got a higher one*/

#include<stdio.h>
#include<string.h>
#include<ncurses.h>
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
	
//Read each line and update the player's score if it's higher than the old one
	while(fgets(buffer, sizeof(buffer), pChange) != NULL){
		if(strstr(buffer, player) != NULL){
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
	




	
	
	
	
	
	
	
	
	


/*Function to display players in order the highiest score to the lowest*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include"score.h"
#include"topscore.h"
#include"menu.h"

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

	printw("\n\n\nPress ENTER to exit\n");
	refresh();
	while(getch() != '\n');
	
	checkPlayer();
	
}

//function to compare two elements (scores) to use qsort function 
int comparePlayer(const void * a, const void * b){
	//converts two void pointers to type player_t 
	player_t *pA = (player_t *)a;
	player_t *pB = (player_t *)b;
	return (pB->score - pA->score);
}











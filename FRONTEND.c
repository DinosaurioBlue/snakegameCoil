/*This is source code for frontend*/


//general inlcudes
#include"GENERAL.h"
#include"BACKEND.h"


//conditional compilation
#ifndef USERNAME
#define USERNAME
#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")//clearing terminal
#define CLEANING() system("cls") 
void gotoxy(int x, int y);//definition of funciton
#define ERR -1// error code
#else
#include<ncurses.h>
#include<termios.h>
#define CLEANING() system("clear")//termios.h
#define CLEAR() clear()//ncurses.h
#endif



//macros
#define LOWCASE(c) ('a'<=(c) && (c)<='z' ? (c) : ((c)+'A'-'a') )


//defines
#define MAX_NAME 50
#define SNAKE_HEAD '@'
#define SNAKE_BODY 'O'
#define FRUIT_CH 'F'
#define BORDER_CHAR '#'








//functions definitions

#ifdef WINDOWS//moves cursor
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif


//prints the whole game 
void Draw(game_settings_t* game,snake_t*snake){



    CLEAR();
    int i;
    //printing borders
    #ifndef WINDOWS
    for (i = 0; i < game->boardWidth + 2; i++) {
        mvprintw(0, i, "%C",game->boardChar);
        mvprintw(game->boardHeight + 1, i, "%C",game->boardChar);
    }
    for (i = 0; i < game->boardHeight + 2; i++) {
        mvprintw(i, 0, "%C",game->boardChar);
        mvprintw(i, game->boardWidth + 1, "%C",game->boardChar);
    }
    //printing score and life
    mvprintw(game->boardHeight+4,0,"your score is:%d",game->score);
    mvprintw(game->boardHeight+5,0,"your lifes are:%d",game->life);

    //printing snake
    mvprintw(snake->pos[0].y,snake->pos[0].x,"%C",game->snakeHead);
    for(i=1;i<snake->length;++i){
        mvprintw(snake->pos[i].y,snake->pos[i].x,"%C",game->snakeBody);
    }

    //printing fruit
    mvprintw(game->fruitCoord.y, game->fruitCoord.x, "%C", game->fruitCh);



    #else//windows draw's function
    for (i = 0; i < game->boardWidth + 2; i++) {
        gotoxy(i, 0);
        printf("%C",);
        gotoxy(i, game->boardHeight + 1);
        printf("%C",game->boardChar);
    }
    for (i = 0; i < game->boardHeight + 2; i++) {
        gotoxy(0, i);
        printf("%C",game->boardChar);
        gotoxy(game->boardWidth + 1, i);
        printf("%C",game->boardChar);
    }

    // Printing score and life
    gotoxy(0, game->boardHeight + 3);
    printf("Score: %d", game->score);
    gotoxy(0, game->boardHeight + 4);
    printf("Lives: %d", game->life);

    // Printing snake
    gotoxy(snake->pos[0].x, snake->pos[0].y);
    printf("%C", game->snake_head);
    for(i=1; i<snake->length; ++i){
        gotoxy(snake->pos[i].x, snake->pos[i].y);
        printf("%C", game->snakeBody);
    }

    // Printing fruit
    gotoxy(game->fruit_x, game->fruit_y);
    printf("%C",game->fruitCh);
    #endif
}

input_t GetInput(void){
    int ch;
    
    #ifdef WINDOWS

    if(kbhit()) {//this is to make the game not to be paused every time it gets here
             
    }   
   #endif


   do {
    ch = getch();
    switch(ch) {
    case 'W':
    case 'w':   return UP;  break;
    case 'S':
    case 's':   return DOWN;    break;
    case 'A':
    case 'a':   return LEFT;    break;
    case 'D':
    case 'd':   return RIGHT;   break;
    case 'Q':
    case 'q':   return QUIT;    break;
    case 'p':
    case 'P':   return PAUSE;   break;
    case 'r':
    case 'R':   return RESTART; break;
    default:    ch = ERR;   break;
    }
    } while (ch != ERR);
}

void CleanStdin(void){
	int temp;
	while((temp = getchar())!='\n' && temp !=EOF);//clear the buffer
}



void SetupFront (game_settings_t * game){
    #ifndef WINDOWS
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input
    curs_set(0); // Hide the cursor
    nodelay(stdscr,TRUE);
    #endif


    if(!game->configured){
        game->boardChar = BORDER_CHAR;
        game->fruitCh=FRUIT_CH;
        game->snakeBody= SNAKE_BODY;
        game->snakeHead=SNAKE_HEAD;
    CLEAR();
    }
}

void KillScreen (void){//only at the end of ncurses mode
    #ifndef WINDOWS
    endwin();
    curs_set(1);
    #endif
    CLEANING();//TERMIOS CALL IF YOU ARE ON LINUX
}

void updateScore(game_settings_t *game, const char *player){
	char buffer[200];
	char *scorePosition;
	int old_score;
	int score = game->score;
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

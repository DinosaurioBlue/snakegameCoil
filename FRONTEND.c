/*This is source code for frontend*/


//general inlcudes
#include"GENERAL.h"
#include"BACKEND.h"
#include<stdlib.h>
#include<unistd.h>

//conditional compilation
#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")//clearing terminal
#define CLEANING() system("cls") 
void GoToxy(int x, int y);//definition of funciton
#define ERR -1// error code
#else
#include<ncurses.h>
#include<termios.h>
#define CLEANING() system("clear")//termios.h
#define CLEAR() clear()//ncurses.h
#endif


//defines
#define NAME_MAX 50
#define SNAKE_HEAD '@'
#define SNAKE_BODY 'O'
#define FRUIT_CH 'F'
#define BORDER_CHAR '#'
#define MIN_SNAKE 1
#define MAX_SNAKE 15
#define MIN_LIFE 1
#define MAX_LIFE 5
#define MIN_TIME 50
#define MAX_TIME 300
#define MIN_SIZE 4
#define MAX_SIZE 64








//functions definitions

#ifdef WINDOWS//moves cursor
void GoToxy(int x, int y) {
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
    mvprintw(game->boardHeight+5,0,"your lives are:%d",game->life);

    //printing snake
    mvprintw(snake->pos[0].y,snake->pos[0].x,"%C",game->snakeHead);
    for(i=1;i<snake->length;++i){
        mvprintw(snake->pos[i].y,snake->pos[i].x,"%C",game->snakeBody);
    }

    //printing fruit
    mvprintw(game->fruitY, game->fruitX, "%C", game->fruitCh);



    #else//windows draw's function
    for (i = 0; i < game->boardWidth + 2; i++) {
        GoToxy(i, 0);
        printf("%C",);
        GoToxy(i, game->boardHeight + 1);
        printf("%C",game->boardChar);
    }
    for (i = 0; i < game->boardHeight + 2; i++) {
        GoToxy(0, i);
        printf("%C",game->boardChar);
        GoToxy(game->boardWidth + 1, i);
        printf("%C",game->boardChar);
    }

    // Printing score and life
    GoToxy(0, game->boardHeight + 3);
    printf("Score: %d", game->score);
    GoToxy(0, game->boardHeight + 4);
    printf("Lives: %d", game->life);

    // Printing snake
    GoToxy(snake->pos[0].x, snake->pos[0].y);
    printf("%C", game->snake_head);
    for(i=1; i<snake->length; ++i){
        GoToxy(snake->pos[i].x, snake->pos[i].y);
        printf("%C", game->snakeBody);
    }

    // Printing fruit
    GoToxy(game->fruit_x, game->fruit_y);
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
    default:					break;
    }
    } while (ch != ERR);
	return NO_KEY;
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
    nocbreak();
    echo();
	curs_set(1);
    endwin();
    #endif
    //CLEANING();//TERMIOS CALL IF YOU ARE ON LINUX
}

//functions that prints on screen 
void PrintScreen(const char *string){
	printf("%s\n", string);
}


//function for the user to press ENTER
void ReceiveEnter(void){
	int temp=0;
	char x;
	while(!temp){
		x = getchar();
		if(x==('\n')){
			temp =1;
		}
		else{
			printf("Please press ENTER\n");
			CleanStdin();
		}
	}
}


//function to receive specific chars from user
char ReceiveChar(int num_chars, ...){
	int temp=0;
	char x, valid_char;
	
	va_list args;
	
	while(!temp){
		x=getchar();
		CleanStdin();
		
		va_start(args, num_chars);
		
		for (int i = 0; i < num_chars; i++) {
            valid_char = va_arg(args, int);
            if(x==valid_char){
				temp=1;
			}
		}
		
		va_end(args);
		
		if(!temp){
			printf("Invalid option. Try Again!\n");
		}
	}
	return x;
}


	
//function to receive a string from user	
void ReceiveStr(char *str){
	int i;
	fgets(str, NAME_MAX, stdin);
	//get rid of 'enter' in string
	for(i=0; i<NAME_MAX; i++){
		if(str[i]=='\n'){
			str[i]='\0';
		}
	}
}




void startGame(game_settings_t * game){
	char x;
	game->configured =0;
	CLEAR();
	//the player will only be allowed to play if they press ENTER 	
	printf("SNAKE GAME  \nPress ENTER to start...\n");
	
	int temp=0;
	while(!temp){
		x = getchar();
		if(x==('\n')){
			temp =1;
		}
		else{
			printf("Please press ENTER\n");
			CleanStdin();
		}
	}
	CheckPlayer(game);



}

//function that prints the player with their score in descending order
void PrintTopscores(game_settings_t *game, int cantPlayers){
	int i;
	printf("TOP SCORES: \n");
	for(i=0; i<cantPlayers; i++){
		printf("%s  ->  %d\n", game->userName, game->score);
	}
	printf("\n\nPress ENTER to exit\n");
	ReceiveEnter();		
	//then goes to menu again 
	CLEAR();
	CheckPlayer(game);
}




/***********************************************************
*														   *
*      function to configure the game settings             *
* 														   *
***********************************************************/
void ConfigurationPlayer(game_settings_t * game){
	int flag =0;
	int temp;	
	CLEAR();
	
	//Configurate board
	
	//board height
	printf("how tall would you like the board to be?\n");
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
			CleanStdin();
		}
		else if((temp<MIN_SIZE)||(temp>MAX_SIZE)){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
		}
		else{
			game->boardHeight = (temp);
			flag++;
		}
	}
	
	//board width
	flag = temp =0;	//restarting values
	printf("how wide would you like the board to be?\n");
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
			CleanStdin();
		}
		else if((temp<MIN_SIZE)||(temp>MAX_SIZE)){
			printf("please enter an integer from %d to %d\n",MIN_SIZE,MAX_SIZE);
		}
		else{
			game->boardWidth = (temp);
			flag++;
		}
		
		
	}

	//border character
	printf("what character would you like your board to use?\n");
	CleanStdin();
	flag =0;
	while(!flag){
		temp = getchar();
		if(('!'<=temp)&&(temp<='~')){
			++flag;
		}
		else{
			printf("Please enter a valid character");
			CleanStdin();
		}
	}
	game->boardChar = (char)(temp);	

	//configure snake
	
	//snake head
	CLEAR();
	printf("what character would you like the head of snake to be?\n");
	CleanStdin();
	flag =0;
	while(!flag){
		temp = getchar();
		if(('!'<=temp)&&(temp<='~')){
			++flag;
		}
		else{
			printf("Please enter a valid character");
			CleanStdin();
		}
	}
	game->snakeHead = (char)(temp);	

	//snake body
	printf("what character would you like the body of snake to be?\n");
	CleanStdin();
	flag =0;
	while(!flag){
		temp = getchar();
		if(('!'<=temp)&&(temp<='~')){
			++flag;
		}
		else{
			printf("Please enter a valid character");
			CleanStdin();
		}
	}
	game->snakeBody= (char)(temp);

	//initial snake size
	printf("how long would you like your snake to be?\n");
	flag = temp =0; //restarting values
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_SNAKE,MAX_SNAKE);
			CleanStdin();
		}
		else if((temp<MIN_SNAKE)||(temp>MAX_SNAKE)){
			printf("please enter an integer from %d to %d\n",MIN_SNAKE,MAX_SNAKE);
		}
		else{
			game->snakeLength = (temp);
			flag++;
		}
	}
	

	//configure foood
	
	//food apearrence
	CLEAR();
	printf("what character would you like the food to be?\n");
	CleanStdin();
	flag =0;
	while(!flag){
		temp = getchar();
		if(('!'<=temp)&&(temp<='~')){
			++flag;
		}
		else{
			printf("Please enter a valid character");
			CleanStdin();
		}
	}
	game->fruitCh= (char)(temp);

	//general game settings	
	
	//initial lifes
	printf("how many lifes would you like to have?\n");
	flag = temp =0;//restarting values
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_LIFE,MAX_LIFE);
			CleanStdin();
		}
		else if((temp<MIN_LIFE)||(temp>MAX_LIFE)){
			printf("please enter an integer from %d to %d\n",MIN_LIFE,MAX_LIFE);
		}
		else{
			game->life = (temp);
			flag++;
		}
	}
	
	//time step
	printf("how many many miliseconds would you like the timestep to be?\n");
	flag = temp =0;//restarting values
	while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",MIN_TIME,MAX_TIME);
			CleanStdin();
		}
		else if((temp<MIN_TIME)||(temp>MAX_TIME)){
			printf("please enter an integer from %d to %d\n",MIN_TIME,MAX_TIME);
		}
		else{
			game->timeStep = (temp);
			flag++;
		}
	}
	CLEAR();
	game->configured=1;
	CleanStdin();		
}



/***********************************************************
*														   *
*                function to end the game                   *
* 														   *
***********************************************************/
int EndGame(game_settings_t * game){//end messagge and deallocates memory
    #ifdef WINDOWS
	system("cls");
    GoToxy(0,0);
    printf("Game Over! Your score was %d\n", game->score);
	sleep(2000);
	system("cls");
    #else
	clear();
    mvprintw(0,0,"Game Over! Your score was %d\n", game->score);
    refresh();
    curs_set(1);
	napms(2000);
	clear();
	#endif
	KillScreen();
	return 0;
	
}

/*This is source code for frontend*/

#include"GENERAL.h"


//conditional compilation
#ifdef WINDOWS
#include<windows.h>
#include<conio.h>
#define CLEAR() system("cls")//clearing terminal
#define CLEAN() system("cls") 
void gotoxy(int x, int y);//definition of funciton
#define ERR -1// error code
#else
#include<ncurses.h>
#include<termios.h>
#define CLEAR() system("clear")//termios.h
#define CLEAN() clear()//ncurses.h
#endif
//general inlcudes



#define LOWCASE(c) ('a'<=(c) && (c)<='z' ? (c) : ((c)+'A'-'a') )








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

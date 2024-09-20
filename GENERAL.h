/*This file defines general information that the whole project will need*/


#ifndef GENERAL_H
#define GENERAL_H

//includes
#include<time.h>
#include<stdbool.h>






//struct definitions

typedef struct
{
     int x;
     int y;
}vector_t;


typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PAUSE,
    RESTART,
    NO_KEY,
    QUIT,
    WRONG_KEY
} input_t;



//define new structure
typedef struct {
    char * userName;
    char snakeHead;
    char snakeBody;
    char boardChar;
    char fruitCh;
    unsigned int score;
    unsigned int life;
    unsigned int snakeLength;
    unsigned int boardHeight;
    unsigned int boardWidth;
    unsigned int fruitX;
    unsigned int fruitY;
    unsigned int timeStep;
    bool configured;
    bool    restarted;
    time_t  gameTime;
} game_settings_t;


#define NAME_MAX 50
typedef struct {
    char userName[NAME_MAX];
    int score;
} player_t;



typedef struct {
    vector_t * pos;
    vector_t dir;
    unsigned int length;
} snake_t;
#endif
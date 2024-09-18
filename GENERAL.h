/*This file defines general information that the whole project will need*/


#ifndef GENERAL_H
#define GENERAL_H

//includes
#include<time.h>
#include<stdbool.h>






//struct definitions

typedef struct
{
    unsigned int x;
    unsigned int y;
}vector_t;


typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PAUSE,
    RESTART,
} input_t;



typedef struct {
    const char * userName;
    char snakeHead;
    char snakeBody;
    char boardChar;
    char fruitCh;
    unsigned int score;
    unsigned int life;
    unsigned int snakeLength;
    unsigned int boardHeight;
    unsigned int boardWidth;
    vector_t fruitCordinate;
    unsigned int timeStep;
    _Bool configured;
    time_t  gameTime;
} game_settings_t;




typedef struct {
    vector_t * pos;
    vector_t dir;
    unsigned int length;
} snake_t;
#endif
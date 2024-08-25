//includes 
#include"snake.h"
#include"menu.h"


//developing parameters
#define DEVELOPING 1
#if DEVELOPING==1
#define BHEIGHT 20
#define BWIDTH  40
#define HEAD    '@'
#define BODY    'o'
#define SIZE    1
#define NAME "jorge"





#endif  





//main function
int main (void){
    //setting game parameters
     game_setup();

    game_settings_t game;
    game_settings_t * p2game=&game;
    game.board_height=BHEIGHT;
    game.board_width= BWIDTH;
    game.snake_body=BODY;
    game.snake_head= HEAD;
    game.user_name=NAME;
    game.snake_length = SIZE;
    game.fruit_ch ='*';
    game.fruit_x =6;
    game.fruit_y =6;
    game.speed=200;


    //then the game is started 
    start_game(p2game);
   



    kill_game();
    
    printf("your score was %d\n",game.score);




   return 0;
}

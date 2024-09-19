/*Esta funcion pertenece a frontend, y lo que hace es entregar un tipo de dato imput_t que se define con enum*/

//Estructura que enumera inputs
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


/*FUNCION QUE CAUSA PROBLEMA*/
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

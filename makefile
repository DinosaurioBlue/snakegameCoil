snake: main.o FRONTEND.o BACKEND.o 
	gcc -Wall -o snake main.o FRONTEND.o BACKEND.o  -lncurses

main.o: main.c snake.h score.h menu.h
	gcc -Wall -c main.c

snake.o: snake.c snake.h
	gcc -Wall -c snake.c
	
menu.o: menu.c menu.h
	gcc -Wall -c menu.c

score.o: score.c score.h
	gcc -Wall -c score.c

clean:
	rm -rf *.o 
	rm snake
	rm s
#every target starting with 'w' is for compiling in windows only
wsnake: wmain.o wsnake.o wmenu.o wscore.o 
	gcc -Wall -o wsnake wmain.o wsnake.o wmenu.o wscore.o 

wmain.o: main.c snake.h menu.h score.h
	gcc -Wall -c -o wmain.o main.c

wsnake.o: snake.c snake.h
	gcc -D WINDOWS -Wall -c -o wsnake.o snake.c
	
wmenu.o: menu.c menu.h
	gcc -D WINDOWS -Wall -c -o wmenu.o menu.c

wscore.o: score.c score.h
	gcc -D WINDOWS -Wall -c -o wscore.o score.c

wclean:
	rm -rf *.o 
	rm wsnake

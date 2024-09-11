snake: main.o snake.o menu.o score.o
	gcc -Wall -o snake main.o snake.o menu.o score.o -lncurses

main.o: main.c snake.h
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
#every target starting with 'w' is for compiling in windows only
wsnake: wmain.o wsnake.o wmenu.o wscore.o
	gcc -Wall -o wsnake wmain.o wsnake.o wmenu.o wscore.o

wmain.o: main.c snake.h
	gcc -Wall -c -o wmain.o main.c

snake.o: snake.c snake.h
	gcc -Wall -c snake.c
	
menu.o: menu.c menu.h
	gcc -Wall -c menu.c

score.o: score.c score.h
	gcc -Wall -c score.c

clean:
	rm -rf *.o 
	rm wsnake





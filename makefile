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

windows_snake: main.o snake.o menu.o score.o
	gcc  -Wall -o snake main.o snake.o menu.o score.o 

clean:
	rm -rf *.o 
	rm snake





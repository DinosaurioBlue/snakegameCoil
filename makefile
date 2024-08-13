snake: main.o snake.o menu.o
	gcc -Wall -o snake main.o snake.o menu.o -lncurses

main.o: main.c snake.h
	gcc -Wall -c main.c

snake.o: snake.c snake.h
	gcc -Wall -c snake.c
snake: main.o snake.o
	gcc -Wall -o snake main.o snake.o -lncurses

main.o: main.c snake.h
	gcc -Wall -c main.c

snake.o: snake.c snake.h
	gcc -Wall -c snake.c
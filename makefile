snake: main.o FRONTEND.o BACKEND.o 
	gcc -Wall -o snake main.o FRONTEND.o BACKEND.o  -lncurses

main.o: main.c BACKEND.h FRONTEND.h GENERAL.h
	gcc -Wall -c main.c

FRONTEND.o: FRONTEND.c FRONTEND.h BACKEND.h GENERAL.h
	gcc -Wall -c FRONTEND.c

BACKEND.o: BACKEND.c BACKEND.h FRONTEND.h GENERAL.h
	gcc -Wall -c BACKEND.c

clean:
	rm -rf *.o 
	rm snake
	rm s

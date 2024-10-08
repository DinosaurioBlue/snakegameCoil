snake: main.o FRONTEND.o BACKEND.o GENERAL.h
	gcc -Wall -o snake main.o FRONTEND.o BACKEND.o  -lncurses

main.o: main.c BACKEND.h FRONTEND.h GENERAL.h
	gcc -Wall -c main.c

FRONTEND.o: FRONTEND.c FRONTEND.h BACKEND.h GENERAL.h 
	gcc -Wall -c FRONTEND.c 

BACKEND.o: BACKEND.c BACKEND.h FRONTEND.h GENERAL.h
	gcc -Wall -c BACKEND.c 

#just for testing

test: test.o FRONTEND.o BACKEND.o GENERAL.h
	gcc -Wall -o test test.o FRONTEND.o BACKEND.o  -lncurses

test.o: test.c BACKEND.h FRONTEND.h GENERAL.h
	gcc -Wall -c test.c

clean:
	rm -rf *.o 
	rm snake
	rm test

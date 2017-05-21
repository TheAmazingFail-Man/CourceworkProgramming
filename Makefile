all: main

main: main.o functions.o
	gcc -Wall -Werror -o main.o functions.o
	rm -rf *.o

main.o: main.c
	gcc -Wall -Werror -o -c main.c

functions.o: functions.c
	gcc -Wall -Werror -o -c functions.c
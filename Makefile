all: main

main: main.c
	gcc -Wall -Werror -c main main.c
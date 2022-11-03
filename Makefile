FLAGS=-Wall -Werror -Wextra -c -lncurses
GCC=gcc
ADDITIONAL=-lncurses

build: all

all: main

pong.o: pong.c
		$(GCC) $(FLAGS) pong.c -o pong.o

player.o: player.c
		$(GCC) $(FLAGS) player.c -o player.o 

field.o: field.c
		$(GCC) $(FLAGS) field.c -o field.o $(ADDITIONAL)

pad.o: pad.c
		$(GCC) $(FLAGS) pad.c -o pad.o

ball.o: ball.c
		$(GCC) $(FLAGS) ball.c -o ball.o

main: pong.o pad.o field.o ball.o player.o
		$(GCC) pong.o field.o pad.o ball.o player.o -o Pong.exe $(ADDITIONAL)

rebuild: clean all

clean: 
		rm -rf *.out *.o *.exe

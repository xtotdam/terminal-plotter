GCC=gcc
FLAGS=
ARGS=-lm -O0 -g -Wall
# ARGS=-lm -O2 -Wall
SRC=main.c

all: clean main

main:
	$(GCC) $(FLAGS) -o main $(SRC) $(ARGS)

clean:
	rm -f main
	rm -f main.exe

GCC=gcc
FLAGS=
ARGS=-lm -O0 -g -Wall
SRC=plotter.c plotter-showcase.c
EXE=plotter

.phony: all clean main docs

all: main

main:
	$(GCC) $(FLAGS) -o $(EXE) $(SRC) $(ARGS)

docs:
	doxygen Doxyfile

clean:
	rm -vf $(EXE)
	rm -vf $(EXE).exe

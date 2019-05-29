CC = gcc
OBJS = main.o util.o parser.o game.o solver.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c util.h types.h parser.h game.h solver.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)

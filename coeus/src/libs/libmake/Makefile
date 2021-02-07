CC = gcc
FLAGS = -Wall
SRC = $(wildcard *.c) 
SRC := $(filter-out test.c, $(SRC))
OBJ = $(SRC:.c=.o) 

all: $(OBJ)

%.o: %.c %.h 
	$(CC) $(FLAGS) -c $< 

clean:
	rm -f *.o

test: test.o $(OBJ)
	$(CC) $(FLAGS) -o test test.o $(OBJ)

test.o: test.c
	$(CC) -c test.c

clean_test:
	rm -f test
	rm -f *.o

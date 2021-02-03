
CC = gcc
FLAGS = -Wall
TARGET = latex.o
SRC = latex.c
DEP = latex.c latex.h

all: $(TARGET)

$(TARGET): $(DEP)
	$(CC) $(FLAGS) -c $(SRC)

test: test.o $(TARGET)
	$(CC) $(FLAGS) -o test test.o $(TARGET)

test.o: test.c
	$(CC) -c test.c

clean_test:
	rm -f test
	rm -f *.tex *.aux *.log
	sudo rm -r latex_test

clean:
	rm -f *.o

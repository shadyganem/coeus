
CC = gcc
FLAGS = -Wall
TARGET = latex.o
SRC = latex.c
DEP = latex.c latex.h

all: $(TARGET)
	echo -e "\033[0;32m Target Made Successfully \033[0m"

$(TARGET): $(DEP)
	$(CC) $(FLAGS) -c $(SRC)

test: test.o $(TARGET)
	$(CC) $(FLAGS) -o test test.o $(TARGET)

test.o: test.c
	$(CC) -c test.c
	echo -e "\033[0;32m Target Made Successfully \033[0m"

clean:
	rm -f *.o
	rm -f test
	rm -f *.tex *.aux *.log
	sudo rm -r latex_test

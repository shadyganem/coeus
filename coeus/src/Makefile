CC = gcc
FLAGS = -Wall
TARGET = coeus.out

SRC = $(wildcard *.c)
SRC := $(filter-out test.c, $(SRC))
OBJ = coeus.o

#TODO create general rule for DEP
DEP1 = libs/liblatex/liblatex.o 
DEP2 = libs/libargparse/libargparse.o
DEP = $(DEP1) $(DEP2)

all: $(TARGET)

$(TARGET): $(OBJ) $(DEP)
	$(CC) $(FLAGS) -o $@ $^ 

$(OBJ): $(SRC) defines.h
	$(CC) $(FLAGS) -c $^

$(DEP1):libs/liblatex/liblatex.c libs/liblatex/liblatex.h
	make -C libs/liblatex/

$(DEP2): libs/libargparse/libargparse.h libs/libargparse/libargparse.c
	make -C libs/libargparse/

install: $(TARGET)
	cp $(TARGET) /home/$(USER)/bin/$(basename $(TARGET))

uninstall:
	rm -f /home/$(USER)/bin/$(TARGET)

clean:
	rm -f $(TARGET)
	make clean -C libs/liblatex
	make clean -C libs/libargparse
	rm -f *.o *.h.gch *.out

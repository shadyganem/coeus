CC = gcc
FLAGS = -Wall
TARGET = coeus.out

SRC = coeus.c defines.h
OBJ = coeus.o
DEP1 = latex/latex.o 
DEP2 = libs/libargparse/libargparse.o
DEP = $(DEP1) $(DEP2)

all: $(TARGET)

$(TARGET): $(OBJ) $(DEP)
	$(CC) $(FLAGS) -o $@ $^ 

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $^

$(DEP1):latex/latex.c latex/latex.h
	make -C latex/

$(DEP2): libs/libargparse/libargparse.h libs/libargparse/libargparse.c
	make -C libs/libargparse/

install: $(TARGET)
	cp $(TARGET) /home/$(USER)/bin/$(basename $(TARGET))

uninstall:
	rm -f /home/$(USER)/bin/$(TARGET)

clean:
	rm $(TARGET)
	make clean -C latex/
	make clean -C libs/libargparse
	rm -f *.o *.h.gch *.out


CC = gcc
FLAGS = -Wall
TARGET = coeus.out

SRC = coeus.c defines.h
OBJ = coeus.o
DEP = latex/latex.o

all: $(TARGET)

$(TARGET): $(OBJ) $(DEP)
	$(CC) $(FLAGS) -o $@ $^ 

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $^

$(DEP):latex/latex.c latex/latex.h
	make -C latex/

install: $(TARGET)
	cp $(TARGET) /home/$(USER)/bin/$(basename $(TARGET))

uninstall:
	rm -f /home/$(USER)/bin/$(TARGET)

clean:
	rm $(TARGET)
	rm -f *.o *.h.gch

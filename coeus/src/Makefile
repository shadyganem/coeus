
CC = gcc
FLAGS = -Wall 
TARGET = coeus

SRC = coeus.c defines.h
OBJ = coeus.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ 

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $^

install: $(TARGET)
	cp $(TARGET) /home/$(USER)/bin

uninstall:
	rm -f /home/$(USER)/bin/$(TARGET)

clean:
	rm $(TARGET)
	rm -f *.o *.h.gch


CC = gcc
FLAGS = -Wall
TARGET = coeus

SRC = coeus.c defines.h
DEPEND = coeus.o

all : $(TARGET)

$(TARGET): $(DEPEND)
	$(CC) $(FLAGS) -o ../$@ $^ 

$(DEPEND): $(SRC)
	$(CC) $(FLAGS) -c $^

install:
	cp ../$(TARGET) /home/$(USER)/bin

clean:
	rm ../$(TARGET)
	rm -f *.o

CC = gcc
FLAGS = -Wall
TARGET = libargparse.o
SRC = libargparse.c libargparse.h

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)

clean:
	rm -f *.o *.h.gch


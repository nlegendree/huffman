CC = gcc
CFLAGS  = -g -Wall -pedantic
TARGET = ./huffman

build: 
	$(CC) $(CFLAGS) -o $(TARGET) ./code/src/main.c 

clean:
	rm -f *.o $(TARGET)

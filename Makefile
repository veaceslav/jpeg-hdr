CC=gcc
CCFLAGS=-Wall
LIBS=-ljpeg

all: main

main: main.c jpegapi.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBS)

jpegapi.o: jpegapi.c
	$(CC) $(CCFLAGS) -c $^

clean:
	rm *.o main

CC=gcc
CCFLAGS=-Wall -g -pg
LIBS=-ljpeg -lm

all: main

main: main.c jpegapi.o hdr.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBS)

jpegapi.o: jpegapi.c
	$(CC) $(CCFLAGS) -c $^

hdr.o: hdr.c
	$(CC) $(CCFLAGS) -c $^

clean:
	rm *.o main

run:
	./main samples/underexposed.JPG samples/normal.JPG samples/overexpose.JPG samples/hdr.JPG

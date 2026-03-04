CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0)

wordcounter: cwordcounter.c
	$(CC) cwordcounter.c -o wordcounter.exe $(CFLAGS) $(LIBS)

clean:
	rm -f wordcounter.exe
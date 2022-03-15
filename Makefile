CC = gcc
CFLAGS = -Wall

file-expander: main.c expand.c expand.h
	$(CC) $(CFLAGS) -o file-expander main.c expand.c

clean:
	rm file-expander

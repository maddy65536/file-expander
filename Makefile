CC = gcc
CFLAGS = -Wall

file-expander: main.c
	$(CC) $(CFLAGS) -o file-expander main.c

clean:
	rm file-expander

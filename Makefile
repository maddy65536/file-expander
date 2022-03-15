CC = gcc
CFLAGS = -Wall

file-expander:
	$(CC) $(CFLAGS) -o file-expander main.c

clean:
	rm file-expander

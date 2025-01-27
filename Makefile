all: rodcut

CC = gcc
CFLAGS = -Wall

rodcut: rodcut.o
	 gcc -o rodcut $(CFLAGS) rodcut.o

rodcut.o: rodcut.c
	 gcc -c rodcut.c $(CFLAGS)

clean:
	 rm -f rodcut *.o
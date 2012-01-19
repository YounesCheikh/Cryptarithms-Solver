#Makefile cryptarithmes

CC=gcc
OPT=-Wall
CURSES=-lncurses
EXEC=cryptarithme

all : $(EXEC)

#Compile biblio
biblio.o: biblio.c
	$(CC) -o biblio.o -c biblio.c $(OPT)

#Compile fonctions
fonctions.o: fonctions.c
	$(CC) -o fonctions.o -c fonctions.c $(OPT)

#Compile main
main.o: main.c
	$(CC) -o main.o -c main.c $(CURSES) $(OPT)

#link fonctions et main

$(EXEC): biblio.o fonctions.o main.o
	$(CC) biblio.o fonctions.o main.o $(CURSES) -o $(EXEC)

clean:
	rm -rf *.o *.exe *~

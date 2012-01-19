#Makefile cryptarithmes

CC=gcc
OPT=-Wall
CURSES=-lncurses
EXEC=cryptarithme
BT=recherche_backtracking/backtracking
RE=recherche_exhaustive/exhaustive
FS=recherche_dictionnaire/filesearch
AR=recherche_backtracking/afficher_res

all : $(EXEC) $(RE) $(BT) $(FS) $(AR)


#Compile fonctions
fonctions.o: fonctions.c
	$(CC) -o fonctions.o -c fonctions.c $(OPT)


########## COMPILE EXHAUSTIVE

#Compile biblio
recherche_exhaustive/biblio.o: recherche_exhaustive/biblio.c 
	$(CC) -o recherche_exhaustive/biblio.o -c recherche_exhaustive/biblio.c $(OPT)

#Compile fonctions
recherche_exhaustive/fonctions.o: recherche_exhaustive/fonctions.c
	$(CC) -o recherche_exhaustive/fonctions.o -c recherche_exhaustive/fonctions.c $(OPT)

#Compile main
recherche_exhaustive/main.o: recherche_exhaustive/main.c
	$(CC) -o recherche_exhaustive/main.o -c recherche_exhaustive/main.c $(CURSES) $(OPT)

#link fonctions et main

$(RE): recherche_exhaustive/biblio.o recherche_exhaustive/fonctions.o recherche_exhaustive/main.o
	$(CC) recherche_exhaustive/biblio.o recherche_exhaustive/fonctions.o recherche_exhaustive/main.o $(CURSES) -o $(RE)

#clean:
#	rm -rf *.o *.exe *~


########## COMPILE BACKTRACKING

#Compile fonctions
recherche_backtracking/backtracking.o: recherche_backtracking/backtracking.c
	$(CC) -o recherche_backtracking/backtracking.o -c recherche_backtracking/backtracking.c $(OPT)

#Compile main
recherche_backtracking/main.o: recherche_backtracking/main.c
	$(CC) -o recherche_backtracking/main.o -c recherche_backtracking/main.c $(CURSES) $(OPT)

#Compile affichage
recherche_backtracking/afficher_res.o: recherche_backtracking/afficher_res.c
	$(CC) -o recherche_backtracking/afficher_res.o -c recherche_backtracking/afficher_res.c $(CURSES) $(OPT)

#affich resultats

$(AR): recherche_backtracking/afficher_res.o
	$(CC) recherche_backtracking/afficher_res.o $(CURSES) -o $(AR)
	
#link fonctions et main

$(BT): recherche_backtracking/backtracking.o fonctions.o recherche_backtracking/main.o
	$(CC) fonctions.o recherche_backtracking/backtracking.o recherche_backtracking/main.o $(CURSES) -o $(BT)


########## COMPILE RECHERCHE DICTIONNAIRE

#Compile fonctions
recherche_dictionnaire/filesearch.o: recherche_dictionnaire/filesearch.c
	$(CC) -o recherche_dictionnaire/filesearch.o -c recherche_dictionnaire/filesearch.c $(OPT)

#Compile main
recherche_dictionnaire/main.o: recherche_dictionnaire/main.c
	$(CC) -o recherche_dictionnaire/main.o -c recherche_dictionnaire/main.c $(CURSES) $(OPT)

#link fonctions et main

$(FS): recherche_dictionnaire/filesearch.o fonctions.o recherche_dictionnaire/main.o
	$(CC) fonctions.o recherche_dictionnaire/filesearch.o recherche_dictionnaire/main.o $(CURSES) -o $(FS)

########## COMPILE MAIN FILE

#Compile main
main.o: main.c
	$(CC) -o main.o -c main.c $(CURSES) $(OPT)

#link fonctions et main

$(EXEC): main.o
	$(CC) main.o $(CURSES) -o $(EXEC)


clean:
	rm -rf *.o *.exe *~ cryptarithme
	rm -rf recherche_backtracking/*.o recherche_backtracking/*.exe recherche_backtracking/*.~ recherche_backtracking/backtracking
	rm -rf recherche_exhaustive/*.o recherche_exhaustive/*.exe recherche_exhaustive/*.~ recherche_exhaustive/exhaustive
	rm -rf recherche_dictionnaire/*.o recherche_dictionnaire/*.exe recherche_dictionnaire/*.~ recherche_dictionnaire/filesearch


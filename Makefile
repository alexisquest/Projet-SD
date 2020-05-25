CC = gcc
CFLAGS = -W -Wall -Os `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
EXEC = floodit_partie1

all: $(EXEC)

api_genere_instance.o: api_genere_instance.c api_genere_instance.h
	$(CC) $(CFLAGS) -c api_genere_instance.c

api_grille.o: api_grille.c api_grille.h
	$(CC) $(CFLAGS) -c api_grille.c

liste_cases.o: liste_cases.c liste_cases.h
	$(CC) $(CFLAGS) -c liste_cases.c

Zsg.o: Zsg.c Zsg.h liste_cases.h
	 $(CC) $(CFLAGS) -c Zsg.c



graphe_zones.o: graphe_zones.c graphe_zones.h fonctions.h
	$(CC) $(CFLAGS) -c graphe_zones.c 

fonctions.o: fonctions.c fonctions.h liste_cases.h Zsg.h
	$(CC) $(CFLAGS) -c fonctions.c
	
fonctions_graph.o: fonctions_graph.c fonctions_graph.h graphe_zones.h liste_cases.h 
	$(CC) $(CFLAGS) -c fonctions_graph.c

#floodit.o: floodit.c
	#$(CC) $(CFLAGS) -c floodit.c 

#floodit: floodit.o liste_cases.o  api_grille.o api_genere_instance.o fonctions.o Zsg.o fonctions_graph.o  graphe_zones.o
	#$(CC) -o floodit floodit.o liste_cases.o api_grille.o api_genere_instance.o fonctions.o Zsg.o fonctions_graph.o $(LDFLAGS)

floodit_partie1.o: floodit_partie1.c
	$(CC) $(CFLAGS) -c floodit_partie1.c 

floodit_partie1: floodit_partie1.o liste_cases.o  api_grille.o api_genere_instance.o fonctions.o Zsg.o graphe_zones.o fonctions_graph.o
	$(CC) -o floodit_partie1 floodit_partie1.o liste_cases.o api_grille.o api_genere_instance.o fonctions.o Zsg.o graphe_zones.o fonctions_graph.o $(LDFLAGS)

clean:
	rm -f *.o $(EXEC)


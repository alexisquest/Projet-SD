#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "api_grille.h"
#include "liste_cases.h"
#include "Zsg.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Retourne dans L la liste des cases de meme couleur que la case i, j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille,
                     ListeCases *L);

/* Algorithme tirant au sort une couleur :
   il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

int sequence_aleatoire_rapide(int **M , Grille *G , int dim , int nbcl , int aff);

#endif /* FONCTIONS_H */

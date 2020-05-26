#ifndef FONCTIONS_GRAPH_H
#define FONCTIONS_GRAPH_H

#include "api_grille.h"
#include "graphe_zones.h"
#include "liste_cases.h"
#include "Pile_case.h"
#include <stdio.h>

void update_bordure_graph( int couleur , Cellule_som** bordure , Sommet* zsg, Graphe_zone* gz  );


int max_tableau_cellule(Cellule_som** tab , int taille);


int max_bordure(Graphe_zone* gz , int nbcl, int dim, Grille *G, int aff);


#endif /* FONCTIONS_GRAPH_H */

#ifndef _GRAPHE_ZONE_
#define _GRAPHE_ZONE_

#include "liste_cases.h"
#include "fonctions.h"



typedef struct sommet Sommet;

/* Element d’une liste cha\^in\’ee de pointeurs sur Sommets */
typedef struct cellule_som {
    Sommet * sommet;
    struct cellule_som * suiv;
} Cellule_som;


struct sommet {
    int num ; /* Numero du sommet (sert uniquement a l’affichage) */
    int cl ; /* Couleur d’origine du sommet-zone */
    ListeCases cases ;/* Listes des cases du sommet-zone */
    int nbcase_som ; /* Nombre de cases de cette liste */
    Cellule_som * sommet_adj ; /* Liste des ar\eteses pointeurs sur les sommets 16 adjacents */
    int marque ;
};


typedef struct graphe_zone {
    int nbsom ;/* Nombre de sommets dans le graphe */
    Cellule_som * som ; /* Liste chainee des sommets du graphe */
    Sommet *** mat ;/* Matrice de pointeurs sur les sommets indiquanta quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;


void ajoute_liste_sommet(Sommet *s, Cellule_som **som); /*ajoute un pointeur sur Sommet à une liste chainée de Cellule_som passée en parametre */

void detruit_liste_somme(Cellule_som *som); //détruit une liste chainée passée en parametre SANS detruire les sommets pointées par cette liste

void ajoute_voisin(Sommet *s1, Sommet *s2); // met à jour deux sommets s1 et s2 en indiquant qu'ils sont adjacents l'un de l'autre

int adjacent(Sommet *s1, Sommet *s2); //renvoie vrai (1) si et seulement si deux sommets sont adjacents sinon false (0)

void init_graphe_zone(Graphe_zone ** G, int dim);


Graphe_zone* cree_graphe_zone(int** M, int nbCases);



void affichage_graphe(Graphe_zone *G, int nbCases);

#endif 

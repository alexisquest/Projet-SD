#include <stdio.h>
#include <stdlib.h>
#include "graphe_zones.h"
#include "liste_cases.h"
#include "Pile_case.h"

Cellule_som * ajoute_liste_sommet(Sommet *s, Cellule_som *som){
    Cellule_som * tmp = (Cellule_som *) malloc(sizeof(Cellule_som));
    
    tmp->sommet = s;
    tmp->suiv = som;
    
    return tmp;
}


void detruit_liste_somme(Cellule_som *som){

    Cellule_som *tmp = som;
    
    while(tmp){ //tant tmp ne vaut pas null
        som = tmp->suiv; // on stock la suite de la liste
        
        free(tmp); // on désalloue l'element courant de la liste 
        tmp = som; // on recupere dans tmp la liste stocker dans som 
    
    }

}


void ajoute_voisin(Sommet *s1, Sommet *s2){
    
    s1->sommet_adj = ajoute_liste_sommet(s2, s1->sommet_adj); // ajout le sommet s2 dans la liste des sommets adjacents de s1
    s2->sommet_adj = ajoute_liste_sommet(s1, s2->sommet_adj);  // ajout le sommet s1 dans la liste des sommets adjacents de s2

}

int adjacent(Sommet *s1, Sommet *s2){
    int s1_s2 = 0; //boolean initialiser à 0 pour dire que s2 n'est pas adjacent à s1 
    int s2_s1 = 0; //boolean initialiser à 0 pour dire que s1 n'est pas adjacent à s2
    
    Cellule_som * tmp = s1->sommet_adj; // recupere la liste adjacent de s1
    
   
    while(tmp){  //parcours dans la liste adjacent de s1
        if(tmp->sommet == s2){ // s2 est adjacent à s1
            s1_s2 = 1; //on met le boolean a 1
            break;
        }
        
        tmp = tmp->suiv;
    }
    
    tmp = s2->sommet_adj; // recupere la liste adjacent de s2
    
    while(tmp){ //parcours dans la liste adjacent de s2
        if(tmp->sommet == s1){ // s1 est adjacent à s2
            s2_s1 = 1; //on met le boolean a 1
            break;
        }
        
        tmp = tmp->suiv;
    }
    
    return (s1_s2 && s2_s1) ? 1 : 0;
}




void cree_graphe_zone(int** M, int nbCases, Graphe_zone *G)
{

  int i, j;
  Sommet *s = NULL, *s2 = NULL;
  // ici on considere G->som = NULL de base

  // allocation des sommets de G
  for (i=0; i<nbCases; i++)
    for (j=0; j<nbCases; j++)
      if (G->mat[i][j] == NULL) {
	s = (Sommet *) malloc(sizeof(Sommet)); // initalisation d'un sommet vide
	s->nbcase_som = 0;
	init_liste(&(s->cases));
	s->cases->i = i;	
	s->cases->j = j;
	s->sommet_adj = NULL;
	G->mat[i][j] = s;
	(G->nbsom)++;

	/* ceci marche meme si G->som n'a pas de liste a la base
	 * donc le "dernier" element sera a NULL
	 */
	G->som = ajoute_liste_sommet(s, G->som);

	// on remplit les sommets en appelant trouve_zone
	trouve_zone(M, i, j, s, G, nbCases);
      }


  // recherche des sommets adjacents
  for (i=0; i < nbCases; i++)
    for(j=0; j < (nbCases - 1); j++) {
      /* Si deux cases adjacentes de la matrice pointent vers des Sommets
       * differents qui ne sont pas deja adjacents alors une relation
       * d'adjacence est ajoutée. Sinon, on passe aux cases suivantes
       */
      s = G->mat[i][j];
      s2 = G->mat[i][j+1];
      // si les sommets sont adjacents, on skip
      if (s == s2 || adjacent(s, s2) != 0)
	continue;

      // Si les sommets sont diff et qu'ils ne sont pas deja adjacents
      ajoute_voisin(s, s2);
    }
}

void trouve_zone(int **M, int i, int j, Sommet *s, Graphe_zone *G, int nbCases)
{
  Pile p;
  Element *e;
  /* Pile_case pileun; */
  /* init_pile(&pileun); */
  /* Pile_case piledeux= NULL; */
  /* int nb = 0; */
  /* s->cl = M[i][j]; */

  /* empile(&p, i, j); */
  /* liste_ajoute((&s->suiv), i, j); */

  s->cl = M[i][j]; // Mise a jour de la couleur de la case
  detruit_liste_somme(s->sommet_adj); // Suppresion des membres de la zone
  s->nbcase_som = 0;


  init_pile(&p);

  empile(&p, i, j); // On empile la premiere case

  while (!pile_vide(p)) {
    e = depile(&p);
    i = e->i, j = e->j; // On depile et recupere l'elem courant


    if ((e->j+1 < nbCases) &&
	(M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!existe(e->i, e->j+1, &s->cases))) {
      ajoute_en_tete(&s->cases, e->i, e->j+1); // Ajout de la case a la liste des membres de la zone
      s->nbcase_som++; // Incr du compteur de zone
      empile(&p, e->i, e->j+1);
    }

    if ((e->j-1 >= 0) &&
	(M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!existe(e->i, e->j-1, &s->cases))) {
      ajoute_en_tete(&s->cases, e->i, e->j-1);
      s->nbcase_som++;
      empile(&p, e->i, e->j-1);
    }

    if ((e->i+1 < nbCases) &&
	(M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!existe(e->i+1, e->j, &s->cases))) {
      ajoute_en_tete(&s->cases, e->i+1, e->j);
      s->nbcase_som++;
      empile(&p, e->i+1, e->j);
    }

    if ((e->i-1 >= 0) && (M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!existe(e->i-1, e->j, &s->cases))) {
      ajoute_en_tete((&s->cases), e->i-1, e->j);
      s->nbcase_som++;
      empile(&p, e->i-1, e->j);
    }

    //On pointe la case de la matrice de G sur la zone
    G->mat[i][j] = s;
    G->som++;

    free(e);

  }
  //  free(p);

}

void affichage_graphe(Graphe_zone *G, int nbCases)
{
  int i=0, j=0;
  Cellule_som *parcours; // sert a parcourir la liste des sommets

  for (i=0; i<nbCases; i++)
    for (j=0; j<nbCases; j++) {
      parcours = G->mat[i][j]->sommet_adj;
      printf("Dans le sommet [%d][%d], on a les noeuds ", i, j);
      while (parcours) {
	printf("%d ", parcours->sommet->num);
	parcours = parcours->suiv;
      }
      printf("\n");
    }

}









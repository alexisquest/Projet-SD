#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "api_grille.h"
#include "api_genere_instance.h"
#include "fonctions.h"
#include "fonctions_graph.h"
#include "graphe_zones.h"
#include "Pile_case.h"

int main(int argc, char *argv[]) {
  clock_t temps_initial;  /* Temps initial en micro-secondes */
  clock_t temps_final;    /* Temps final en micro-secondes */
  float temps_cpu;        /* Temps total en secondes */

  if(argc != 7) {
    printf("Usage: %s dimension nb_de_couleurs niveau_difficulte "
           "graine exo:0|1|2 aff:0|1\n", argv[0]);
    return 1;
  }

  int dim = atoi(argv[1]);
  int nbcl = atoi(argv[2]);
  int nivdif = atoi(argv[3]);
  int graine = atoi(argv[4]);
  int exo = atoi(argv[5]);
  int aff = atoi(argv[6]);
  

  /* Generation de l'instance */
  int** M = malloc(dim * sizeof(*M));
  if(M == NULL) {
    exit(1);
  }
  int i;
  for(i = 0; i < dim; i++) {
    M[i] = malloc(dim * sizeof(*M[i]));
    if(M[i] == NULL) {
      exit(1);
    }
  }
  gi_genere_matrice(dim, nbcl, nivdif, graine, M);

  /* Affichage de la grille */
  
  Grille *G = NULL;
  if(aff == 1) {
    G = grille_init(dim, nbcl, 500);
    grille_ouvre_fenetre(G);

    for(i = 0;i < dim;i++) {
      int j;
      for(j = 0;j < dim;j++) {
        grille_attribue_couleur_case(G, i, j, M[i][j]);
      }
    }
    grille_redessine(G);
  }
	
  temps_initial = clock();

  if(exo == 0) {
    printf("\t%d", sequence_aleatoire_rec(M, G, dim, nbcl, aff));
  }

  if(exo == 1) {
    printf("\t%d", sequence_aleatoire_rapide(M , G , dim , nbcl ,aff));
  }

  if(exo == 2){
  	
  	Graphe_zone* graph=cree_graphe_zone(M , dim);
  	//affichage_graphe(graph , dim);
  	printf("\t%d", max_bordure(graph,nbcl,dim,G,aff));
  }

  if(aff == 1) {
    grille_attente_touche();
    grille_ferme_fenetre(G);
    grille_free(G);
  }
  
  
  
  temps_final = clock();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf("\t%f\n", temps_cpu);
  return 0;
}



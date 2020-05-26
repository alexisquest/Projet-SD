#include "API_Grille.h"
#include "Liste_case.h"
#include<stdio.h>
#include "fonctions_graph.h" //fichier comportant les prototypes des fonctions dvp pour l'exo 5

//Exercice 6 – Strategie parcours en largeur

// fonction permettant d'obtenir le plus court chemin
int cherche_plus_court(Graphe_zone *G, Sommet *destination){
  int taille=destination->distance;
  int * listeCouleur = (int *) malloc(sizeof(int)*taille);
  int i;
  Sommet *tmp=destination;
  for (i=taille-1;i>=0;i--){
    listeCouleur[i]=tmp->cl;
    tmp=tmp->pere;}
  return taille;
}

// Q 6.2
//-------------CAS DE BASE----------------//
void parcours_largeur(Graphe_zone* G, int dim, int nbcl, Grille* grille, int aff){

  //on commence par ajouter le cas de base a la zone ainsi que ses adjacents a la bordure
  Cellule_som * cs = malloc(sizeof(Cellule_som));
  cs -> sommet = gz -> G ->mat[0][0];
  cs -> sommet -> marque = 0;
  cs -> suiv = NULL;
  gz -> Szsg = cs ;

  //ajout des adjacents a la bordure
  Cellule_som * tmp = gz->Szsg->sommet->sommet_adj;
  while(tmp){
    tmp->sommet -> marque = 1 ;
    Cellule_som * c1 = malloc(sizeof(Cellule_som));
    c1->sommet = tmp ->sommet;
    c1->suiv = gz->Bordure_g[tmp->sommet->cl];
    gz->Bordure_g[tmp->sommet->cl]=c1;
    (gz->taille_bordure[tmp->sommet->cl]) += tmp->sommet->nbcase_som;

    tmp = tmp -> suiv ;
  }

  //-------------FIN DU CAS DE BASE---------------//

  //ajout de la zone inferieur droite dans last
  Sommet* last = G->mat[dim-1][dim-1];

  int* tab = cherche_plus_court(G->mat[0][0], last); //on fait appelle a la fonction de l'exo 6.2

  int i=0;
  for(i=1 ; i<=last->distance ; i++){

  maj_bordure_g(gz, tab[i]);
  cpt++;

  //----------------AFFICHAGE------------------//

  if(aff==1){

    Cellule_som* lcs = gz->Szsg;
    while(lcs){

    ListeCases lc = lcs->sommet->cases;
    while(lc){
    grille_attribue_couleur_case(grille,lc->i,lc->j,tab[i]); //couleur=tab[i]
    lc=lc->suiv;
    }

    lcs=lcs->suiv;
    }

    grille_attente_touche();
    grille_redessine(grille);

    affiche_zsg(gz);
    affiche_bordure(gz);
    }

  }


  //--------FONCTION max_bordure EXO5--------//
  max_bordure(G, dim, nbcl, grille, aff, gz);


  return;
}

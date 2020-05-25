#include <stdio.h>
#include <stdlib.h>
#include "graphe_zones.h"


#include "liste_cases.h"
#include "fonctions.h"

//ajoute un sommet dans une liste chainée de sommets
void ajoute_liste_sommet(Sommet *s, Cellule_som **som){
    Cellule_som * tmp = (Cellule_som *) malloc(sizeof(Cellule_som));
    
    tmp->sommet = s;
    tmp->suiv = *som;
    *som=tmp;
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
    
    ajoute_liste_sommet(s2,&s1->sommet_adj); // ajout le sommet s2 dans la liste des sommets adjacents de s1
    ajoute_liste_sommet(s1,&s2->sommet_adj);  // ajout le sommet s1 dans la liste des sommets adjacents de s2

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




void init_graphe_zone(Graphe_zone ** G, int dim){
	int i, j;
	
	(*G) = malloc(sizeof(*(*G)));
	
	(*G)->nbsom = 0;
	(*G)->som = NULL;
	
	(*G)->mat = malloc(sizeof(*(*G)->mat) * dim);
	for(i=0; i<dim; i++){
		(*G)->mat[i] = malloc(sizeof(*(*G)->mat[i])*dim);
		
		for(j=0; j<dim; j++){
			(*G)->mat[i][j]=NULL;
		}
	}
}



Graphe_zone* cree_graphe_zone(int** M, int nbCases)
{
	
  Graphe_zone* G=NULL;
  init_graphe_zone(&G,nbCases);
  int i, j,cpt=0;
  Sommet *s=NULL ,*s1 = NULL, *s2 = NULL;
  // ici on considere G->som = NULL de base
    ListeCases deja_fait =NULL;
  // allocation des sommets de G
  for (i=0; i<nbCases; i++){
    for (j=0; j<nbCases; j++){
    
      if (existe(i,j,&deja_fait) ==0) {

      	
		s = (Sommet *) malloc(sizeof(Sommet)); // initalisation d'un sommet vide
        s->num=cpt;
        cpt++;
		s->nbcase_som = 0;
		
		init_liste(&(s->cases));
		s->cl=M[i][j];
		ajoute_en_tete(&(s->cases) , i , j);//ajoute  ds le sommet la case courant
        s->nbcase_som++;
		s->sommet_adj = NULL;
		s-> marque=2;
		
		G->mat[i][j] = s;
		(G->nbsom)++;;//creer le sommet avec la premiere case
    
     ajoute_liste_sommet(s,&G->som);//ajoute le sommet dans la liste des sommet du graphe
      
     // on récupère toutes les cases du sommet zone dans tmp
     ListeCases tmp=NULL;
     int taille=0;
     trouve_zone_rec(M, nbCases , i ,  j , &taille , &tmp);
     //on insère ces cases dans le sommet  
    
        while (tmp){
            ajoute_en_tete(&(s->cases), tmp->i,tmp->j ); //on insere la case dans le sommet
            G->mat[tmp->i][tmp->j] = s; // on pointe la case vers le sommet auquel il appartient 
            ajoute_en_tete(&deja_fait, tmp->i,tmp->j ); // on ajoute le sommet a la liste "deja_fait",pour ne pas remettre cette dans un autre sommet 
            tmp=tmp->suiv; //avance   
        }
     	s->nbcase_som+=taille;

      }
    }
  }

  //recherche des sommets adjacents
  
  for (i=0; i < nbCases; i++){
    for(j=0; j < nbCases; j++) {
   		s = G->mat[i][j];
   		
   		if(i+1<nbCases){
      		s1 = G->mat[i+1][j];
      		if (s == s1 || adjacent(s, s1) != 0)
				continue;

      		// Si les sommets sont diff et qu'ils ne sont pas deja adjacents
      		ajoute_voisin(s, s1);
      	}
      	
      	if(j+1<nbCases){
      		s2 = G->mat[i][j+1];
      		if (s == s2 || adjacent(s, s2) != 0)
				continue;

      		// Si les sommets sont diff et qu'ils ne sont pas deja adjacents
      		ajoute_voisin(s, s2);
      	}
   	 
    }
  }
  
  
  return G;
}



void affichage_graphe(Graphe_zone *G, int nbCases)
{
	
  int i=0, j=0;
  Cellule_som *parcours_adj =NULL; // sert a parcourir la liste des sommets adjacents
  
  /*
  for (j=0; j<nbCases; j++){
    for (i=0; i<nbCases; i++) {
      parcours_adj = G->mat[i][j]->sommet_adj;
      
      printf("le sommet [%d][%d] num du sommet:%d,couleur=%d, à comme sommet adjacent : \t", i, j,G->mat[i][j]->num,G->mat[i][j]->cl );
      
      while (parcours_adj) {
	printf("num=%d\t,", parcours_adj->sommet->num);
	parcours_adj = parcours_adj->suiv;
      }
      printf("\n");
    }
    
  }*/
  /*
  printf("affichage des sommets adjacents:\n");
  Cellule_som* tmp_som = G->som;
  while(tmp_som){
  	printf("sommet num %d à comme voisin :",tmp_som->sommet->num);
  	parcours_adj = tmp_som->sommet->sommet_adj;
  	while (parcours_adj) {
		printf(" %d", parcours_adj->sommet->num);
		parcours_adj = parcours_adj->suiv;
    }
    printf("\n");
    tmp_som=tmp_som->suiv;
  }
  printf("\n");
  */
  //printf("num de sommet :\n");
  for (j=0; j<nbCases; j++){
    for (i=0; i<nbCases; i++) {
      parcours_adj = G->mat[i][j]->sommet_adj;
      
      printf("  %d",G->mat[i][j]->cl);
      
    }
    printf("\n");
  }

}









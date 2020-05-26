#include "fonctions.h"
#include <stdlib.h>



int sequence_aleatoire_rec(int **M , Grille *G , int dim , int nbcl , int aff){
	ListeCases L;
	init_liste(&L);
	
	int taille=0;
	
	trouve_zone_rec(M,dim,0,0,&taille,&L);
	
	/*affichage*/
	//printf("%d/%d\n",taille,dim*dim);
	if(aff == 1){
		grille_redessine(G);
	}
	
	/*vérification si l'inondation est terminé*/
	if(taille == dim*dim){
		return 1;
	}
	
	
		
	/*tirage d'une nouvelle couleur*/
	int tirage = 0;
	do{
		tirage = rand()%nbcl;
	}while(tirage == M[0][0]);
	
	/* changement des couleurs dans la matrice*/
	while(L){
		M[L->i][L->j] = tirage;
		L=L->suiv;
	}
	
	/*changement couleur dans la grille*/
	if(aff==1){
		int i;
		for(i = 0;i < dim;i++) {
		  int j;
		  for(j = 0;j < dim;j++) {
		    grille_attribue_couleur_case(G, i, j, M[i][j]);
		  }
		}	
    }
    
	return 1 + sequence_aleatoire_rec(M,G,dim,nbcl,aff);
}



void trouve_zone_rec(int **M , int dim , int i , int j , int *taille , ListeCases *L){

	if(i<dim-1){
		/*case à droite*/
		if(M[i+1][j] == M[i][j] && existe(i+1,j,L)==0 ){
			ajoute_en_tete(L , i+1 , j);
			*taille = *taille + 1 ;
			trouve_zone_rec(M,dim,i+1,j,taille,L);
		}
	}
	if(j<dim-1){
		/*case en bas*/
		if(M[i][j+1] == M[i][j] && existe(i,j+1,L)==0){
			ajoute_en_tete(L , i , j+1);
			*taille = *taille + 1 ;
			trouve_zone_rec(M,dim,i,j+1,taille,L);
		}	
	}
	/*case à gauche*/
	if(i>0){
		if(M[i-1][j] == M[i][j] && existe(i-1,j,L)==0 ){
			ajoute_en_tete(L , i-1 , j);
			*taille = *taille + 1 ;
			trouve_zone_rec(M,dim,i-1,j,taille,L);
		}
	}
	/*case en haut*/
	if(j>0){
		if(M[i][j-1] == M[i][j] && existe(i,j-1,L)==0){
			ajoute_en_tete(L , i , j-1);
			*taille = *taille + 1 ;
			trouve_zone_rec(M,dim,i,j-1,taille,L);
		}	
	}
}


int sequence_aleatoire_rapide(int **M , Grille *G , int dim , int nbcl , int aff){
	
	Zsg *Z;

	int cpt=0;
	int nbessaie=0;
	init_Zsg(&Z,dim,nbcl);
	cpt+=agrandit_Zsg(M,Z,M[0][0],0,0);
	/*affichage*/
	if(aff == 1){
		grille_redessine(G);
	}
	
	while(cpt < dim*dim){
		
		nbessaie++;
		/*tirage d'une nouvelle couleur*/
		int tirage = 0;
		do{
			tirage = rand()%nbcl;
		}while(tirage == M[0][0]);

		

		/*on agrandit la zone a partir de toutes les cases de la bordure ayant la couleur tiré au sort*/
		ListeCases ite = Z->B[tirage];
		while(ite){
			cpt += agrandit_Zsg(M,Z,tirage,ite->i,ite->j);
			ite = ite->suiv;
		}
		detruit_liste(&Z->B[tirage]);
		
		/*on change de couleur les cases de Lzsg*/
		ListeCases it = Z->Lzsg;
		while(it){
			M[it->i][it->j]=tirage;
			it = it->suiv;
		}

		/*changement couleur dans la grille*/
		if(aff==1){
			int i;
			for(i = 0;i < dim;i++) {
			  int j;
			  for(j = 0;j < dim;j++) {
			    grille_attribue_couleur_case(G, i, j, M[i][j]);
			  }
			}
			grille_redessine(G);	
	    }
		
	}
	return nbessaie+1;


}

#include "fonctions_graph.h"

#include <stdlib.h>




void update_bordure_graph( int couleur , Cellule_som** bordure , Sommet* zsg, Graphe_zone* gz ){
	Cellule_som* ite_bordure = bordure[couleur];
	while(ite_bordure){
		/*on met les cases du sommet dans la zsg*/
		ListeCases c=ite_bordure->sommet->cases;
		while(c){
			ajoute_en_tete(&zsg->cases, c->i, c->j);
			gz->mat[c->i][c->j]=zsg;
			c=c->suiv;
		}
		detruit_liste(&ite_bordure->sommet->cases);

		/*on insère dans la bordure les zones qui était adjacent à la zone que l'on vient de rajouter au zsg*/
		Cellule_som* ite_sommet_adj = ite_bordure->sommet->sommet_adj;
		while(ite_sommet_adj){
			//si le sommet est de la meme couleur que la zsg , on ajoute les cases du sommet dans la zsg
			if(ite_sommet_adj->sommet->marque==2 && ite_sommet_adj->sommet->cl==couleur){
				ListeCases c=ite_sommet_adj->sommet->cases;
				while(c){
					ajoute_en_tete(&zsg->cases, c->i, c->j);
					gz->mat[c->i][c->j]=zsg;
					c=c->suiv;
				}
				//et on rajoute les sommet adjcents à cette zone dans la bordure
				Cellule_som* tmp = ite_sommet_adj->sommet->sommet_adj;
				while(tmp){
						if(ite_sommet_adj->sommet->marque==2){
							ajoute_liste_sommet(ite_sommet_adj->sommet , &bordure[ite_sommet_adj->sommet->cl]);
							ite_sommet_adj -> sommet -> marque = 1;
						}
						tmp = tmp->suiv;
					}
					
			}
			
			
			else{
				//sinon on ajoute simplement les sommet dans la bordure
				if(ite_sommet_adj->sommet->marque==2){
					ajoute_liste_sommet(ite_sommet_adj->sommet , &bordure[ite_sommet_adj->sommet->cl]);
					ite_sommet_adj -> sommet -> marque = 1;
				}
			}
			ite_sommet_adj = ite_sommet_adj->suiv;
		}

		/*on passe au sommet de la bordure suivant*/
		ite_bordure=ite_bordure->suiv;
	}
	bordure[couleur]=NULL;
}



int max_tableau_cellule(Cellule_som** tab , int taille){
	int max = 0;
	int couleur_max = -1;
	int ite = 0;
	/*on parcourt chaque case du tableau soit chaque couleur*/
	while(ite<taille){
		Cellule_som* ite_tab = tab[ite];
		
		int cpt=0;
		
		/*pour chaque sommet d'une couleur*/
		while(ite_tab){
		
			/*on fait la somme des cases de chaque sommet de cette couleur*/
			cpt+=ite_tab->sommet->nbcase_som;
			
			ite_tab=ite_tab->suiv;
		}
		/*on regarde si cette couleur à le plus de cases*/
		if(cpt>max){
			max = cpt;
			couleur_max = ite;
		}
		ite++;
	}
	return couleur_max;
}



void max_bordure(Graphe_zone* gz , int nbcl, int dim, Grille *G, int aff){
	
	/*------INITIALISATION------*/

	/*on créer le sommet zsg*/
	Sommet* zsg = gz->mat[0][0];

	/*on ajoute la zone contenant la case 0,0 à la zsg*/
	gz->mat[0][0]->marque = 0;

	/*on créer la bordure*/
	Cellule_som** bordure = malloc(sizeof(*bordure)*nbcl);
	for(int i=0 ; i<nbcl ; i++){
		bordure[i]=NULL;
	}

	/*on ajoute les sommet adj à la premiere zone à la bordure*/
	Cellule_som* ite = gz->mat[0][0]->sommet_adj;
	while(ite){
		ajoute_liste_sommet(ite->sommet , &bordure[ite->sommet->cl]);
		ite = ite->suiv;
	}

	/*------FIN INITIALISATION------*/

	/*affichage*/
	if(aff == 1){
		grille_redessine(G);
	}
	int couleur_max;
	while((couleur_max = max_tableau_cellule(bordure , nbcl))!=-1){
	
		update_bordure_graph(couleur_max , bordure , zsg , gz);

		/*changement couleur dans la grille*/
		if(aff==1){
			int i;
			for(i = 0;i < dim;i++) {
			  int j;
			  for(j = 0;j < dim;j++) {
			    grille_attribue_couleur_case(G, i, j, gz->mat[i][j]->cl);
			  }
			}
			grille_redessine(G);
			sleep(1);	
	    }
		
	}


} 




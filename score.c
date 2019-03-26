#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"


#define FICHIER "score.txt"


void aff_liste(LISTE_SCORE * liste)
{
	SCORE * courant = liste->premier;
	printf (" **** SCORE ****\n") ;
	while (courant != NULL)
	{ 
		printf ("pseudo=%s score =%d\n", courant->pseudo, courant->taille_serpent) ;
		courant = courant->suivant ;
	}
	printf("\n\n");
	return;
}
// ecrse le fichier et ecrit toute la liste de score
void ecrire_score(LISTE_SCORE * liste_score) 
{
	FILE* fichier_score = NULL;
	//suppression du contenue des fichier et lecture
	fichier_score = fopen(FICHIER,"w+");
	// ajouter nouveau score
	SCORE * courant = liste_score->premier;
	int nb=0;
	while (courant != NULL)
	{ 
		fprintf(fichier_score,"%s %d ", courant->pseudo, courant->taille_serpent) ;
		courant = courant->suivant ;
		nb++;
	}
	while (nb <5 )
	{
		fprintf(fichier_score,"***** 0 ");
		nb++;
	}
	fclose(fichier_score);
	return;
}


void lire_score(LISTE_SCORE * liste)
{
	FILE* fichier_score = NULL;
	char pseudo[5][10]  ;
	int score[5];
	int i;

	fichier_score = fopen(FICHIER,"r");
	if ( fichier_score == NULL )
	{
		printf("Creation du fichier de score\n");
		ecrire_score(liste);
		fichier_score = fopen(FICHIER,"r");
	}


	// recuperation du contenue du fichier pour le mettre dans liste_score
	fscanf(fichier_score,"%s %d %s %d %s %d %s %d %s %d ",
	pseudo[0], &score[0],
	pseudo[1], &score[1],
	pseudo[2], &score[2],
	pseudo[3], &score[3],
	pseudo[4], &score[4] );

	for(i=0; i<5; i++)
	{

		SCORE* score_elt = (SCORE*)malloc(sizeof(SCORE));

		score_elt->taille_serpent =score[i];

		strcpy(score_elt->pseudo,pseudo[i]);
		
		ajoute_score( liste, score_elt );
	}

	fclose(fichier_score);
	return;
}


// Ajoute un elt au bon endroi dans une liste deja trie.
// La liste est TOUJOURS trie car on ajoute des elt uniquement via cette fonction
// La fonction conserve egalement la taille maximum correcte
void ajoute_score (LISTE_SCORE * liste_score,SCORE *nv_score_elt)
{
	//Inserer le nv elt au bon endroit
	SCORE * precedant = NULL;
	SCORE * courant = liste_score->premier;
	int deja_insere = 0;

	while ((courant!=NULL) && (deja_insere ==0))
	{
		if ( nv_score_elt->taille_serpent >= courant->taille_serpent)
		{
			//Le score a ajoute est superieur ou egale au score courant de la boucle, il va devant
			nv_score_elt->suivant = courant;
			if ( precedant != NULL )
				precedant->suivant = nv_score_elt;
			else // En tete de liste
			{
				liste_score->premier = nv_score_elt;
			}
			
			deja_insere = 1;
		}
		//On avance....
		precedant = courant;
		courant = courant->suivant;
	}
	//Il faut verifer si on doit ajouter le nv elt en fin ( si on ne l'a pas deja inserer )
	//en sortant de la boucle courant est NULL mais precedant pointe sur le dernier elt
	if ( deja_insere == 0 )
	{
		if ( precedant == NULL ) 
		{ //C'est le premier score que l'on ajoute
			liste_score->premier = nv_score_elt;
		}
		else
		{

			precedant->suivant = nv_score_elt;
		}
	}
	
	//Couper la liste au dela de la taille maxi (5)
	courant = liste_score->premier;
	int nb_elt=0;
	while (courant!=NULL)
	{
		nb_elt++;
		if ( nb_elt == 5 )
		{
			//On coupe le seul elt qui est en trop donc un seul free a faire
			free(courant->suivant);
			courant->suivant = NULL;
		}
		courant=courant->suivant;
	}
}

void libere_liste(LISTE_SCORE * liste)
{
	SCORE * courant = liste->premier;
	while ((courant!=NULL) ) {
		SCORE * suivant = NULL;
		suivant = courant->suivant;
		free(courant);
		courant = suivant;
	}
	
}


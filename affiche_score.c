#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"
#include "structure.h"
#include "jouer.h"
#include "loadmap.h"
#include "affiche_score.h"

void calcul_score(int *diamant_obtenu, int* centaine, int *dizaine, int *unite)
{
	int diamant=*diamant_obtenu;
	while (diamant>=100)
	{
		*centaine= *centaine +1;
		diamant= diamant-100;
	}
	while (diamant>=10)
	{
		*dizaine = *dizaine +1;
		diamant= diamant-10;
	}
	while (diamant>=1)
	{
		*unite = *unite +1;
		diamant= diamant-1;
	}
	 
	 return;
 }


void affiche_score(SDL_Surface *ecran, Ressource * sprite,int* diamant_obtenu,int* centaine, int*dizaine, int* unite)
{
	
	SDL_Rect positioncentaine, positiondizaine, positionunite;
	positioncentaine.x = 508;
	positioncentaine.y = 500;
	positiondizaine.x = 572;
	positiondizaine.y = 500;
	positionunite.x = 636;
	positionunite.y = 500;
	
	switch (*centaine)
	{
	case 1: 
	SDL_BlitSurface(sprite->chiffre1, NULL, ecran, &positioncentaine);
	break;
	case 2: 
	SDL_BlitSurface(sprite->chiffre2, NULL, ecran, &positioncentaine);
	break;
	case 3: 
	SDL_BlitSurface(sprite->chiffre3, NULL, ecran, &positioncentaine);
	break;
	case 4: 
	SDL_BlitSurface(sprite->chiffre4, NULL, ecran, &positioncentaine);
	break;
	case 5: 
	SDL_BlitSurface(sprite->chiffre5, NULL, ecran, &positioncentaine);
	break;
	case 6: 
	SDL_BlitSurface(sprite->chiffre6, NULL, ecran, &positioncentaine);
	break;
	case 7: 
	SDL_BlitSurface(sprite->chiffre7, NULL, ecran, &positioncentaine);
	break;
	case 8: 
	SDL_BlitSurface(sprite->chiffre8, NULL, ecran, &positioncentaine);
	break;
	case 9: 
	SDL_BlitSurface(sprite->chiffre9, NULL, ecran, &positioncentaine);
	break;
	
	default: break;
	}
	
	switch (*dizaine)
	{
	case 1: 
	SDL_BlitSurface(sprite->chiffre1, NULL, ecran, &positiondizaine);
	break;
	case 2: 
	SDL_BlitSurface(sprite->chiffre2, NULL, ecran, &positiondizaine);
	break;
	case 3: 
	SDL_BlitSurface(sprite->chiffre3, NULL, ecran, &positiondizaine);
	break;
	case 4: 
	SDL_BlitSurface(sprite->chiffre4, NULL, ecran, &positiondizaine);
	break;
	case 5: 
	SDL_BlitSurface(sprite->chiffre5, NULL, ecran, &positiondizaine);
	break;
	case 6: 
	SDL_BlitSurface(sprite->chiffre6, NULL, ecran, &positiondizaine);
	break;
	case 7: 
	SDL_BlitSurface(sprite->chiffre7, NULL, ecran, &positiondizaine);
	break;
	case 8: 
	SDL_BlitSurface(sprite->chiffre8, NULL, ecran, &positiondizaine);
	break;
	case 9: 
	SDL_BlitSurface(sprite->chiffre9, NULL, ecran, &positiondizaine);
	break;
	case 0:
	if(*diamant_obtenu>=100)
	{
		SDL_BlitSurface(sprite->chiffre0, NULL, ecran, &positiondizaine);
		break;
	}
	default: break;
	}
	
	switch (*unite)
	{
	case 1: 
	SDL_BlitSurface(sprite->chiffre1, NULL, ecran, &positionunite);
	break;
	case 2: 
	SDL_BlitSurface(sprite->chiffre2, NULL, ecran, &positionunite);
	break;
	case 3: 
	SDL_BlitSurface(sprite->chiffre3, NULL, ecran, &positionunite);
	break;
	case 4: 
	SDL_BlitSurface(sprite->chiffre4, NULL, ecran, &positionunite);
	break;
	case 5: 
	SDL_BlitSurface(sprite->chiffre5, NULL, ecran, &positionunite);
	break;
	case 6: 
	SDL_BlitSurface(sprite->chiffre6, NULL, ecran, &positionunite);
	break;
	case 7: 
	SDL_BlitSurface(sprite->chiffre7, NULL, ecran, &positionunite);
	break;
	case 8: 
	SDL_BlitSurface(sprite->chiffre8, NULL, ecran, &positionunite);
	break;
	case 9: 
	SDL_BlitSurface(sprite->chiffre9, NULL, ecran, &positionunite);
	break;
	case 0:
	if(*diamant_obtenu>=10 || *diamant_obtenu==0)
	{
		SDL_BlitSurface(sprite->chiffre0, NULL, ecran, &positionunite);
		break;
	}
	default: break;
	}
	
	return;
	
}
	
Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE); // Mauvaise allocation
    }

    element->nombre = -1;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

void ajoute_score (Liste * liste_score,Element *nouveau_score)
{
	//Inserer le nv elt au bon endroit
	Element * precedent = NULL;
	Element * courant = liste_score->premier;
	int deja_insere = 0;
	while ((courant!=NULL) && (deja_insere ==0))
	{
		if ( nouveau_score->nombre >= courant->nombre)
		{
			//Le score a ajoute est superieur ou egale au score courant de la boucle, il va devant
			nouveau_score->suivant = courant;
			if ( precedent != NULL )
				precedent->suivant = nouveau_score;
			else // En tete de liste
			{
				liste_score->premier = nouveau_score;
			}
			
			deja_insere = 1;
		}
		//On avance....
		precedent = courant;
		courant = courant->suivant;
	}
	//Il faut verifer si on doit ajouter le nv elt en fin ( si on ne l'a pas deja inserer )
	//en sortant de la boucle courant est NULL mais precedant pointe sur le dernier elt
	if ( deja_insere == 0 )
	{
		if ( precedent == NULL ) 
		{ //C'est le premier score que l'on ajoute
			liste_score->premier = nouveau_score;
		}
		else
		{

			precedent->suivant = nouveau_score;
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


void ecrire_score(Liste * liste_score) 
{
	
	FILE* fichier_score = NULL;
	//suppression du contenue des fichier et lecture
	fichier_score = fopen("score.txt","w+");
	// ajouter nouveau score
	Element * courant = liste_score->premier;
	int nb=0;
	while (courant != NULL)
	{ 
		fprintf(fichier_score,"%d ", courant->nombre) ;
		courant = courant->suivant ;
		nb++;
	}
	while (nb <5 )
	{
		fprintf(fichier_score,"-1 ");
		nb++;
	}
	fclose(fichier_score);
	return;
}


void lire_score(Liste * liste_score)
{
	FILE* fichier_score = NULL;
	int score[5];
	int i;

	fichier_score = fopen("score.txt","r");
	if ( fichier_score == NULL )
	{
		ecrire_score(liste_score);
		fichier_score = fopen("score.txt","r");
	}


	// recuperation du contenue du fichier pour le mettre dans liste_score
	fscanf(fichier_score,"%d %d %d %d %d ",
	&score[0],
	&score[1],
	&score[2],
	&score[3],
	&score[4] );

	for(i=0; i<5; i++)
	{

		Element* score_elt = (Element*)malloc(sizeof(Element));

		score_elt->nombre =score[i];
		
		ajoute_score( liste_score, score_elt );
	}

	fclose(fichier_score);
	return;
}

void aff_liste(Liste * liste)
{
	Element * courant = liste->premier;
	printf (" **** SCORE ****\n") ;
	while (courant != NULL)
	{ 
		printf ("score =%d\n",courant->nombre) ;
		courant = courant->suivant ;
	}
	printf("\n\n");
	return;
}


void libere_liste(Liste * liste)
{
	Element * courant = liste->premier;
	while ((courant!=NULL) ) 
	{
		Element * suivant = NULL;
		suivant = courant->suivant;
		free(courant);
		courant = suivant;
	}
	
}

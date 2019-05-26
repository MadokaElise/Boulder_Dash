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
	if(*diamant_obtenu>=10)
	{
		SDL_BlitSurface(sprite->chiffre0, NULL, ecran, &positionunite);
		break;
	}
	default: break;
	}
	
	return;
}
	

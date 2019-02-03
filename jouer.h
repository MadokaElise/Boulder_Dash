#ifndef JOUER
#define JOUER
	#include "structure.h"
	#include "constante.h"
	/* Lance le jeux */
	void jouer (SDL_Surface *ecran, Ressource * sprite) ;
	void mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *position);


#endif

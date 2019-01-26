#ifndef JOUER
#define JOUER
	
	#include "constante.h"
	/* Lance le jeux */
	void jouer (SDL_Surface *ecran) ;
	void mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *position);


#endif

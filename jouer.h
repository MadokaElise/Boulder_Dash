#ifndef JOUER
#define JOUER
	
	#include "constante.h"
	void jouer (char tabmap[NB_LIGNE][NB_COLONNE], SDL_Surface *ecran) ;
	void mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *position);


#endif
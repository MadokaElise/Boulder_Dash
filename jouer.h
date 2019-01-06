#ifndef JOUER
#define JOUER
	
	#include "constante.h"
	void jouer (char tab[NB_COLONNE][NB_LIGNE], SDL_Surface *ecran) ;
	void mouvement_joueur(char tab[NB_COLONNE][NB_LIGNE], int orientation, SDL_Rect *position);


#endif

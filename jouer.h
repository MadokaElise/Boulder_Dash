#ifndef JOUER
#define JOUER
	#include "structure.h"
	#include "constante.h"
	#include "affiche_score.h"
	/* Lance le jeux */
	int explosion_enemi (char tab[NB_LIGNE][NB_COLONNE], int i, int j, int mort);
	void jouer (SDL_Surface *ecran, Ressource * sprite,Liste *list_score) ;
	void mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *position, int *diamant_obtenu);
	int gestion_enemi(char tab[NB_LIGNE][NB_COLONNE], int mort);
	int gravitedirect (char tab[NB_LIGNE][NB_COLONNE], int mort);

#endif

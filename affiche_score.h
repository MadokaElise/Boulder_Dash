#ifndef AFFICHESCORE
#define AFFICHESCORE
	#include "structure.h"
	#include "constante.h"
	void calcul_score(int *diamant_obtenu, int* centaine, int *dizaine, int *unite);
	void affiche_score(SDL_Surface *ecran, Ressource * sprite,int* diamant_obtenu,int* centaine, int*dizaine, int* unite);
	
#endif

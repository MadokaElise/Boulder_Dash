#ifndef AFFICHESCORE
#define AFFICHESCORE
	#include "structure.h"
	#include "constante.h"
	
	/** STRUCTURES **/
	typedef struct Element Element;
	struct Element
	{
		int nombre;
		Element *suivant;
	};
	
	typedef struct Liste Liste;
	struct Liste
	{
		Element *premier;
	};
	
	
	void calcul_score(int *diamant_obtenu, int* centaine, int *dizaine, int *unite);
	void affiche_score(SDL_Surface *ecran, Ressource * sprite,int* diamant_obtenu,int* centaine, int*dizaine, int* unite);
	Liste *initialisation();
	void ajoute_score (Liste * liste_score,Element *nouveau_score);
	void ecrire_score(Liste * liste_score) ;
	void lire_score(Liste * liste_score);
	void aff_liste(SDL_Surface *ecran, Ressource *sprite,Liste * liste);
	void libere_liste(Liste * liste_score);
	void affiche_score2(SDL_Surface *ecran, Ressource * sprite,int nbr_score,int* diamant_obtenu,int* centaine, int*dizaine, int* unite);
#endif

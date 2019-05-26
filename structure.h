#ifndef structure
#define structure

#include <SDL_image.h>

typedef struct 
{
	// Création des surfaces
	SDL_Surface *terre;
	SDL_Surface *incassable;
	SDL_Surface *diamant;
	SDL_Surface *porte_ouverte;
	SDL_Surface *porte_ferme;
	SDL_Surface *bonhomme;
	SDL_Surface *rocher; 
	SDL_Surface *rocher_mvt;
	SDL_Surface *diamant_mvt;
	SDL_Surface *enemi;
	SDL_Surface *win;
	SDL_Surface *gameover;
	SDL_Surface *anime1_1;
	SDL_Surface *anime1_2;
	SDL_Surface *anime1_3;
	SDL_Surface *anime2_1;
	SDL_Surface *anime2_2;
	SDL_Surface *anime2_3;
	SDL_Surface *anime2_4;
	SDL_Surface *anime2_5;
	SDL_Surface *anime2_6;
	SDL_Surface *explosion;
	SDL_Surface *diamantscore;
	SDL_Surface *chiffre0;
	SDL_Surface *chiffre1;
	SDL_Surface *chiffre2;
	SDL_Surface *chiffre3;
	SDL_Surface *chiffre4;
	SDL_Surface *chiffre5;
	SDL_Surface *chiffre6;
	SDL_Surface *chiffre7;
	SDL_Surface *chiffre8;
	SDL_Surface *chiffre9;


} Ressource ;


#endif

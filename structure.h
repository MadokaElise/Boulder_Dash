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
	SDL_Surface *explosion;

} Ressource ;


#endif
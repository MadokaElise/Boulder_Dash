
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "constante.h"
#include "structure.h"

// Fonction qui affichage la map et retourne le nombre de diamant restant sur la map pour savoir si la porte doit s'ouvrir ou non

int affichage (char tab[NB_LIGNE][NB_COLONNE], SDL_Surface *ecran, Ressource * sprite)
{
	
	// Création de la variable position qui cible une surface
	SDL_Rect position;
	
	int i, j,Diamant_Restant; 
	
	// Placement des objets à l'écran
	// Compteur de points : si après balayage Diamant_Restant est égal à 0 alors la porte devient ouverte

    Diamant_Restant = 0;
        
    // Chargement des sprites
    
       
	// Balayage du tableau pour placer les sprites sur l'écran
	for (i = 0 ; i < NB_COLONNE ; i++)
    {
		for (j = 0 ; j < NB_LIGNE ; j++)
		{
			position.x = i * TAILLE_BLOC;
			position.y = j * TAILLE_BLOC;

			switch(tab[j][i])
			{
				case TERRE:
					SDL_BlitSurface(sprite->terre, NULL, ecran, &position);
                    break;
				case INCASSABLE:
					SDL_BlitSurface(sprite->incassable, NULL, ecran, &position);
					break;
				case BONHOMME:
					SDL_BlitSurface(sprite->bonhomme, NULL, ecran, &position);
					break;
				case DIAMANT:
					SDL_BlitSurface(sprite->diamant, NULL, ecran, &position);
					Diamant_Restant++;
                    break;
                case DIAMANTMVT:
					SDL_BlitSurface(sprite->diamant_mvt, NULL, ecran, &position);
					Diamant_Restant++;
                    break;
                case PORTE_OUVERTE:
					SDL_BlitSurface(sprite->porte_ouverte, NULL, ecran, &position);
					break;
				case PORTE_FERME:
					SDL_BlitSurface(sprite->porte_ferme, NULL, ecran, &position);
					break;
				case ROCHER:
					SDL_BlitSurface(sprite->rocher, NULL, ecran, &position);
					break;
				case ROCHERMVT:
					SDL_BlitSurface(sprite->rocher_mvt, NULL, ecran, &position);
					break;
				case ENEMI_BAS:
					SDL_BlitSurface(sprite->enemi, NULL, ecran, &position);
					break;
				case ENEMI_DROITE:
					SDL_BlitSurface(sprite->enemi, NULL, ecran, &position);
					break;
				case ENEMI_GAUCHE:
					SDL_BlitSurface(sprite->enemi, NULL, ecran, &position);
					break;
				case ENEMI_HAUT:
					SDL_BlitSurface(sprite->enemi, NULL, ecran, &position);
					break;
				case EXPLOSION:
					SDL_BlitSurface(sprite->explosion, NULL, ecran, &position);
					break;
                    
			}
		}
	}
	// Mise a jour de l'écran
	SDL_Flip(ecran);
	return Diamant_Restant;
}

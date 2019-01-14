
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "constante.h"




int affichage (char tab[NB_LIGNE][NB_COLONNE], SDL_Surface *ecran)
{
	// creation des surface
	SDL_Surface *terre = NULL, *incassable = NULL, *diamant = NULL, *porte_ouverte = NULL,
	*porte_ferme=NULL, *bonhomme=NULL, *rocher=NULL, *rocher_mvt=NULL, *diamant_mvt=NULL;
	// creation de la variable position qui cible une surface
	SDL_Rect position;
	
	int i, j,Diamant_Restant; 
	
	// Placement des objets à l'écran
	// Conteur de point si apres ballayage Diamant_Restant =0 alors 
	//la porte devient ouverte
    Diamant_Restant = 0;
        
    // Chargement des sprites
    terre = IMG_Load("Terre_1.bmp");
    incassable = IMG_Load("Terre_3.bmp");
    diamant= IMG_Load("diamant_2.bmp");
    porte_ouverte = IMG_Load("porte_ouverte.bmp");
    porte_ferme= IMG_Load("porte_ferme.bmp");
    bonhomme= IMG_Load("perso_1.bmp");
    rocher = IMG_Load("rocher_1.bmp");
    rocher_mvt = IMG_Load("rocher_mvt.bmp");
    diamant_mvt = IMG_Load("diamant_mvt.bmp");
       
	// Ballayage du tableau pour placer les sprites sur l'ecran
	for (i = 0 ; i < NB_COLONNE ; i++)
    {
		for (j = 0 ; j < NB_LIGNE ; j++)
		{
			position.x = i * TAILLE_BLOC;
			position.y = j * TAILLE_BLOC;

			switch(tab[j][i])
			{
				case TERRE:
					SDL_BlitSurface(terre, NULL, ecran, &position);
                    break;
				case INCASSABLE:
					SDL_BlitSurface(incassable, NULL, ecran, &position);
					break;
				case BONHOMME:
					SDL_BlitSurface(bonhomme, NULL, ecran, &position);
					break;
				case DIAMANT:
					SDL_BlitSurface(diamant, NULL, ecran, &position);
					Diamant_Restant++;
                    break;
                case DIAMANTMVT:
					SDL_BlitSurface(diamant_mvt, NULL, ecran, &position);
					Diamant_Restant++;
                    break;
                case PORTE_OUVERTE:
					SDL_BlitSurface(porte_ouverte, NULL, ecran, &position);
					break;
				case PORTE_FERME:
					SDL_BlitSurface(porte_ferme, NULL, ecran, &position);
					break;
				case ROCHER:
					SDL_BlitSurface(rocher, NULL, ecran, &position);
					break;
				case ROCHERMVT:
					SDL_BlitSurface(rocher_mvt, NULL, ecran, &position);
					break;
                    
			}
		}
	}
	SDL_Flip(ecran);
	return Diamant_Restant;
}

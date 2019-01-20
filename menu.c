#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "constante.h"
#include "affichage.h"
#include "jouer.h"
#include "menu.h"


void menu(int* choix, SDL_Surface *ecran)
{
	int x=0,y=0;
	
	SDL_Surface *menu = NULL, *boutonjouer = NULL, *boutonscore = NULL, *boutonaide = NULL, *boutonfin = NULL;
	
	SDL_Event event;
	SDL_Rect positionMenu, positionBoutonJouer,positionBoutonFin, positionBoutonScore, positionBoutonAide;
	
	// Chargement des sprites
	/** a sortir à l'avenir**/
		
    menu = IMG_Load("menu.bmp");
    boutonjouer = IMG_Load("boutonjouer.bmp");
    boutonscore = IMG_Load("boutonscore.bmp");
    boutonaide = IMG_Load("boutonaide.bmp");
    boutonfin = IMG_Load("boutonfin.bmp");
    
    // Position des boutons 
    /** Taille boutons: 220*75 **/
    positionMenu.x = 0;
    positionMenu.y = 0;
    positionBoutonJouer.x = 85;
    positionBoutonJouer.y = 340;
    positionBoutonScore.x = 390;
    positionBoutonScore.y = 340;
    positionBoutonAide.x = 85;
    positionBoutonAide.y = 500;
    positionBoutonFin.x = 390;
    positionBoutonFin.y = 500;
	
	// Affichage
	SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
	SDL_BlitSurface(boutonjouer, NULL, ecran, &positionBoutonJouer);
	SDL_BlitSurface(boutonscore, NULL, ecran, &positionBoutonScore);
	SDL_BlitSurface(boutonaide, NULL, ecran, &positionBoutonAide);
	SDL_BlitSurface(boutonfin, NULL, ecran, &positionBoutonFin);
	SDL_Flip(ecran);
	while (*choix==0)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *choix = 1; //QUITTER
                break;
           
            case SDL_MOUSEBUTTONUP: // Clic de la souris
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					x=event.button.x;
					y=event.button.y;
					
					if(((84 < x)&&(x < 306))&&((339 < y)&&(y < 416)))
					{
						*choix = 2; //JOUER
						break;
					}else if(((389 < x)&&(x < 611))&&((339 < y)&&(y < 416)))
					{
						*choix = 3; // SCORE
						break;
					}else if(((84 < x)&&(x < 306))&&((499 < y)&&(y < 576)))
					{
						*choix = 4; // AIDE
						break;
					}else if(((389 < x)&&(x < 611))&&((499 < y)&&(y < 576)))
					{
						*choix = 5; // FIN
						break;
					}
				}
				
			default:;
		     
        }
     }
     
     return;
 }

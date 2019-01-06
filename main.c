#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "constante.h"
#include "affichage.h"
#include "jouer.h"


void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int main(void)
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    //SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1, diamant;
    char map[NB_COLONNE][NB_LIGNE] = 
	{
	{'i','i','i','i','r','t','t','d','t','t'},
	{'t','t','r','i',' ','t','t','t','i','i'},
	{'b','t','t','i','t','t','t','i','i','i'},
	{'t','t','t','t','t','t','t','t','i','i'},
	{'t','r','r','i','t','t','t','f','i','i'},
	{'i','i','i','i','t','t','t','t','i','i'},
	{'d','r','r','r','t','t','t',' ','r','t'},
	{'t','t','t','t','t','d','t',' ','r','r'},
	{'t','t','t','t','t','t','t','t','r','r'},
	{'r','r','r','r','t','t','t','t','r','r'}
	};

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("perso_1.bmp"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Boulder Dash", NULL);
	int x=1;

	while (x<10)
	{
		printf("truc\n");
	jouer(map , ecran);
	x++;
	}
	
    //menu = IMG_Load("menu.jpg");
    //positionMenu.x = 0;
    //positionMenu.y = 0;
/*
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        //continuer = 0;
                        break;
                    case SDLK_q: // Demande à jouer
                        jouer(map , ecran);
                        break;
                    case SDLK_KP2: // Demande l'éditeur de niveaux
                        //editeur(ecran);
                        break;
					default:
						break;
                }
                break;
                
        }
     }
*/
        // Effacement de l'écran
        //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        //SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        //SDL_Flip(ecran);
    
	
    //SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}

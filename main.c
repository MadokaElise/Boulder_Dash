
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "constante.h"
#include "affichage.h"
#include "jouer.h"
#include "menu.h"


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
	int choix=0,x,y;
	SDL_Event event;
    SDL_Surface *ecran = NULL, *regle = NULL, *boutonfin = NULL;
	SDL_Rect positionRegle, positionBoutonFin;
	SDL_WaitEvent(&event);
	
    char map[NB_LIGNE][NB_COLONNE] = 
	{
	{'t','t','t','t','t','t',' ','t','t','d','t','r',' ','t','t','t','t','t','r','t','r','t','t','t','t','t','t','t',' ','t','t','t','t','r','t','t','t','t'},
	{'t','r','b','r','t','t','t','t','t','t',' ','t','t','t','t','t','t','t','t','t','r','d','t','t','r','t','t','t','t',' ','t','t','t','t','t',' ','t','t'},
	{'t','t','t','t','t','t','t','t','t','t',' ','t','t',' ','t','t','t','t','t','r','t','r','t','t','r','t','t','t','t','t','t','t','t','r','t','t','t','t'},
	{'r','t',' ',' ','t','t','t','t','t','t','t','t','t','r','t','t','t','t','t','t','r','t','t','r','t','t','t','t','t','r','t','t','r','t','t','t','t','t'},
	{'r','t','r','r','t','t','t','t','t','t','t','t','t','r','r','t','t','r','t','t','t','t','t','t','t','t','t','r','t','t','t','t','t','r','t','r',' ','t'},
	{'t','t','t','r','t','t','r','t','t','t','t','t','t','t','t','r','t','t','t','t','t','r','t',' ','r','t','t','t','t','t','t','t','t','r','t','r','r','t'},
	{'i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','t','t','t','r','t','t','r','t'},
	{'t',' ','t','t','t','t','t','t','d','t',' ','t','t','r','t','r','t','t','t','t','t','t','t','t','t','t','d','t','r',' ','t','t','t','t','t','t','r','t'},
	{'t','t','d','t','t','t','t','t','r','t','t','t','t','t',' ','t','t','t','t','t','t','t','t','r',' ',' ','r','t','t','d','t','t','t','t','r','t','t','t'},
	{'t','t','t','r','t','t','r','t','r','t','t','t','t','t','t','t','t','t','t','t','t','t','t','r','r','t','r','t','t','r','t','t','t','t','t','t','t','t'},
	{'t',' ','t','t','t','t','t','r','t','t','t','t','t','t','t','t','r','r','t','t','t','t','t','t','t','t','r','t','t','r','t','d','t','t','t','t',' ','t'},
	{'t','r','t','t','t','t','t','r','t',' ',' ','t','t','t','t','t','r','t','r','d','t','t','d','t','t','t','t','r','t','t','t','r','t','t','d','t','r','t'},
	{'t','d','r','t',' ','t','t','t','t','t','t','t','t','t','t','t','t','r','r','r','t','t','r','t','t','t','t','t','t','t','t','d','t','t','t','t','t','r'},
	{'t','t','t','t','t','t','t','t','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i'},
	{' ',' ','t','t','t','t','t','t','t','t','t',' ','t','t','t','d','t','t','t','t','r','t','t','t','t','t','r','t','t','t','r','t','t','t','t','t','t','t'},
	{'r',' ','t','t','t','t','t','t','t','t','t','r','r','t','t','r','t','t','t','t','t','t','t','t','r','t','t','t','t','t','t','r','t','r',' ','t','t','f'},
	{'t','r','t','t','r','t','t','t','t','t','t','t','t','r','t','t','t','t','t','r','t',' ',' ','t','t','t','t','d','t','t','t','r','t','r','r','t','t','t'},
	{'t','t','t','t','r','d','t','t',' ','t','t','t','t','t','t','t','t','r','t','t','t','t','t','t','r','t','r','d','t','t','t','t','t','t','r','t','t','t'},
	{'t','t','t',' ','t','t',' ','t','r','t','t','r','t','r','r','t','t','t','t','t','t','t','t','t','r','t','r','d','t','t','t','t','t','t','r','t','t','r'},
	{'t','d','t','t','t','t','r','t','t','t','t','t',' ','t','t','t','t','t','t','t','t','t',' ','t','r','t','t','r','t','t','t','t','r','t','t','t','r','t'},
	};
	
	
    SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetIcon(IMG_Load("icone.ico"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Boulder Dash", NULL);
	
		do
		{
			choix=0;
			menu(&choix, ecran);
			
			if((choix==1)||(choix==5))
			{
				choix=5;
				//SDL_Quit();
			}else if(choix==3)
			{
				SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
				//	affichage score
			}else if(choix==4)
			{
				// affichage aide
				
				SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
				regle = IMG_Load("regle.bmp");
				boutonfin = IMG_Load("boutonfin.bmp");
				positionRegle.x = 0;
				positionRegle.y = 0;
				positionBoutonFin.x=460;
				positionBoutonFin.y=515;
				
				SDL_BlitSurface(regle, NULL, ecran, &positionRegle);
				SDL_BlitSurface(boutonfin, NULL, ecran, &positionBoutonFin);
				SDL_Flip(ecran);
				
				while (choix==4)
				{	
					SDL_WaitEvent(&event);
					switch(event.type)
					{	
						case SDL_QUIT:
						choix=5;
						//SDL_Quit();//QUITTER
						break;
						case SDL_MOUSEBUTTONUP:
							if (event.button.button == SDL_BUTTON_LEFT)
							{
								x=event.button.x;
								y=event.button.y;
								
								if(((460 < x)&&(x < 680))&&((515 < y)&&(y < 590)))
								{
							
								choix=10;
								break;								
								}
							}
							break;
						default:;
					}
				}
			
		
		
		
		}else if(choix==2)
		{
			affichage(map, ecran);
			//pause();
			
			SDL_Flip(ecran);
			jouer(ecran);
			
		}
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		
	}while((choix!=1)&&(choix!=5));	
		
	SDL_Quit();
	return EXIT_SUCCESS;
	
}

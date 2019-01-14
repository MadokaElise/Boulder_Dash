#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>
    #define TAILLE_BLOC   32 // Taille d'un bloc (carré) en pixels
    #define NB_COLONNE    38 // nombre de colonne du palateau
    #define NB_LIGNE      20 // nombre de ligne du plateau
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_COLONNE
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_LIGNE

#define INCASSABLE      'i'
	#define ROCHER          'r'
	#define DIAMANT         'd'
	#define TERRE           't'
	#define BONHOMME        'b'
	#define PORTE_FERME     'f'
	#define PORTE_OUVERTE   'o'
	#define GALERIE         ' '
	

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



int main (void)
{
	char map[20][38] = 
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
	SDL_Surface *ecran = NULL;
	SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("perso_1.bmp"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	// creation des surface
	SDL_Surface *terre = NULL, *incassable = NULL, *diamant = NULL, *porte_ouverte = NULL,
	*porte_ferme=NULL, *bonhomme=NULL, *rocher=NULL;
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
       
	// Ballayage du tableau pour placer les sprites sur l'ecran
	for (i = 0 ; i < 38 ; i++)
    {
		for (j = 0 ; j < 20 ; j++)
		{
			position.x = i * 32;
			position.y = j * 32;

			switch(map[j][i])
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
                case PORTE_OUVERTE:
					SDL_BlitSurface(porte_ouverte, NULL, ecran, &position);
					break;
				case PORTE_FERME:
					SDL_BlitSurface(porte_ferme, NULL, ecran, &position);
					break;
				case ROCHER:
					SDL_BlitSurface(rocher, NULL, ecran, &position);
					break;
                    
			}
		}
	}
	SDL_Flip(ecran);
	pause();
	return 0;
}


//gcc -Wall map2.c -o aff -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image

/* char map[NB_COLONNE][NB_LIGNE] = 
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
	* /

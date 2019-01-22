#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"

// Gestion de la gravité d'un rocher dans le vide et d'un rocher en équilibre sur un autre
// (rocher et dimant subissent les mêmes règles de gravité)
int gravitedirect (char tab[NB_LIGNE][NB_COLONNE], int mort)
{
	
	int i,j;
	// Balayage de la map à l'envers à la recherche de rocher et de diamant
	for (i = NB_LIGNE ; i>=0 ; i--)
    {
        for (j = NB_COLONNE ; j>=0 ; j--)
        {
			// Recherche d'un rocher (ou diamant) qui va devoir etre changé en rocher (ou diamant) en mouvement
            if ( (tab[i][j] == ROCHER) || (tab[i][j] == DIAMANT ))
            {
				// Test si le rocher (ou diamant) se trouve dans le vide
                if (tab[i+1][j] == GALERIE) 
                {
					
					if  (tab[i][j] == ROCHER)
					{
						tab[i+1][j]=ROCHERMVT;
					}
					else if  (tab[i][j] == DIAMANT)
					{
						tab[i+1][j]=DIAMANTMVT;
					}
					tab[i][j]=GALERIE;
					
				}
				// Test si le rocher (ou diamant) est en équillibre sur un autre et si des galeries se trouvent autour de lui à droite puis à gauche
                if ( (tab[i+1][j+1] == GALERIE) && (tab[i][j+1] == GALERIE) && ((tab[i+1][j]==ROCHER) || (tab[i+1][j]==DIAMANT) ) )
                {
					
					if  (tab[i][j] == ROCHER)
					{
						tab[i][j+1]=ROCHERMVT;
					}
					else if  (tab[i][j] == DIAMANT)
					{
						tab[i][j+1]=DIAMANTMVT;
					}
					tab[i][j]=GALERIE;
				}
				if ( (tab[i+1][j-1] == GALERIE) && (tab[i][j-1] == GALERIE) &&((tab[i+1][j]==ROCHER) || (tab[i+1][j]==DIAMANT) ) )
                {
					
					if  (tab[i][j] == ROCHER)
					{
						tab[i][j-1]=ROCHERMVT;
					}
					else if  (tab[i][j] == DIAMANT)
					{
						tab[i][j-1]=DIAMANTMVT;
					}
					tab[i][j]=GALERIE;
				}
                
            }
            // Gestion des rochers (ou diamants) en mouvement 
            if ( (tab[i][j] == ROCHERMVT) || (tab[i][j] == DIAMANTMVT ))
            {
				// Test si le rocher (ou diamant) reste en mouvement car toujours dans le vide
				if (tab[i+1][j] == GALERIE) 
                {
					
					if  (tab[i][j] == ROCHERMVT)
					{
						tab[i+1][j]=ROCHERMVT;
					}
					else if  (tab[i][j] == DIAMANTMVT)
					{
						tab[i+1][j]=DIAMANTMVT;
					}
					tab[i][j]=GALERIE;
					
				}
				// Test si le rocher (ou diamant) tombe sur un obsatacle, sa chute s'arrete
                if (tab[i+1][j] != GALERIE) 
                {
					if (tab[i+1][j] == BONHOMME)
					{
						return mort =1;
					}
					if  (tab[i][j] == ROCHERMVT)
					{
						tab[i][j] = ROCHER;
					}
					else if  (tab[i][j] == DIAMANTMVT)
					{
						tab[i][j] =DIAMANT;
					}
					
				}
			}            
        }
    }
    return mort = 0;
}

   
void mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *pos)
{
	
	switch(orientation)
    {
        case GAUCHE: /** Y est l'abscisse **/
			// Vérification :
			// => dépassement de la zone de jeu
			// => présence d'un bloc incassable
			// => présence d'un rocher
			// => porte fermée
			if ((pos->y - 1 < 0) || (tab[pos->x][pos->y - 1]== INCASSABLE)|| (tab[pos->x][pos->y - 1]== ROCHER)|| (tab[pos->x][pos->y - 1]== PORTE_FERME))
			{
				// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
				break;
			}
			// Si la case est accessible, le joueur va à gauche
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x][pos->y-1]=BONHOMME;
			pos->y--;
			break;
		case DROITE:
			// Vérification :
			// => dépassement de la zone de jeu
			// => présence d'un bloc incassable
			// => présence d'un rocher
			// => porte fermée
			if ((pos->y + 2 > NB_COLONNE) || (tab[pos->x][pos->y + 1]== INCASSABLE)|| (tab[pos->x][pos->y + 1]== ROCHER)|| (tab[pos->x][pos->y + 1]== PORTE_FERME))
			{
				// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
				break;
			}
			// Si la case est accessible, le joueur va à droite
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x][pos->y+1]=BONHOMME;
			pos->y++;
			break;
		case HAUT:
			// Vérification :
			// => dépassement de la zone de jeu
			// => présence d'un bloc incassable
			// => présence d'un rocher
			// => porte fermée
			if ((pos->x - 1 < 0) || (tab[pos->x - 1][pos->y]== INCASSABLE)|| (tab[pos->x - 1][pos->y]== ROCHER)|| (tab[pos->x - 1][pos->y]== PORTE_FERME))
			{
				// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
				break;
			}
			// Si la case est accessible, le joueur monte
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x - 1][pos->y]=BONHOMME;
			pos->x--;
			break;
		case BAS:
			// Vérification :
			// => dépassement de la zone de jeu
			// => présence d'un bloc incassable
			// => présence d'un rocher
			// => porte fermée
			if ((pos->x +2 >NB_LIGNE) || (tab[pos->x + 1][pos->y]== INCASSABLE)|| (tab[pos->x + 1][pos->y]== ROCHER)|| (tab[pos->x + 1][pos->y]== PORTE_FERME))
			{
				// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
				break;
			}
			// Si la case est accessible, le joueur descend
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x + 1][pos->y]=BONHOMME;
			pos->x++;
			break;
		}
		
}

void jouer (SDL_Surface *ecran) 
{
	void SDL_Delay(Uint32 ms);
	SDL_Surface *gameover = NULL;
	gameover = IMG_Load("game_over.bmp");
	SDL_Rect positiongameover;
	positiongameover.x= 300;
	positiongameover.y=50;
	int i, j, x,y, diamant, continuer=0, mort ;
	// Initialisation de la map
	char tab[NB_LIGNE][NB_COLONNE] = 
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
	
	SDL_Rect  position_joueur;
	SDL_Event event;
	

	diamant = affichage(tab,ecran);
	
	// Recherche de la position de départ du bonhomme
	for (i = 0 ; i < NB_COLONNE ; i++)
    {
        for (j = 0 ; j < NB_LIGNE ; j++)
        {
            if (tab[i][j] == BONHOMME) 
            {
                position_joueur.x = i;
                position_joueur.y = j;
                
            }
        }
    }
	
    // Activation de la répétition des touches
    SDL_EnableKeyRepeat(100, 100);

    while (continuer==0)
    {
		
        SDL_WaitEvent(&event);
       
		switch(event.type)
		{
			
			case SDL_QUIT:
				continuer = 1;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					     // Quitter la fenêtre de jeu et retourner au menu principal
						continuer = 1;
						break;
					case SDLK_UP:
						mouvement_joueur(tab, HAUT, &position_joueur);
						break;
					case SDLK_DOWN:
						mouvement_joueur(tab, BAS, &position_joueur);
						break;
					case SDLK_RIGHT:
						mouvement_joueur(tab, DROITE, &position_joueur);
						break;
					case SDLK_LEFT:
						mouvement_joueur(tab, GAUCHE, &position_joueur);
						break;
					default:
						break;
				}
				
				break;
				
		}
		
		mort =gravitedirect(tab, mort);
	
		if (mort == 1)
		{
			// Quitter la fenêtre de jeu et retourner au menu principal
			continuer=1;
			SDL_BlitSurface(gameover, NULL, ecran, &positiongameover);
			SDL_Flip(ecran);
			// Affichage de l'image "gameover" pendant 2,5 secondes
			SDL_Delay(2500);
			
			
		}
		
		// Affichage de l'écran de jeu
		diamant = affichage(tab,ecran);
		
		SDL_Flip(ecran);
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // Affichage de l'écran de jeu
		diamant = affichage(tab,ecran);
		SDL_Flip(ecran);

        // Si on n'a trouvé aucun diamant sur la carte, c'est que la porte s'ouvre
        if (diamant==0)
        {
			
			// Recherche de la position de de la porte fermée pour la rendre ouverte
			for (i = 0 ; i < NB_COLONNE ; i++)
			{
				for (j = 0 ; j < NB_LIGNE ; j++)
				{
					if (tab[j][i] == PORTE_FERME) 
					{
						// La porte fermeée est remplacée par la porte ouverte
						tab[j][i] = PORTE_OUVERTE;
						y=i;
						x=j;
					
					}
				}
			}
		}

		if ( (position_joueur.x==x) && (position_joueur.y==y) )
		{
			// Quitte la fenêtre de jeu car le joueur a gagné et retourne au menu principal
			continuer =1;
		}

	}
}


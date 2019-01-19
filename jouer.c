#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"

// Gestion de la gravite rocher dans le vide
// Rocher en equilibre sur un autre
//( rocher et diamant subissent les meme regle de gravite)
int gravitedirect (char tab[NB_LIGNE][NB_COLONNE], int mort)
{
	
	int i,j;
	// ballayage de la map  à du bas vers le haut à la rocher de rocher et diamant
	for (i = NB_LIGNE ; i>=0 ; i--)
    {
        for (j = NB_COLONNE ; j>=0 ; j--)
        {
			// recherche de diamant qui va devoir etre chager en rocher en mouvement
            if ( (tab[i][j] == ROCHER) || (tab[i][j] == DIAMANT ))
            {
				// test si le rocher chutent toud droit car il se trouve dans le vide
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
				// test si le rocher est en equillibre sur un autre ou non et si des galeries
                //se trouve autour de lui a droite ou a gauche
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
            // gestion des rochers en mouvement
            if ( (tab[i][j] == ROCHERMVT) || (tab[i][j] == DIAMANTMVT ))
            {
				// test si le rocher reste en mouvement car toujours en suspention dans le vide
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
				// si le rocher tombe sur un obsatacle sa chute s'arrete
                if (tab[i+1][j] != GALERIE) 
                {
					if (tab[i+1][j] == BONHOMME)
					{
						printf ("game over !! \n");
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
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermee:
			if ((pos->y - 1 < 0) || (tab[pos->x][pos->y - 1]== INCASSABLE)|| (tab[pos->x][pos->y - 1]== ROCHER)|| (tab[pos->x][pos->y - 1]== PORTE_FERME))
			{
				// si la case ou le joueur veut se rendre est interdite on sort de la boucle
				break;
			}
			// si la case est accessible le joueur va gauche
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x][pos->y-1]=BONHOMME;
			pos->y--;
			break;
		case DROITE:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermee:
			if ((pos->y + 2 > NB_COLONNE) || (tab[pos->x][pos->y + 1]== INCASSABLE)|| (tab[pos->x][pos->y + 1]== ROCHER)|| (tab[pos->x][pos->y + 1]== PORTE_FERME))
			{
				// si la case ou le joueur veut se rendre est interdite on sort de la boucle
				break;
			}
			// si la case est accessible le joueur va droite
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x][pos->y+1]=BONHOMME;
			pos->y++;
			break;
		case HAUT:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermee:
			if ((pos->x - 1 < 0) || (tab[pos->x - 1][pos->y]== INCASSABLE)|| (tab[pos->x - 1][pos->y]== ROCHER)|| (tab[pos->x - 1][pos->y]== PORTE_FERME))
			{
				// si la case ou le joueur veut se rendre est interdite on sort de la boucle
				break;
			}
			// si la case est accessible le joueur monte
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x - 1][pos->y]=BONHOMME;
			pos->x--;
			break;
		case BAS:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermee:
			if ((pos->x +2 >NB_LIGNE) || (tab[pos->x + 1][pos->y]== INCASSABLE)|| (tab[pos->x + 1][pos->y]== ROCHER)|| (tab[pos->x + 1][pos->y]== PORTE_FERME))
			{
				// si la case ou le joueur veut se rendre est indertite on sort de la boucle
				break;
			}
			// si la case est accessible le joueur descend
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
	// initialisation de la map
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
	
	// Recherche de la position de depart du bonhomme
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
				 
        printf(" continuer %d\n",continuer);
		
				continuer = 1;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = 1; // quitter la fenetre de jeu et retourner au menu principale
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
			// on quitte la page de jeu pour retourner au menu principale
			continuer=1;
			SDL_BlitSurface(gameover, NULL, ecran, &positiongameover);
			SDL_Flip(ecran);
			// l'image "gameover" s'affiche 2,5 secondes
			SDL_Delay(2500);
			
			
		}
		
		// Affichage de l'ecran de jeu
		diamant = affichage(tab,ecran);
		
		SDL_Flip(ecran);
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // Affichage de l'ecran de jeu
		diamant = affichage(tab,ecran);
		SDL_Flip(ecran);

        // Si on n'a trouvé aucun diamant sur la carte, c'est que la porte s'ouvre
        if (diamant==0)
        {
			
			// Recherche de la position de de la porte ferme pour la rendre ouverte
			for (i = 0 ; i < NB_COLONNE ; i++)
			{
				for (j = 0 ; j < NB_LIGNE ; j++)
				{
					if (tab[j][i] == PORTE_FERME) 
					{
						// la porte ferme est remplacer par la porte ouverte
						tab[j][i] = PORTE_OUVERTE;
						y=i;
						x=j;
					
					}
				}
			}
		}

		if ( (position_joueur.x==x) && (position_joueur.y==y) )
		{
			// quitte la fenetre de jeu car le joueur a gagné et retourne au menu principal
			continuer =1;
		}

	}
}


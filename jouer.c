#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"

void mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *pos)
{
	
	switch(orientation)
    {
        case GAUCHE:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermer:
			if ((pos->y - 1 < 0) || (tab[pos->x][pos->y - 1]== INCASSABLE)|| (tab[pos->x][pos->y - 1]== ROCHER)|| (tab[pos->x][pos->y - 1]== PORTE_FERME))
			{
				// si la case ou le joeur veut se rendre est indertite on sort de la boucle
				break;
			}
			// si la case est accecible le joeur monte
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x][pos->y-1]=BONHOMME;
			pos->y--;
			break;
		case DROITE:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermer:
			if ((pos->y + 1 < 0) || (tab[pos->x][pos->y + 1]== INCASSABLE)|| (tab[pos->x][pos->y + 1]== ROCHER)|| (tab[pos->x][pos->y + 1]== PORTE_FERME))
			{
				// si la case ou le joeur veut se rendre est indertite on sort de la boucle
				break;
			}
			// si la case est accecible le joeur descent
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x][pos->y+1]=BONHOMME;
			pos->y++;
			break;
		case HAUT:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermer:
			if ((pos->x - 1 < 0) || (tab[pos->x - 1][pos->y]== INCASSABLE)|| (tab[pos->x - 1][pos->y]== ROCHER)|| (tab[pos->x - 1][pos->y]== PORTE_FERME))
			{
				// si la case ou le joeur veut se rendre est indertite on sort de la boucle
				break;
			}
			// si la case est accecible le joeur monte
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x - 1][pos->y]=BONHOMME;
			pos->x--;
			break;
		case BAS:
			// Verification
			// Depacement de la zone de jeu ou bloc incassable ou rocher ou la porte fermer:
			if ((pos->x + 1 < 0) || (tab[pos->x + 1][pos->y]== INCASSABLE)|| (tab[pos->x + 1][pos->y]== ROCHER)|| (tab[pos->x + 1][pos->y]== PORTE_FERME))
			{
				// si la case ou le joeur veut se rendre est indertite on sort de la boucle
				break;
			}
			// si la case est accecible le joeur monte
			tab[pos->x ][pos->y]=GALERIE;
			tab[pos->x + 1][pos->y]=BONHOMME;
			pos->x++;
			break;
		}
		
}

void jouer (char tab[NB_LIGNE][NB_COLONNE],SDL_Surface *ecran) 
{
	
	int i, j, x,y, diamant, continuer=0 ;
	
	SDL_Rect  position_joueur;
	SDL_Event event;
	
	printf("truc4\n");
	
	diamant = affichage(tab,ecran);
	
	// REcherche de la position de depart du bonhomme
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
			printf("swtich\n");
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
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
		
		// Affichage de l'ecran de jeu
		diamant = affichage(tab,ecran);
		SDL_Flip(ecran);
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // Affichage de l'ecran de jeu
		diamant = affichage(tab,ecran);
		SDL_Flip(ecran);
		//("nb diamant %d\n", diamant);
        // Si on n'a trouvé aucun diamant sur la carte, c'est que la porte s'ouvre
        if (diamant==0)
        {
			printf("gagner\n");
			// Recherche de la position de de la porte ferme pour la rendre ouverte
			for (i = 0 ; i < NB_COLONNE ; i++)
			{
				for (j = 0 ; j < NB_LIGNE ; j++)
				{
					if (tab[j][i] == PORTE_FERME) 
					{
						tab[j][i] = PORTE_OUVERTE;
						y=i;
						x=j;
						printf("i , j %d %d\n",x,y);
					}
				}
			}
		}
		//printf("joueur : %d %d\n",position_joueur.x,position_joueur.y );
		
		if ( (position_joueur.x==x) && (position_joueur.y==y) )
		{
			//printf("fini\n");
			continuer =1;
			
		}
					
			
		
		
		

            //placer porte ouverte dans le tableur

       
        



        SDL_Flip(ecran);
	}
}




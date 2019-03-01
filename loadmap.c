#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"
#include "structure.h"
#include "jouer.h"
#include "loadmap.h"

void load_map(char tab[NB_LIGNE][NB_COLONNE], int niveau)
{
	FILE* fichier=NULL;
	int i,j;
	char caractereActuel='0';
	
	/** CHOIX DE LA MAP **/
	switch(niveau)
	{
		
		case 1:
		fichier = fopen("map1.txt", "r");
		break;
		case 2:
		fichier = fopen("map5.txt", "r");
		break;
		case 3:
		fichier = fopen("map3.txt", "r");
		break;
		case 4:
		fichier = fopen("map4.txt", "r");
		break;
		case 5:
		fichier = fopen("map2txt", "r");
		break;
		
		default:;
	}
	 if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        for(i=0;i<NB_LIGNE;i++)
        {
			for(j=0;j<NB_COLONNE;j++)
			{
				caractereActuel = fgetc(fichier);
				tab[i][j]=caractereActuel;
			}
		}
			         
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
    
	return;
}

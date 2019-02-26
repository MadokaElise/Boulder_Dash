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

char** load_map()
{
	FILE* fichier=NULL;
	int i,j;
	char caractereActuel='0';
	char tab[NB_LIGNE][NB_COLONNE];
	fichier = fopen("map1.txt", "r");
	
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
    
	return tab;
}

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"
#include "structure.h"
#include "loadmap.h"

char** load_map()
{
	FILE* fichier=NULL;
	int i,j;
	char caractereActuel='0';
	
	int ** tab = NULL;
	int i=0;

	tab = (int**)malloc(dim1*sizeof(int*));
	for(i=0;i<dim1;i++)
	{
		tab[i] = (int*)malloc(dim2*sizeof(int));
	}
	
	fichier = fopen("map1.txt", "r");
	
	 if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        for(i=0;i<NB_LIGNE;i++)
        {
			for(j=0;j<NB_COLONNE;j++)
			{
				caractereActuel = fgetc(fichier);
				map[i][j]=caractereActuel;

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

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "affichage.h"
#include "constante.h"
#include "structure.h"
#include "loadmap.h"
#include "affiche_score.h"

int explosion_enemi(char tab[NB_LIGNE][NB_COLONNE], int i, int j, int mort)
{

	if (tab[i][j] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i][j + 1] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i][j - 1] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i + 1][j + 1] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i + 1][j] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i + 1][j-1] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i - 1][j] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i - 1][j - 1] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i + 1][j - 1] == BONHOMME)
	{
		mort = 1;
	}
	if (tab[i - 1][j + 1] == BONHOMME)
	{
		mort = 1;
	}

	tab[i][j] = EXPLOSION;
	tab[i + 1][j + 1] = EXPLOSION;
	tab[i + 1][j] = EXPLOSION;
	tab[i][j + 1] = EXPLOSION;
	tab[i - 1][j] = EXPLOSION;
	tab[i][j - 1] = EXPLOSION;
	tab[i - 1][j - 1] = EXPLOSION;
	tab[i - 1][j + 1] = EXPLOSION;
	tab[i + 1][j - 1] = EXPLOSION;

	return mort;
}

// Gestion de la gravité d'un rocher dans le vide et d'un rocher en équilibre sur un autre
// (rocher et dimant subissent les mêmes règles de gravité)
int gravitedirect(char tab[NB_LIGNE][NB_COLONNE], int mort)
{

	int i, j;
	// Balayage de la map à l'envers à la recherche de rocher et de diamant
	for (i = NB_LIGNE; i >= 0; i--)
	{
		for (j = NB_COLONNE; j >= 0; j--)
		{
			if (tab[i][j] == EXPLOSION)
			{
				tab[i][j] = GALERIE;
			}
			// Recherche d'un rocher (ou diamant) qui va devoir etre changé en rocher (ou diamant) en mouvement
			if ((tab[i][j] == ROCHER) || (tab[i][j] == DIAMANT))
			{
				// Test si le rocher (ou diamant) se trouve dans le vide
				if (tab[i + 1][j] == GALERIE)
				{

					if (tab[i][j] == ROCHER)
					{
						tab[i + 1][j] = ROCHERMVT;
					}
					else if (tab[i][j] == DIAMANT)
					{
						tab[i + 1][j] = DIAMANTMVT;
					}
					tab[i][j] = GALERIE;
				}
				// Test si le rocher (ou diamant) est en équillibre sur un autre et si des galeries se trouvent autour de lui à droite puis à gauche
				if ((tab[i + 1][j + 1] == GALERIE) && (tab[i][j + 1] == GALERIE) && ((tab[i + 1][j] == ROCHER) || (tab[i + 1][j] == DIAMANT)))
				{

					if (tab[i][j] == ROCHER)
					{
						tab[i][j + 1] = ROCHERMVT;
					}
					else if (tab[i][j] == DIAMANT)
					{
						tab[i][j + 1] = DIAMANTMVT;
					}
					tab[i][j] = GALERIE;
				}
				if ((tab[i + 1][j - 1] == GALERIE) && (tab[i][j - 1] == GALERIE) && ((tab[i + 1][j] == ROCHER) || (tab[i + 1][j] == DIAMANT)))
				{

					if (tab[i][j] == ROCHER)
					{
						tab[i][j - 1] = ROCHERMVT;
					}
					else if (tab[i][j] == DIAMANT)
					{
						tab[i][j - 1] = DIAMANTMVT;
					}
					tab[i][j] = GALERIE;
				}
			}
			// Gestion des rochers (ou diamants) en mouvement
			if ((tab[i][j] == ROCHERMVT) || (tab[i][j] == DIAMANTMVT))
			{
				// Test si le rocher (ou diamant) reste en mouvement car toujours dans le vide
				if (tab[i + 1][j] == GALERIE)
				{

					if (tab[i][j] == ROCHERMVT)
					{
						tab[i + 1][j] = ROCHERMVT;
					}
					else if (tab[i][j] == DIAMANTMVT)
					{
						tab[i + 1][j] = DIAMANTMVT;
					}
					tab[i][j] = GALERIE;
				}
				// Test si le rocher (ou diamant) tombe sur un obsatacle, sa chute s'arrete
				if (tab[i + 1][j] != GALERIE)
				{
					if (tab[i + 1][j] == BONHOMME)
					{
						return mort = 1;
					}
					if ((tab[i + 1][j] == ENEMI_BAS) || (tab[i + 1][j] == ENEMI_DROITE) || (tab[i + 1][j] == ENEMI_GAUCHE) || (tab[i + 1][j] == ENEMI_HAUT))
					{

						mort = explosion_enemi(tab, i + 1, j, mort);

						return mort;
					}
					if (tab[i][j] == ROCHERMVT)
					{
						tab[i][j] = ROCHER;
					}
					else if (tab[i][j] == DIAMANTMVT)
					{
						tab[i][j] = DIAMANT;
					}
				}
			}
		}
	}
	return mort = 0;
}

int mouvement_joueur(char tab[NB_LIGNE][NB_COLONNE], int orientation, SDL_Rect *pos, int *diamant_obtenu, int mort)
{

	switch (orientation)
	{
	case GAUCHE: /** Y est l'abscisse **/
		// Vérification :
		// => dépassement de la zone de jeu
		// => présence d'un bloc incassable
		// => présence d'un rocher
		// => porte fermée
		if ((pos->y - 1 < 0) || (tab[pos->x][pos->y - 1] == INCASSABLE) || (tab[pos->x][pos->y - 1] == ROCHER) ||(tab[pos->x][pos->y - 1] == ROCHERMVT) || (tab[pos->x][pos->y - 1] == PORTE_FERME))
		{
			// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
			break;
		}
		
		/** Si le joueur récupère un diamant **/
		if (tab[pos->x][pos->y - 1] == DIAMANT)
		{
			*diamant_obtenu = *diamant_obtenu + 1;
		}
		if( (tab[pos->x][pos->y - 1] == ENEMI_BAS) || (tab[pos->x][pos->y - 1] == ENEMI_BASMVT)||(tab[pos->x][pos->y - 1] == ENEMI_HAUT) || (tab[pos->x][pos->y - 1] == ENEMI_HAUTMVT)||(tab[pos->x][pos->y - 1] == ENEMI_DROITE) || (tab[pos->x][pos->y - 1] == ENEMI_DROITEMVT)||(tab[pos->x][pos->y - 1] == ENEMI_GAUCHE) || (tab[pos->x][pos->y - 1] == ENEMI_GAUCHEMVT) )
		{
			mort =1;
			return mort;
		}
		// Si la case est accessible, le joueur va à gauche
		tab[pos->x][pos->y] = GALERIE;
		tab[pos->x][pos->y - 1] = BONHOMME;
		pos->y--;
		break;
	case DROITE:
		// Vérification :
		// => dépassement de la zone de jeu
		// => présence d'un bloc incassable
		// => présence d'un rocher
		// => porte fermée
		if ((pos->y + 2 > NB_COLONNE) || (tab[pos->x][pos->y + 1] == INCASSABLE) || (tab[pos->x][pos->y + 1] == ROCHER) || (tab[pos->x][pos->y + 1] == ROCHERMVT) || (tab[pos->x][pos->y + 1] == PORTE_FERME))
		{
			// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
			break;
		}
		
		/** Si le joueur récupère un diamant **/
		if (tab[pos->x][pos->y + 1] == DIAMANT)
		{
			*diamant_obtenu = *diamant_obtenu + 1;
		}
		if( (tab[pos->x][pos->y + 1] == ENEMI_BAS) || (tab[pos->x][pos->y + 1] == ENEMI_BASMVT)||(tab[pos->x][pos->y + 1] == ENEMI_HAUT) || (tab[pos->x][pos->y + 1] == ENEMI_HAUTMVT)||(tab[pos->x][pos->y + 1] == ENEMI_DROITE) || (tab[pos->x][pos->y + 1] == ENEMI_DROITEMVT)||(tab[pos->x][pos->y + 1] == ENEMI_GAUCHE) || (tab[pos->x][pos->y + 1] == ENEMI_GAUCHEMVT) )
		{
			mort =1;
			return mort;
		}
		// Si la case est accessible, le joueur va à droite
		tab[pos->x][pos->y] = GALERIE;
		tab[pos->x][pos->y + 1] = BONHOMME;
		pos->y++;
		break;
	case HAUT:
		// Vérification :
		// => dépassement de la zone de jeu
		// => présence d'un bloc incassable
		// => présence d'un rocher
		// => porte fermée
		if ((pos->x - 1 < 0) || (tab[pos->x - 1][pos->y] == INCASSABLE) || (tab[pos->x - 1][pos->y] == ROCHER) || (tab[pos->x - 1][pos->y] == ROCHERMVT)|| (tab[pos->x - 1][pos->y] == PORTE_FERME))
		{
			// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
			break;
		}
		
		/** Si le joueur récupère un diamant **/
		if (tab[pos->x - 1][pos->y] == DIAMANT)
		{
			*diamant_obtenu = *diamant_obtenu + 1;
		}
		if( (tab[pos->x - 1][pos->y] == ENEMI_BAS) || (tab[pos->x - 1][pos->y] == ENEMI_BASMVT)||(tab[pos->x - 1][pos->y]== ENEMI_HAUT) || (tab[pos->x - 1][pos->y] == ENEMI_HAUTMVT)||(tab[pos->x - 1][pos->y] == ENEMI_DROITE) || (tab[pos->x - 1][pos->y] == ENEMI_DROITEMVT)||(tab[pos->x - 1][pos->y] == ENEMI_GAUCHE) || (tab[pos->x - 1][pos->y] == ENEMI_GAUCHEMVT) )
		{
			mort =1;
			return mort;
		}
		// Si la case est accessible, le joueur monte
		tab[pos->x][pos->y] = GALERIE;
		tab[pos->x - 1][pos->y] = BONHOMME;
		pos->x--;
		break;
	case BAS:
		// Vérification :
		// => dépassement de la zone de jeu
		// => présence d'un bloc incassable
		// => présence d'un rocher
		// => porte fermée
		if ((pos->x + 2 > NB_LIGNE) || (tab[pos->x + 1][pos->y] == INCASSABLE) || (tab[pos->x + 1][pos->y] == ROCHER) || (tab[pos->x + 1][pos->y] == ROCHERMVT) || (tab[pos->x + 1][pos->y] == PORTE_FERME))
		{
			// Si la case où le joueur veut se rendre est interdite, on sort de la boucle
			break;
		}
		
		/** Si le joueur récupère un diamant **/
		if (tab[pos->x + 1][pos->y] == DIAMANT)
		{
			*diamant_obtenu = *diamant_obtenu + 1;
		}
		if( (tab[pos->x + 1][pos->y] == ENEMI_BAS) || (tab[pos->x + 1][pos->y] == ENEMI_BASMVT)||(tab[pos->x + 1][pos->y]== ENEMI_HAUT) || (tab[pos->x + 1][pos->y] == ENEMI_HAUTMVT)||(tab[pos->x + 1][pos->y] == ENEMI_DROITE) || (tab[pos->x + 1][pos->y] == ENEMI_DROITEMVT)||(tab[pos->x + 1][pos->y] == ENEMI_GAUCHE) || (tab[pos->x + 1][pos->y] == ENEMI_GAUCHEMVT) )
		{
			mort =1;
			return mort;
		}
		// Si la case est accessible, le joueur descend
		tab[pos->x][pos->y] = GALERIE;
		tab[pos->x + 1][pos->y] = BONHOMME;
		pos->x++;
		break;
	}
	return 0;
}

// fonction qui gere le deplacement des enemis
// EXPLIQUER L'ALGO PLUS TARD !!!
int gestion_enemi(char tab[NB_LIGNE][NB_COLONNE], int mort)
{
	int i, j;

	for (i = 0; i < NB_LIGNE; i++)
	{

		for (j = 0; j < NB_COLONNE; j++)
		{
			if (tab[i][j] == ENEMI_DROITE)
			{

				// test si il peut allez sur sa droite

				if (tab[i][j + 1] == GALERIE)
				{
					tab[i][j] = GALERIE;
					tab[i][j + 1] = ENEMI_DROITEMVT;
				}
				else if (tab[i][j + 1] == BONHOMME)
				{
					mort = 1;
				}
				else
				{
					tab[i][j] = ENEMI_HAUTMVT;
				}
			}
			if (tab[i][j] == ENEMI_HAUT)
			{
				// test si il peut allez en haut

				if (tab[i - 1][j] == GALERIE)
				{
					tab[i][j] = GALERIE;
					tab[i - 1][j] = ENEMI_HAUTMVT;
				}
				else if (tab[i - 1][j] == BONHOMME)
				{
					mort = 1;
				}
				else
				{
					tab[i][j] = ENEMI_GAUCHEMVT;
				}
			}

			if (tab[i][j] == ENEMI_GAUCHE)
			{
				// test si il peut allez sur sa gauche

				if (tab[i][j - 1] == GALERIE)
				{
					tab[i][j] = GALERIE;
					tab[i][j - 1] = ENEMI_GAUCHEMVT;
				}
				else if (tab[i][j - 1] == BONHOMME)
				{
					mort = 1;
				}
				else
				{
					tab[i][j] = ENEMI_BASMVT;
				}
			}
			if (tab[i][j] == ENEMI_BAS)
			{
				// test si il peut allez en bas

				if (tab[i + 1][j] == GALERIE)
				{
					tab[i][j] = GALERIE;
					tab[i + 1][j] = ENEMI_BASMVT;
				}
				else if (tab[i + 1][j] == BONHOMME)
				{
					mort = 1;
				}
				else
				{
					tab[i][j] = ENEMI_DROITEMVT;
				}
			}
		}
	}

	// enemi en mouvement redevienne des enemi
	for (i = 0; i < NB_LIGNE; i++)
	{

		for (j = 0; j < NB_COLONNE; j++)
		{
			if (tab[i][j] == ENEMI_BASMVT)
			{
				tab[i][j] = ENEMI_BAS;
			}
			if (tab[i][j] == ENEMI_HAUTMVT)
			{
				tab[i][j] = ENEMI_HAUT;
			}
			if (tab[i][j] == ENEMI_DROITEMVT)
			{
				tab[i][j] = ENEMI_DROITE;
			}
			if (tab[i][j] == ENEMI_GAUCHEMVT)
			{
				tab[i][j] = ENEMI_GAUCHE;
			}
		}
	}
	return mort;
}

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;
	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return (interval);
}

void affichage_aide(int niveau, SDL_Surface *ecran, Ressource *sprite)
{
	int i;
	void SDL_Delay(Uint32 ms);
	SDL_Rect position;
	position.x = 300;
	position.y = 150;
	if (niveau == 1)
	{
		for (i = 0; i < 3; i++)
		{
			SDL_BlitSurface(sprite->anime1_1, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(300);
			SDL_BlitSurface(sprite->anime1_2, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(300);
			SDL_BlitSurface(sprite->anime1_3, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(300);
		}
	}
	if (niveau == 2)
	{
		for (i = 0; i < 3; i++)
		{
			SDL_BlitSurface(sprite->anime2_1, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime2_2, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime2_3, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime2_4, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime2_5, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime2_6, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
		}
	}
	if (niveau == 3)
	{
		for (i = 0; i < 3; i++)
		{
			SDL_BlitSurface(sprite->anime3_1, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime3_2, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime3_3, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			SDL_BlitSurface(sprite->anime3_4, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(100);
			SDL_BlitSurface(sprite->anime3_5, NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(200);
			
		}
	}
}

void jouer(SDL_Surface *ecran, Ressource *sprite,Liste *liste_score)
{
	void SDL_Delay(Uint32 ms);
	//initialisation suface
	//SDL_Surface *gameover = NULL, *win =NULL;

	SDL_Rect positiongameover, positionwin, positiondiamantscore;
	positionwin.x = 150;
	positionwin.y = 0;
	positiongameover.x = 350;
	positiongameover.y = 0;
	positiondiamantscore.x= 700;
	positiondiamantscore.y= 500;
	// initialisatio variable diverse
	int i, j, x = -1, y = -1, diamant, continuer = 0, mort = 0, niveau = 1,diamant_obtenu=0;
	int centaine=0, dizaine=0, unite=0;
	// Initialisation pour timer

	int delay;
	SDL_TimerID my_timer_id;
	delay = 200; /* To round it down to the nearest 10 ms */
	my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL);

	// Initialisation de la map
	char tab[NB_LIGNE][NB_COLONNE];

	load_map(tab, niveau);
	
	SDL_Rect position_joueur;
	SDL_Event event;

	diamant = affichage(tab, ecran, sprite);
	affichage_aide(niveau, ecran, sprite);
	diamant = affichage(tab, ecran, sprite);
	//affichage_aide(niveau, ecran, sprite);
	// Recherche de la position de départ du bonhomme
	for (i = 0; i < NB_COLONNE; i++)
	{
		for (j = 0; j < NB_LIGNE; j++)
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

	while (continuer == 0)
	{

		SDL_WaitEvent(&event);

		switch (event.type)
		{
		// cas de la croix rouge de la fenetre
		case SDL_QUIT:
			continuer = 1;
			break;

		// cas du timer
		case SDL_USEREVENT:
			mort = gravitedirect(tab, mort);
			mort = gestion_enemi(tab, mort);
			break;

		//cas touche de clavier appuyer
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				// Quitter la fenêtre de jeu et retourner au menu principal
				continuer = 1;
				break;
			case SDLK_UP:
				mort = mouvement_joueur(tab, HAUT, &position_joueur,&diamant_obtenu,mort);
				break;
			case SDLK_DOWN:
				mort = mouvement_joueur(tab, BAS, &position_joueur,&diamant_obtenu,mort);
				break;
			case SDLK_RIGHT:
				mort = mouvement_joueur(tab, DROITE, &position_joueur,&diamant_obtenu,mort);
				break;
			case SDLK_LEFT:
				mort = mouvement_joueur(tab, GAUCHE, &position_joueur,&diamant_obtenu,mort);
				break;
			default:
				break;
			}
			break;
		}

		// Effacement de l'écran
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

		// Affichage de l'écran de jeu
		diamant = affichage(tab, ecran, sprite);
		// Actualisation de l'ecran
		SDL_Flip(ecran);

		if (mort == 1)
		{
			// Quitter la fenêtre de jeu et retourner au menu principal
			continuer = 1;
			
			/** calculer le nombre de diamants obtenus **/
			calcul_score(&diamant_obtenu,&centaine,&dizaine,&unite);
			
			/** Affichage du game over et du resultat **/
			SDL_BlitSurface(sprite->gameover, NULL, ecran, &positiongameover);
			SDL_BlitSurface(sprite->diamantscore, NULL, ecran, &positiondiamantscore);
			affiche_score(ecran,sprite,&diamant_obtenu,&centaine,&dizaine,&unite);
			
			SDL_Flip(ecran);
			/** Ajout du nouveau score **/
			
			
			Element *nouveau_score =malloc(sizeof(*nouveau_score));
			nouveau_score->nombre=diamant_obtenu;
			ajoute_score(liste_score,nouveau_score);
			ecrire_score(liste_score);
			
			// Affichage de l'image "gameover" pendant 2,5 secondes
			SDL_Delay(2500);
		}
		
		// Si on n'a trouvé aucun diamant sur la carte, c'est que la porte s'ouvre
		if (diamant == 0)
		{

			// Recherche de la position de de la porte fermée pour la rendre ouverte
			for (i = 0; i < NB_COLONNE; i++)
			{
				for (j = 0; j < NB_LIGNE; j++)
				{
					if (tab[j][i] == PORTE_FERME)
					{
						// La porte fermeée est remplacée par la porte ouverte
						tab[j][i] = PORTE_OUVERTE;
						y = i;
						x = j;
					}
				}
			}
		}

		if ((position_joueur.x == x) && (position_joueur.y == y))
		{
			niveau++;
			
			if (niveau > NIVEAU_MAX)
			{
				/** Ajout du score lors d'une victoire **/
				
				/** calculer le nombre de diamants obtenus **/
				calcul_score(&diamant_obtenu,&centaine,&dizaine,&unite);
				
				/** Affichage du win et du resultat **/
				SDL_BlitSurface(sprite->win, NULL, ecran, &positionwin);
				SDL_BlitSurface(sprite->diamantscore, NULL, ecran, &positiondiamantscore);
				affiche_score(ecran,sprite,&diamant_obtenu,&centaine,&dizaine,&unite);
				
				SDL_Flip(ecran);
				/** Ajout du nouveau score **/
				
				
				Element *nouveau_score =malloc(sizeof(*nouveau_score));
				nouveau_score->nombre=diamant_obtenu;
				ajoute_score(liste_score,nouveau_score);
				ecrire_score(liste_score);
				// Quitte la fenêtre de jeu car le joueur a gagné et retourne au menu principal
				
				
				
				SDL_Flip(ecran);
				// Affichage de l'image "WIN" pendant 2,5 secondes
				SDL_Delay(2500);
				continuer = 1;
			}
			else
			{
				
				load_map(tab, niveau);
				affichage_aide(niveau, ecran, sprite);
				for (i = 0; i < NB_COLONNE; i++)
				{
					for (j = 0; j < NB_LIGNE; j++)
					{ //printf("COINCER \n");

						if (tab[i][j] == BONHOMME)
						{
						position_joueur.x = i;
						position_joueur.y = j;
						}
					}
				}
			}
			x = -1;
			y = -1;
		}
	}

	SDL_RemoveTimer(my_timer_id);
	//SDL_FreeSurface(gameover);
	//SDL_FreeSurface(win);
}

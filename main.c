
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "constante.h"
#include "affichage.h"
#include "jouer.h"
#include "menu.h"
#include "structure.h"
#include "affiche_score.h"

void chargement (Ressource *sprite)
{
	sprite->terre = IMG_Load("Terre_1.bmp");
    sprite->incassable = IMG_Load("Terre_3.bmp");
    sprite->diamant= IMG_Load("diamant_2.bmp");
    sprite->porte_ouverte = IMG_Load("porte_ouverte.bmp");
    sprite->porte_ferme= IMG_Load("porte_ferme.bmp");
    sprite->bonhomme= IMG_Load("totoro.bmp");
    sprite->rocher = IMG_Load("rocher_1.bmp");
    sprite->rocher_mvt = IMG_Load("rocher_mvt.bmp");
    sprite->diamant_mvt = IMG_Load("diamant_mvt.bmp");
	sprite->enemi = IMG_Load("enemi.bmp");
	sprite->explosion = IMG_Load("explosion.bmp");
	sprite->gameover = IMG_Load("game_over.bmp");
	sprite->win = IMG_Load("win.bmp");
	sprite->anime1_1=IMG_Load("annim_rocher1.bmp");
	sprite->anime1_2=IMG_Load("annim_rocher2.bmp");
	sprite->anime1_3=IMG_Load("annim_rocher3.bmp");
	sprite->anime2_1=IMG_Load("annim_enemi6.bmp");
	sprite->anime2_2=IMG_Load("annim_enemi5.bmp");
	sprite->anime2_3=IMG_Load("annim_enemi1.bmp");
	sprite->anime2_4=IMG_Load("annim_enemi2.bmp");
	sprite->anime2_5=IMG_Load("annim_enemi3.bmp");
	sprite->anime2_6=IMG_Load("annim_enemi4.bmp");
	sprite->anime3_1=IMG_Load("annim_explosion1.bmp");
	sprite->anime3_2=IMG_Load("annim_explosion2.bmp");
	sprite->anime3_3=IMG_Load("annim_explosion3.bmp");
	sprite->anime3_4=IMG_Load("annim_explosion4.bmp");
	sprite->anime3_5=IMG_Load("annim_explosion5.bmp");
	
	sprite->diamantscore=IMG_Load("diamantscore.bmp");
	sprite->chiffre0=IMG_Load("chiffre0.bmp");
	sprite->chiffre1=IMG_Load("chiffre1.bmp");
	sprite->chiffre2=IMG_Load("chiffre2.bmp");
	sprite->chiffre3=IMG_Load("chiffre3.bmp");
	sprite->chiffre4=IMG_Load("chiffre4.bmp");
	sprite->chiffre5=IMG_Load("chiffre5.bmp");
	sprite->chiffre6=IMG_Load("chiffre6.bmp");
	sprite->chiffre7=IMG_Load("chiffre7.bmp");
	sprite->chiffre8=IMG_Load("chiffre8.bmp");
	sprite->chiffre9=IMG_Load("chiffre9.bmp");

	
	return;
}

int main(void)
{
	int choix=0,x,y;
	SDL_Event event;
    SDL_Surface *ecran = NULL, *regle = NULL, *boutonfin = NULL, *menuscore = NULL, *boutonfin2=NULL;
	SDL_Rect positionRegle, positionBoutonFin, positionMenuScore, positionBoutonFin2;
	SDL_WaitEvent(&event);
	// chargement des sous systeme video et timer
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    // Chargement de l'icône
	SDL_WM_SetIcon(IMG_Load("icone.ico"), NULL); 
    // chargement des sprites de jeu
	Ressource sprite;
	chargement (&sprite);
    // Chargement de la fenêtre
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Boulder Dash", NULL);
    
    Liste *liste_score = initialisation();
    lire_score(liste_score);
	
		do
		{
			choix=0;
			menu(&choix, ecran);
			if(choix==3) 	
			{
				/** Affichage du score **/
				
				SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
				menuscore = IMG_Load("menuscore.bmp");
				boutonfin2 = IMG_Load("boutonfin.bmp");
				positionMenuScore.x = 0;
				positionMenuScore.y = 0;
				positionBoutonFin2.x=100;
				positionBoutonFin2.y=515;
				
				SDL_BlitSurface(menuscore, NULL, ecran, &positionMenuScore);
				SDL_BlitSurface(boutonfin2, NULL, ecran, &positionBoutonFin2);
				
				
				/** MENU SCORE **/
				
				
				aff_liste(liste_score);
				
				SDL_Flip(ecran);
				
				while (choix==3)
				{	
					
					SDL_WaitEvent(&event);
					switch(event.type)
					{	
						case SDL_QUIT:
						choix=5;
						break;
						case SDL_MOUSEBUTTONUP:
							if (event.button.button == SDL_BUTTON_LEFT)
							{
								x=event.button.x;
								y=event.button.y;
								
								if(((100 < x)&&(x < 320))&&((515 < y)&&(y < 590)))
								{
							
								choix=10;
								break;								
								}
							}
							break;
						default:;
					}
				}
				
				
			}else if(choix==4)
			{
				// Affichage de l'aide
			
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
			// Effacement de l'écran
			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
			SDL_Flip(ecran);
			jouer(ecran, &sprite,liste_score);
		}
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		
		
	}while((choix!=1)&&(choix!=5));	
		/** Liberer la liste **/
		libere_liste(liste_score);
	SDL_Quit();
	return EXIT_SUCCESS;
	
}

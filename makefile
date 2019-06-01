all: jouer.c affichage.c main.c menu.c affiche_score.c menu.h jouer.h affichage.h constante.h structure.h loadmap.c loadmap.h affiche_score.h
	gcc -Wall  main.c  affichage.c jouer.c menu.c loadmap.c affiche_score.c -o boulder -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image






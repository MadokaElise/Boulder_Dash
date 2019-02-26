all: jouer.c affichage.c main.c menu.c menu.h jouer.h affichage.h constante.h structure.h loadmap.c loadmap.h
	gcc -Wall  main.c  affichage.c jouer.c menu.c loadmap.c -o boulder -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image






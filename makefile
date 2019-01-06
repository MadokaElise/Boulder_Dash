all: jouer.c affichage.c main.c jouer.h affichage.h constante.h
	gcc -Wall  main.c  affichage.c jouer.c -o boulder -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image


#ifndef CONSTANTES
#define CONSTANTES
	
	// Constante des dimension
    #define TAILLE_BLOC   32 // Taille d'un bloc (carré) en pixels
    #define NB_COLONNE    10 // nombre de colonne du palateau
    #define NB_LIGNE      10 // nombre de ligne du plateau
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_COLONNE
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_LIGNE
	
	// Constante des different bloc
	#define INCASSABLE      'i'
	#define ROCHER          'r'
	#define DIAMANT         'd'
	#define TERRE           't'
	#define BONHOMME        'b'
	#define PORTE_FERME     'f'
	#define PORTE_OUVERTE   'o'
	
	// Constante Orientation
	
	#define HAUT     1
	#define BAS      2
	#define DROITE   3
	#define GAUCHE   4
	
#endif

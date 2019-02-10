#ifndef CONSTANTES
#define CONSTANTES
	
	// Constante des dimension
    #define TAILLE_BLOC   32 // Taille d'un bloc (carré) en pixels
    #define NB_COLONNE    38 // Nombre de colonne du palateau
    #define NB_LIGNE      20 // Nombre de ligne du plateau
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_COLONNE
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_LIGNE
	
	// Constante des differents blocs
	#define INCASSABLE      'i'
	#define ROCHER          'r'
	#define DIAMANT         'd'
	#define TERRE           't'
	#define BONHOMME        'b'
	#define PORTE_FERME     'f'
	#define PORTE_OUVERTE   'o'
	#define GALERIE         ' '
	#define ROCHERMVT       'm'
	#define DIAMANTMVT      'v'
	#define ENEMI_DROITE    'e'
	#define ENEMI_GAUCHE    'g'       
	#define ENEMI_BAS       'a'
	#define ENEMI_HAUT      'u'
	
	
	// Constante d'orientation
	
	#define HAUT     1
	#define BAS      2
	#define DROITE   3
	#define GAUCHE   4
	
#endif

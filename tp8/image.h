#ifndef __IMAGE_H__
#define __IMAGE_H__ 1

#include "matrice.h"

typedef struct sImage * tImage;

extern tImage ImAllouer(int, int);
extern void ImLiberer(tImage *);
extern int ImNbLig(tImage);
extern int ImNbCol(tImage);
extern tMatrice ImNivGris(tImage);

extern tImage ImLire(char []);
extern void ImEcrire(tImage, char []);
extern void afficherImage(tImage);
#endif

#ifndef __MATRICE_H__
#define __MATRICE_H__ 1

typedef int ** tMatrice;

extern tMatrice matAllouer(int, int);
extern void afficherMat(tMatrice, int, int);
extern tMatrice lireMat(int *, int *);
extern tMatrice matCopier(tMatrice, int, int);
extern void libererMatrice(tMatrice *);

#endif

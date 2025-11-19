#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	int l, c;
	tMatrice mat = lireMat(&l, &c);

	afficherMat(mat, l, c);	

	tMatrice copie = matCopier(mat, l, c);

	afficherMat(copie, l, c);

	libererMatrice(&copie);
	libererMatrice(&mat);
	return 0;
}

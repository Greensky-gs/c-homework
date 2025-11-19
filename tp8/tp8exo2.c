#include <stdlib.h>
#include <stdio.h>
#include "matrice.h"
#include "image.h"

int main() {
	tImage image = ImLire("feep.pgm");

	afficherImage(image);

	tImage rotation = ImAllouer(ImNbCol(image), ImNbLig(image));
	
    tMatrice nivGris = ImNivGris(image);
	tMatrice nivRotation = ImNivGris(rotation);

	for (int i = 0; i < ImNbLig(image); i++) {
		for (int j = 0; j < ImNbCol(image); j++) {
			nivRotation[ImNbCol(image) - j - 1][i] = nivGris[i][j];
		}
	}
	
    afficherImage(rotation);

	ImLiberer(&image);
    ImLiberer(&rotation);

	return 0;
}

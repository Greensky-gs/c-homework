#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "matrice.h"

struct sImage {
	int NbLig;
	int NbCol;
	tMatrice NivGris;
};

tImage ImAllouer(int NbLignes, int NbColonnes) {
	struct sImage * ptr = malloc(sizeof(struct sImage));
	if (ptr == NULL) {
		perror("ImAllouer : Erreur allocation sImage");
		return NULL;
	}
	
	tMatrice matriceGris = matAllouer(NbLignes, NbColonnes);
       	if (matriceGris == NULL) {
		perror("ImAllouer : Erreur allocation matriceGris");
		libererMatrice(&matriceGris);
		return NULL;	
	}
	
	ptr->NbLig = NbLignes;
	ptr->NbCol = NbColonnes;
	ptr->NivGris = matriceGris;

	return ptr;
}
void ImLiberer(tImage * ptr) {
	libererMatrice(&(*ptr)->NivGris);
	free(*ptr);
	*ptr = NULL;
}

int ImNbLig(tImage img) {
	return img->NbLig;
}
int ImNbCol(tImage img) {
	return img->NbCol;
}
tMatrice ImNivGris(tImage img) {
	return img->NivGris;
}

tImage ImLire(char nomFichier[]) {
	FILE * stream = fopen(nomFichier, "rb");
	if (stream == NULL) {
		perror("ImLire : Erreur lecture fichier");
		return NULL;
	}

	int l, c, maximal;
	int res = fscanf(stream, "P2\n%d %d\n%d", &c, &l, &maximal);
	if (res < 3) {
		perror("ImLire : erreur lecture");
		fclose(stream);
		return NULL;
	}

	tImage image = ImAllouer(l, c);
	if (image == NULL) {
		perror("ImLire : Erreur allocation image");
		fclose(stream);
		return NULL;
	}

	int i = 0;
	int j = 0;
	int total = image->NbCol * image->NbLig;

	while (i * image->NbCol + j < total) {
		fscanf(stream, "%d", &image->NivGris[i][j]);

		image->NivGris[i][j] = round(255.0 * image->NivGris[i][j] / maximal);
		j++;
		if (j == image->NbCol) {
			j = 0;
			i++;

		}
	}

	fclose(stream);

	return image;

}
void ImEcrire(tImage im, char nomFichier[]) {
	FILE * stream = fopen(nomFichier, "wt");
	if (stream == NULL) {
		perror("ImEcrire : Erreur ouverture fichier");
		return;
	}

	char contenu[250] = {0};
	sprintf(contenu, "P2\n%d %d\n255\n", ImNbCol(im), ImNbLig(im));
	fputs(contenu, stream);

	contenu[4] = '\0'; // Buffer d'écriture des nombres (max 255, donc 3 caractères + espace + \0 = on coupe au 5e caractère (on réutilise le buffer, on est pas des animaux))

	for (int i = 0; i < ImNbLig(im); i++) {
		for (int j = 0; j < ImNbCol(im); j++) {
			sprintf(contenu, "%d ", im->NivGris[i][j]);
			int res = fputs(contenu, stream);
			if (res == EOF) {
				perror("ImEcrire : erreur ecriture");
				fclose(stream);
				return;
			}
		}
		fputs("\n", stream);
	}

	fclose(stream);
}
void afficherImage(tImage image) {
	afficherMat(image->NivGris, image->NbLig, image->NbCol);
}

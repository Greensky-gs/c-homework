#include <stdio.h>

void Trier(int tab[], int elts) {
	for (int i = elts - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (tab[j + 1] < tab[j]) {
				int temp   = tab[j];
				tab[j]     = tab[j + 1];
				tab[j + 1] = temp;
			}
		}
	}
}
void afficher(int tab[], int elts) {
	printf("\x1b[35m[\x1b[0m");
	for (int i = 0; i < elts; i++) {
		printf("\x1b[32m%4d\x1b[0m, ", tab[i]);
	}
	printf("\x1b[35m]\x1b[0m\n");
}

void triPtr(int tab[], int elts, int * ptr[]) {
	for (int i = 0; i < elts; i++) {
		ptr[i] = &tab[i];
	}
	for (int i = elts - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (*ptr[j + 1] < *ptr[j]) {
				int * temp = ptr[j];
				ptr[j]     = ptr[j + 1];
				ptr[j + 1] = temp;
			}
		}
	}
}
void afficherPtr(int * ptr[], int elts) {
	printf("\x1b[35m[\x1b[0m");
	for (int i = 0; i < elts; i++) {
		printf("\x1b[32m%4d\x1b[0m, ",*( ptr[i]));
	}
	printf("\x1b[35m]\x1b[0m\n");
}

int main() {
	int tab[] = { 1, 2, -5, 3, 0 };
	afficher(tab, 5);

	int * ptr[5];
	triPtr(tab, 5, ptr);

	afficher(tab, 5);
	afficherPtr(ptr, 5);
}

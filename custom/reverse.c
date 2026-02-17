#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(void * tab, int n, size_t t) {
	void * temp = malloc(t);
	int i = 0;
	while (i < n / 2) {
		memcpy(temp, tab + i * t, t);
		memcpy(tab + i * t, tab + t * (n - i - 1), t);
		memcpy(tab + t * (n - i - 1), temp, t);

		i++;
	}

	free(temp);
}

void print_int_tab(int * tab, int size) {
	int i = 0;
	while (i++ < size) {
		printf("%d ", tab[i - 1]);
	}
	printf("\n");
}

int main() {
	int tab[5] = { 1, 2, 3, 4, 5 };

	print_int_tab(tab, 5);

	reverse(tab, 5, sizeof(int));

	print_int_tab(tab, 5);
}

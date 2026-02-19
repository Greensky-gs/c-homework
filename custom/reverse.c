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

void print_tab(void * tab, int size, size_t t, void callback(void *)) {
	int i = 0;
	while (i < size) {
		callback(tab + i * t);
		i++;
	}
	printf("\n");
}

void print_int(void * p) {
	printf("%d ", *(int *)p);
}

int main() {
	int tab[5] = { 1, 2, 3, 4, 5 };

	print_tab(tab, 5, sizeof(int), &print_int);

	reverse(tab, 5, sizeof(int));

	print_tab(tab, 5, sizeof(int), &print_int);
}

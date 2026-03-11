#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void ecrire_dans_stdout(char nom_fichier[]) {
	int source = open(nom_fichier, O_RDONLY, 0);
	if (source == -1) {
		perror("open source");
		return;
	}

	char buffer[100];
	int s;
	while ((s = read(source, buffer, 100)) > 0) {
		write(STDOUT_FILENO, buffer, s);
	}

	fflush(stdout);

	close(source);
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Pas d'entrée\n");
		return 1;
	}
	ecrire_dans_stdout(argv[1]);

	return 0;
}

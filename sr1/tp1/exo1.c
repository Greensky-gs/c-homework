#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int quest1() {
	printf("pid = \x1b[33m%d\x1b[0m\n", getpid());
	printf("Parent id = \x1b[33m%d\x1b[0m\n", getppid());
	printf("Group id = \x1b[33m%d\x1b[0m\n", getpgrp());
	
	char * c;
	if ((c = getlogin()) == NULL) printf("Utilisateur : info indisponible\n");
	else printf("Login utilisateur : \x1b[91m%s\x1b[0m\n", c);

	printf("ID propriétaire proc. = \x1b[33m%d\x1b[0m\n", getuid());
	printf("ID groupe proprio. proc. = \x1b[33m%d\x1b[0m\n", getgid());

	return 0;
}
int quest2() {
	// Programme qui appelle celui de la question 1
	quest1();
}

int main() {
	switch (fork()) {
		case -1:
			perror("Fork error");
			exit(1);
		break;
		case 0:
			quest2();
			printf("Je suis le fils, je m'arrete avec le code 0\n");
			exit(0);
		break;
		default:
			wait(NULL); // Ne pas mettre le wait va faire que peut-être le père s'arrête avant le fils
			printf("Je suis le père, j'ai attendu mon fils et je m'arrete avec le code 0\n");
			exit(0);
		break;
	}
}

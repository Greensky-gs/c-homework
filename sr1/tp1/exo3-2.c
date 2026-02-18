#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NB_MOT_MAX 20

int decoupe(char chaine[], char * pMots[]) {
	char *p = chaine;
	int nb = 0;

	while ((*p) != 0 && nb < NB_MOT_MAX) {
		while ((*p) == ' ' && (*p) != 0) p++;
		if ((*p) == 0) break;

		pMots[nb++] = p;
		while ((*p) != ' ' && (*p) != 0) p++;
		if ((*p) == 0) break;
		*p = 0;
		p++;
	}

	pMots[nb] = NULL;
	return nb;
}


void print_header() {
	printf("\x1b[35m[%d]\x1b[0m ", getpid());
}

void print_command(char * ptrs[], int size) {
	int i = 0;
	while (i < size) {
		printf("%s ", ptrs[i]);
		i++;
	}

}

int exec_command(char * ptrs[], int size) {
	pid_t pid = fork();
	switch (pid) {
		case -1:
			perror("fork");
			return 1;
		case 0:
			print_header();
			printf("J'exécute \x1b[91m"); 
			print_command(ptrs, size);
			printf("\x1b[0m\n");
			fflush(stdout);

			execvp(ptrs[0], ptrs);
			exit(1);
		break;
		default:
			print_header();
			printf("J'ai délégué \x1b[91m");
			print_command(ptrs, size);
			printf("\x1b[0m à \x1b[33m%d\x1b[0m\n", pid);
			fflush(stdout);

			return 0;

		break;
	}
}

int main(int argc, char * argv[]) {
	int i = 1;
	while (i < argc) {
		char * mots[NB_MOT_MAX + 1];
		
		int res = decoupe(argv[i], mots);
		
		exec_command(mots, res);

		i++;
	}

	pid_t wpid;
	int status = 0;
	while ((wpid = wait(&status)) > 0) {};

	print_header();
	printf("Appels terminés\n");
}

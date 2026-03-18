#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 4

int create_child(int epsilon[2]) {
	pid_t pid;
	switch (pid = fork()) {
		case -1:
			perror("fork");
			return 0;
		
	}
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Au moins 2 arguments");
		return 1;
	}

	int epsilon[2];
	if (pipe(epsilon) == -1) {
		perror("pipe");
		return 1;
	}

	int i = 1;
	int childs = 0;

	int n = 0;
	while (n < N) {
		
	}

	while (i < argc) {
		char * str, * end;
		str = argv[i];
		errno = 0;
		long long int x = strtoull(str, &end, 10);

		if (str == end) {
			printf("[PERE] Argument \x1b[33m%d\x1b[0m non valide\n", i);
			i++;
			continue;
		}

		chillds++;
		handle_number(x);
	}
}

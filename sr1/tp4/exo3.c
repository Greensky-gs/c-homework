#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 4

int est_premier(long long int);

static void child_callback(int n, int epsilon[2], int count[2]) {
	int count_v = 0;

	long long int buf;
	close(epsilon[1]);
	close(count[0]);

	while (read(epsilon[0], &buf, sizeof(long long int)) > 0) {
		printf("[FILS %d] %20llu ", n, buf);
		
		int res;
		if ((res = est_premier(buf))) printf("est premier\n");
		else printf("n'est pas premier\n");

		count_v += res;
	}
	close(epsilon[0]);

	write(count[1], &count_v, sizeof(int));
	close(count[1]);

	_exit(0);
};

static int create_child(int n, int epsilon[2], int count[2]) {
	switch (fork()) {
		case -1:
			perror("fork");
			return 0;
		case 0:
			child_callback(n, epsilon, count);
			break;
		default:
			return 1;
	}
	return 0;
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Au moins 2 arguments\n");
		return 1;
	}

	int epsilon[2]; // Alors c'est comme un tube
	if (pipe(epsilon) == -1) {
		perror("pipe");
		return 1;
	}
	int count_pipe[2];
	if (pipe(count_pipe) == -1) {
		perror("pipe");
		close(epsilon[0]);
		close(epsilon[1]);
		return 1;
	}

	int i = 1;
	int childs = 0;

	int n = 0;
	while (n < N) {
		childs += create_child(n, epsilon, count_pipe);
		n++;
	}

	if (n == 0) {
		printf("Aucun processus enfant crée\n");
		close(epsilon[0]);
		close(epsilon[1]);
		return 1;
	}

	close(count_pipe[1]);

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
		if (errno != 0) {
			perror("strtoull");
			continue;
		}

		write(epsilon[1], &x, sizeof(long long int));
		i++;
	}
	close(epsilon[1]);

	int finished = 0;
	while (finished < childs) {
		wait(NULL);
		finished++;
	}

	int total = 0;
	int buf;
	while (read(count_pipe[0], &buf, sizeof(int)) > 0) {
		total += buf;
	}

	printf("[ PERE ] %20d nombres premiers\n", total);
}

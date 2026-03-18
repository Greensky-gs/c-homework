#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Il faut N\n");
		return 1;
	}
	int N;

	if (sscanf(argv[1], "%d", &N) != 1) {
		printf("N illisible\n");
		return 1;
	}

	int epsilon[2];
	if (pipe(epsilon) == -1) {
		perror("pipe");
		return 1;	
	}

	pid_t pid;
	switch (pid = fork()) {
		case -1:
			perror("fork");
			close(epsilon[0]);
			close(epsilon[1]);
			return 1;
		case 0:
			close(epsilon[1]);

			int buf;
			while (read(epsilon[0], &buf, sizeof(int)) > 0) {
				printf("[FILS] %d\n", buf);
			}
			close(epsilon[0]);

			_exit(1);
			break;
		default:
			close(epsilon[0]);

			int i = 1;
			while (i < N + 1) {
				write(epsilon[1], &i, sizeof(int));
				i++;
				sleep(1);
			}


			close(epsilon[1]);
			int status;
			waitpid(pid, &status, 0);

			if (WIFEXITED(status)) {
				printf("Mon fils %d s'est terminé avec le code %d\n", pid, WEXITSTATUS(status));
			} else {
				printf("Mon fils %d ne s'est pas terminé\n", pid);
			}
			break;

	}

	return 0;
}

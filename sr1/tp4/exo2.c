#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_BASSIN 5

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Il faut N\n");
		return 1;
	}
	int N;
	if (sscanf(argv[1], "%d", &N) != 1) {
		printf("N invalide\n");
		return 1;
	}

	int remplir[2];
	int etat[2];

	if (pipe(remplir) == -1) {
		perror("pipe");
		return 1;
	}
	if (pipe(etat) == -1) {
		perror("pipe (etat)");
		close(remplir[0]);
		close(remplir[1]);
		return 1;
	}

	int bassin = 0;
	pid_t pid;
	switch (pid = fork()) {
		case -1:
			close(remplir[0]);
			close(remplir[1]);
			close(etat[0]);
			close(etat[1]);

			perror("fork");
			return 1;
			break;
		case 0:
			close(remplir[1]);
			close(etat[0]);

			int buffer;
			while (read(remplir[0], &buffer, sizeof(int)) > 0) {
				if (buffer > 0) {
					bassin++;
					printf("*");
					fflush(stdout);

					if (bassin >= MAX_BASSIN) {
						write(etat[1], &bassin, sizeof(int));
					} 
				} else {
					bassin = 0;
					printf("\n");	
				}
			}
			printf("\n");

			close(etat[1]);
			close(remplir[0]);
			_exit(1);
			break;
		default:
			int flags = fcntl(etat[0], F_GETFL);
			flags |= O_NONBLOCK;
			fcntl(etat[0], F_SETFL, flags);

			int buf;
			int i = 1;
			while (i < N + 1) {
				int mo = -1;
				if (read(etat[0], &buf, sizeof(int)) > 0) write(remplir[1], &mo, sizeof(int));

				write(remplir[1], &i, sizeof(int));
				sleep(1);
				
				i++;
			}

			close(remplir[1]);
			close(remplir[0]);
			close(etat[0]);
			close(etat[1]);

			int status;
			waitpid(pid, &status, 0);

			if (WIFEXITED(status)) {
				printf("Mon fils %d s'est terminé avec le code %d\n", pid, WEXITSTATUS(status));
			} else {
				printf("Mon fils %d ne s'est pas terminé\n", pid);
			}
			break;
	}
}

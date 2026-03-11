#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int execute_command(int fd_source, int fd_dest) {
	switch (fork()) {
		case -1:
			perror("fork");
			return -1;
		case 0:
			char * buffer = calloc(BUFFER_SIZE, sizeof(char));
			int size;

			while ((size = read(fd_source, buffer, BUFFER_SIZE)) > 0) {
				write(fd_dest, buffer, size);
			}

			free(buffer);
			exit(0);
			break;
		default:
			wait(NULL);
			return 0;
			break;
	}
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Not enough args\n");
		return 1;
	}
	int dest = STDOUT_FILENO;
	if (argc > 3) {
		if (argv[argc - 2][0] == '>' && argv[argc - 2][1] == 0) {
			dest = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR);
			if (dest < 0) {
				printf("Echec ouverture fichier dest\n");
				return 1;
			}	
		}
	}

	int i = 1;
	while (i < argc) {
		if (argv[argc - 2][0] == '>' && argv[argc - 2][1] == 0) break;

		int source = open(argv[i], O_RDONLY, 0);
		if (source < 0) {
			printf("\x1b[33m%d\x1b[0m skipped because exists not\n", i);
			i++;
			continue;
		}

		execute_command(source, dest);	
		i++;

		close(source);
	}
}

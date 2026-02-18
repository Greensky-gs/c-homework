#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void ls() {
	execlp("ls", "ls", "-la", NULL);
}
void date() {
	execlp("date", "date", NULL);
}

int exec_command(void cmd(void), int waitchild) {
	pid_t pid;
	switch (pid = fork()) {
		case -1:
			perror("fork");
			return 1;
		case 0:
			cmd();
		break;
		default:
			if (waitchild) waitpid(pid, NULL, 0);
			return 0;
		break;
	}

	return 0;
}

int main_propre() {
	exec_command(&ls, 1);
	exec_command(&date, 1);
}

int main() {
	switch (fork()) {
		case -1:
			perror("fork");
			return 1;
		break;
		case 0:
			execlp("ls", "ls", "-la", NULL);
			exit(0);
		break;
		default:
			wait(NULL); // Un seul fils, donc possible
			execlp("date", "date", NULL);
			exit(0);
		break;
	}
}

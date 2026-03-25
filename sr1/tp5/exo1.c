#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define N 1

static int streq(char * a, char * b) {
	int i = 0;
	while (a[i] != 0 && b[i] != 0) {
		if (a[i] != b[i]) return 0;
		i++;
	}

	return b[i] == 0;
}

static int create_child(int fichiers[2], int resultat[2], void callback(int fichiers[2], int resultat[2])) {
	pid_t pid;
	switch (pid = fork()) {
		case -1:
			perror("fork");
			return 0;
			break;
		case 0:
			callback(fichiers, resultat);
			exit(0);
			break;
		default:
			return 1;
	}
}

struct mapping {
	char * code;
	char * name;
};

static void traiterFichier(int fichiers[2], int resultat[2]) {
	close(fichiers[1]);

	char buffer[1025] = {0};
	char content[128] = {0};

	struct mapping map[] = {
		{"GIF87a", "GIF"},
		{"GIF89a", "GIF"},
		{"ID3", "MP3"},
		{"fLaC", "FLAC"},
		{"#!", "SHEBANG"},
		{"%PDF", "PDF"}
	};

	while (read(fichiers[0], buffer, 1024) > 0) {
		int fd;
		if ((fd = open(buffer, O_RDONLY)) == -1) {
			perror("open");
			continue;
		}

		if (read(fd, &content, 127) <= 0) {
			close(fd);
			continue;
		}

		int i = 0;
		while (i < 6) {
			struct mapping cur = map[i];
			if (streq(content, cur.code)) {
				char * buf;
				if ((buf = calloc(sizeof(int) + sizeof(ino_t) + 10, sizeof(char))) == NULL) {
					perror("calloc");
					continue;
				}

				strcpy(
			}
			i++;
		}

		close(fd);
	}

	close(fichiers[0]);
}

static int is_sys(char * a) {
	if (a[0] == 0) return 0;
	if (a[0] == '.' && a[1] == 0) return 1;
	if (a[0] == '.' && a[1] == '.' && a[2] == 0) return 1;
	return 0;
}
static void parcours_arborescence(char * path, int fichiers[2]) {
	DIR * rep;
	if ((rep = opendir(path)) == NULL) return;

	struct dirent * ent;
	struct stat sb;

	while ((ent = readdir(rep)) != NULL) {
		if (is_sys(ent->d_name)) continue;
		char * newpath;
		if ((newpath = calloc(1025, sizeof(char))) == NULL) continue;

		strcat(newpath, path);
		strcat(newpath, "/");
		strcat(newpath, ent->d_name);

		if (lstat(newpath, &sb) == -1) {
			free(newpath);
			continue;
		}

		if (S_ISDIR(sb.st_mode)) {
			parcours_arborescence(newpath, fichiers);
		} else {
			write(fichiers[1], newpath, 1024);
		}

		free(newpath);
	}

	closedir(rep);
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		printf("Arguments insuffisants\n");
		return 1;
	}
	int childs = 0;

	int fichiers[2], resultat[2];
	if (pipe(fichiers) == -1) {
		perror("pipe : fichiers ;");
		return 1;
	}
	if (pipe(resultat) == -1) {
		perror("fork : resultat");
		close(fichiers[0]);
		close(fichiers[1]);
		return 1;
	}

	int i = 0;
	while (i < N) {
		childs += create_child(fichiers, resultat, traiterFichier);
		i++;
	}
	if (childs == 0) {
		printf("Aucun fils crée\n");
		close(fichiers[0]);
		close(fichiers[1]);
		close(resultat[0]);
		close(resultat[1]);
		return 1;
	}

	// On est dans le parent
	close(fichiers[0]);
	parcours_arborescence(argv[1], fichiers);

	close(fichiers[1]);

	return 0;
}

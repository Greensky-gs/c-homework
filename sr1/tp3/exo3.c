#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void afficher_inode(struct stat * infos) {
	printf(" ");
	switch (infos->st_mode & S_IFMT) {
		case S_IFBLK: printf("bloc      "); break;
		case S_IFCHR: printf("caractère "); break;
		case S_IFDIR: printf("dossier   "); break;
		case S_IFIFO: printf("FIFO/pipe "); break;
		case S_IFLNK: printf("symlink   "); break;
		case S_IFREG: printf("fichier   "); break;
		case S_IFSOCK: printf("scoket    ");break;
		default: printf("N/A       ");break;
	}

	printf("   %-8ld", infos->st_size);
	printf("   %-20s", ctime(&(infos->st_mtime)));
}

static int is_2p(char * a) {
	if (a[0] == 0) return 0;
	if (a[0] == '.' && a[1] == 0) return 0;
	if (a[0] == '.' && a[1] == '.' && a[2] == 0) return 1;
	return 0;
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Arguments invalides\n");
		return 1;
	}

	if (argc == 2) {
		struct stat sb;
		if (lstat(argv[1], &sb) == -1) {
			perror("lstat");
			return 1;
		}

		if ((sb.st_mode & S_IFMT) != S_IFDIR) {
			printf("    %-20s", argv[1]);
			afficher_inode(&sb);
			return 0;
		}

		DIR * dir;
		if ((dir = opendir(argv[1])) == NULL) {
			perror("opendir");
			return 1;
		}

		struct dirent * temp = readdir(dir);
		struct stat statbuf;
		while (temp != NULL) {
			if (lstat(temp->d_name, &statbuf) == -1) {
				printf("Erreur lecture \x1b[33m%s\x1b[0m, ignorage\n", temp->d_name);
				temp = readdir(dir);
				continue;
			}

			if (is_2p(temp->d_name)) {
				temp = readdir(dir);
				continue;
			}

			printf(" %-20s", temp->d_name);
			afficher_inode(&statbuf);

			temp = readdir(dir);
		}

		closedir(dir);
		return 0;
	}

	int i = 1;
	while (i < argc) {
		struct stat sb;
		if (lstat(argv[i], &sb) == -1) {
			printf("Erreur lecture de \x1b[33m%s\x1b[0m, ignoration\n", argv[i]);
			i++;
			continue;
		}

		printf("   %-20s ", argv[i]);
		afficher_inode(&sb);

		i++;
	}
}

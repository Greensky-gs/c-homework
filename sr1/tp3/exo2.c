#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

void afficher_inode(struct stat * infos) {
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

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Arguments invalides\n");
		return 1;
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

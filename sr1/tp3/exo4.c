#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

static int is_rep(char * a) {
	if (a[0] == 0) return 0;
	if (a[0] == '.' && a[1] == 0) return 1;
	if (a[0] == '.' && a[1] == '.' && a[2] == 0) return 1;
	return 0;
}

int empty_count(char * a) {
	struct stat statbuf;
	if ((lstat(a, &statbuf)) == -1) {
		perror("lstat");
		return 0;
	}

	if ((statbuf.st_mode & S_IFMT) == S_IFREG) {
		int res = statbuf.st_size == 0;
		if (res) printf("%s\n", a);
		return res;
	} else if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
		DIR * rep;
		if ((rep = opendir(a)) == NULL) {
			perror("opendir");
			return 0;
		}
		struct dirent * direntb;

		int sum = 0;
		while ((direntb = readdir(rep)) != NULL) {
			if (is_rep(direntb->d_name)) continue;
			char * next = calloc(strlen(a) + strlen(direntb->d_name) + 2, sizeof(char));
			strcat(next, a);
			strcat(next, "/");
			strcat(next, direntb->d_name);
			sum += empty_count(next);

			free(next);
		};

		closedir(rep);
		return sum;
	}
	return 0;
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		printf("Argument invalide\n");
		return 1;
	}

	int empties = empty_count(argv[1]);
	printf("Empties found = %d\n", empties);

	return 0;
}

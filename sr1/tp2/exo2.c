#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


static int read_nieme(char name[], int n) {
	int file = open(name, O_RDONLY, 0);
	if (file < 0) return -1;

	int size = lseek(file, 0, SEEK_END) / sizeof(int);
	if (n > size || n < 0) {
		close(file);
		return -2;
	}

	if (lseek(file, n * sizeof(int), SEEK_SET) < 0) {
		close(file);
		return -3;
	};
	
	int buffer;
	if (read(file, &buffer, sizeof(int)) < 0) {
		close(file);
		return -4;
	};

	close(file);
	return buffer;
}
static int write_nieme(char name[], int n, int val) {
	int file = open(name, O_WRONLY, 0);
	if (file < 0) return -1;

	int size = lseek(file, 0, SEEK_END) / sizeof(int);
	if (n > size || n < 0) {
		close(file);
		return -2;
	}

	if (lseek(file, n * sizeof(int), SEEK_SET) < 0) {
		close(file);
		return -3;
	};
	
	if (write(file, &val, sizeof(int)) < 0) {
		close(file);
		return -4;
	};

	close(file);
	return val;
}

int main(int argc, char * argv[]) {
	if (argc < 3) return -1;

	if (argc == 3) {
		int n;
		sscanf(argv[1], "%d", &n);
	
		int res = read_nieme(argv[2], n);
		switch (res) {
			case -1:
				printf("Invalid fichier\n");
				break;
			case -2:
				printf("Invalid n\n");
				break;
			case -3:
				printf("L lseek il a pas marché\n");
				break;
			case -4:
				printf("Cannot read chef\n");
				break;
			default:
				printf("Lu = %d\n", res);
				break;
		}
	} else if (argc == 4) {
		int n, v;
		if (sscanf(argv[1], "%d", &n) == 0) {
			printf("Invalid n\n");
			return 1;
		}
		if (sscanf(argv[2], "%d", &v) == 0) {
			printf("Invalid value");
			return 1;
		}

		int res = write_nieme(argv[3], n, v);
		switch (res) {
			case -1:
				printf("Invalid fichier\n");
				break;
			case -2:
				printf("Invalid n\n");
				break;
			case -3:
				printf("L lseek il a pas marché\n");
				break;
			case -4:
				printf("Cannot read for write\n");
				break;
			default:
				printf("Ecrit correctement\n" );
				break;
		}
	} else {
		printf("Invalid args\n");
	}
}

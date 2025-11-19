CC=gcc
FLAGS=-Wall -fsanitize=address,undefined -g
STDLIBS=-lm

tp8exo2.exe: tp8exo2.c matrice.o image.o
	$(CC) tp8exo2.c matrice.o image.o $(FLAGS) $(STDLIBS) -o tp8exo2.exe

image.o: image.c image.h
	$(CC) image.c -c -o image.o $(FLAGS)

matrice.o: matrice.c matrice.h
	$(CC) matrice.c -c -o matrice.o $(FLAGS)

clean:
	rm -rf *.o *.exe

launch:
	make clean
	make
	clear
	./tp8exo2.exe

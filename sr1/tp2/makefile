main.uwu: main.c
	gcc main.c -o main.uwu -Wall -Wextra -fsanitize=address,undefined -g

clean:
	rm *.uwu -f

launch:
	make clean
	make
	clear
	./main.uwu

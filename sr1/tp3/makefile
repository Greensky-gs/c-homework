INPUT=main.c
OUTPUT=main.uwu
CC=gcc
FLAGS=-Wall -Wextra
SANTS=-fsanitize=address,undefined

$(OUTPUT): $(INPUT)
	$(CC) $(INPUT) $(FLAGS) $(SANTS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

full:
	make clean
	make
	clear
	./$(OUTPUT)

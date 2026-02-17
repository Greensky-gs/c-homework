FLAGS=-Wall
SANIT=-fsanitize=address,undefined

tri: tri.c
	gcc tri.c $(FLAGS) $(SANIT) -o tri.exe && ./tri.exe
pascal: pascal.c
	gcc pascal.c $(FLAGS) $(SANIT) -o pascal.exe && ./pascal.exe

main: main.c
	gcc main.c $(FLAGS) $(SANIT) -o main.exe && ./main.exe

clean:
	rm -rf *.o
	rm -rf *.exe

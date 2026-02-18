TARGET=main.exe
SOURCE=main.c

$(TARGET): $(SOURCE)
	gcc $(SOURCE) -o $(TARGET) -g -Wall -Wextra -fsanitize=address,undefined

launch: $(TARGET)
	rm $(TARGET) -f
	make
	clear
	./$(TARGET)

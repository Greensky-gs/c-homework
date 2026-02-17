CC=gcc
FLAGS=-Wall
EXE=main.exe
SANITIZES=-fsanitize=address,undefined -g

# Variable des sanitizers passés dans la commande
SANITIZERS=
ifeq ($(strip $(S)),)
	ifneq (,$(findstring S,$(MAKEFLAGS)))
		# Si on a -S dans la ligne de commande on rajoute les sanitizers
		SANITIZERS=$(SANITIZES)
	endif
endif

# Message d'avertissement des sanitizers
ECHO_MSG=@echo -e "\033[0;32mCompilation normale\033[0m"

ifneq ($(strip $(SANITIZERS)),) # Modification
	ECHO_MSG=@echo -e "\033[0;31mAjout des sanitizers\033[0m"
endif

$(EXE): main.c
	$(ECHO_MSG)
	$(CC) main.c -o $(EXE) $(FLAGS) $(SANITIZERS)

clean:
	rm -rf *.o *.exe
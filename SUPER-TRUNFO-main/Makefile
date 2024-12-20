# compilador e flags??
CC = gcc
CFLAGS = -Wall -Wextra -O2

# nome do arquivo exe
TARGET = estrutura_beta

# fontes e headers
SRC = estrutura_beta.c struct_card.c gerenciamento_deck.c
OBJ = $(SRC:.c=.o)

# sistema operacional
OS := $(shell uname 2>/dev/null || echo Windows)

all: $(TARGET)

# criar o executável
$(TARGET): $(OBJ)
	@echo "Gerando arquivo executável"
ifeq ($(OS), Windows)
	$(CC) $(OBJ) -o $(TARGET).exe
else
	$(CC) $(OBJ) -o $(TARGET)
endif

# compilando obj
%.o: %.c
	@echo "Compilando e gerando os objetos"
	$(CC) $(CFLAGS) -c $< -o $@

# limpa arquivos criados
clean:
	@echo "Apagando objetos e executáveis antigos..."
ifeq ($(OS), Windows)
	del /f /q $(OBJ) $(TARGET).exe
else
	rm -f $(OBJ) $(TARGET)
endif

# executar os programas
run: all
ifeq ($(OS), Windows)
	@$(TARGET).exe
else
	@./$(TARGET)
endif
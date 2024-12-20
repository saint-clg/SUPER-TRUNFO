# Nome do compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Nome do executável
TARGET = estrutura_beta

# Arquivos fonte e cabeçalhos
SRC = estrutura_beta.c struct_card.c gerenciamento_deck.c
OBJ = $(SRC:.c=.o)

# Detecta o sistema operacional
OS := $(shell uname 2>/dev/null || echo Windows)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJ)
	@echo "Gerando arquivo executável"
ifeq ($(OS), Windows)
	$(CC) $(OBJ) -o $(TARGET).exe
else
	$(CC) $(OBJ) -o $(TARGET)
endif

# Regra para compilar os objetos
%.o: %.c
	@echo "Compilando e gerando os objetos"
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza de arquivos gerados
clean:
	@echo "Apagando objetos e executáveis antigos..."
ifeq ($(OS), Windows)
	del /f /q $(OBJ) $(TARGET).exe
else
	rm -f $(OBJ) $(TARGET)
endif

# Regra para executar o programa
run: all
ifeq ($(OS), Windows)
	@$(TARGET).exe
else
	@./$(TARGET)
endif
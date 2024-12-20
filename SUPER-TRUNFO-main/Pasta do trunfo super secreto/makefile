# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g

# Arquivos-fonte
SRCS = estrutura_beta.c gerenciamento_deck.c

# Arquivos de cabeçalho
HEADERS = gerenciamento_deck.h struct_card.h

# Arquivo executável
TARGET = programa

# Regra principal
all: $(TARGET)

# Como compilar o executável
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Limpeza
clean:
	rm -f $(TARGET)

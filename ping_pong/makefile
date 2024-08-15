# Nome do arquivo executável
TARGET = main

# Arquivo objeto necessário para a linkagem
OBJS = main.o

# Compilador
CC = mpicc

# Opções de linkagem
LDFLAGS = -o

# Regra padrão de linkagem
all: $(TARGET)

# Regra para linkar o arquivo objeto e gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(TARGET) $(OBJS)

# Regra de limpeza
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

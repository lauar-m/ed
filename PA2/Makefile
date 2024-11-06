# Nome do executável
TARGET = bin/pa1.out

# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -g -I include  # Adiciona o diretório include

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regra principal
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para criar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

#all: $(TARGET)
#	./$(TARGET) -z 9 -s 27 -a s
#	./$(TARGET) -z 9 -s 27 -a i
#	./$(TARGET)	-z 9 -s 27 -a q
#	./$(TARGET)	-z 9 -s 27 -a q3
#	./$(TARGET)	-z 9 -s 27 -a qi
#	./$(TARGET)	-z 9 -s 27 -a q3i
#	./$(TARGET)	-z 9 -s 27 -a h
#	./$(TARGET)	-z 9 -s 27 -a rs
#	./$(TARGET)	-z 81 -s 17 -a s
#	./$(TARGET)	-z 81 -s 17 -a i
##	./$(TARGET)	-z 81 -s 17 -a q
#	./$(TARGET) -z 81 -s 17 -a q3
#	./$(TARGET)	-z 81 -s 17 -a qi
##	./$(TARGET)	-z 81 -s 17 -a h
#	./$(TARGET)	-z 81 -s 17 -a rs
#	./$(TARGET)	-z 448 -s 15 -a i
##./$(TARGET)	-z 448 -s 15 -a q
#	./$(TARGET)	-z 448 -s 15 -a q3
#	./$(TARGET)	-z 448 -s 15 -a qi
#	./$(TARGET)	-z 448 -s 15 -a q3i
#	./$(TARGET)	-z 448 -s 15 -a h
#	./$(TARGET)	-z 448 -s 15 -a rs
#	./$(TARGET)	-z 4803 -s 34 -a s
#	./$(TARGET) -z 4803 -s 34 -a i
##	./$(TARGET) -z 4803 -s 34 -a q
#./$(TARGET)	-z 4803 -s 34 -a q3
#./$(TARGET) -z 4803 -s 34 -a qi
#	./$(TARGET)	-z 4803 -s 34 -a q3i
#	./$(TARGET)	-z 4803 -s 34 -a h
#	./$(TARGET) -z 19097 -s 25 -a s
##	./$(TARGET)	-z 19097 -s 25 -a i
#./$(TARGET) -z 19097 -s 25 -a q
#	./$(TARGET)	-z 19097 -s 25 -a q3
#	./$(TARGET)	-z 19097 -s 25 -a qi
#	./$(TARGET)	-z 19097 -s 25 -a q3i
#	./$(TARGET) -z 19097 -s 25 -a h
#	./$(TARGET)	-z 19097 -s 25 -a rs


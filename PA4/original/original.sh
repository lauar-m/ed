#!/bin/bash

# Diretório com os arquivos .c
SOURCE_DIR="/home/malulauar/ED/ed/PA4/original"
TIMEOUT_LIMIT=45  # Limite de tempo para evitar loop infinito

# Compilação dos arquivos .c em executáveis
for file in "$SOURCE_DIR"/*.c; do
    if [ -f "$file" ]; then
        # Nome do arquivo sem a extensão .c
        output="${file%.c}"

        # Compilação do arquivo C em um executável
        echo "Compilando $file..."
        gcc -g -o "$output" "$file"

        # Verifica se a compilação foi bem-sucedida
        if [ $? -eq 0 ]; then
            echo "Compilação bem-sucedida para $file. Analisando com Valgrind..."

            # Executa o Valgrind no executável com limite de tempo
            timeout $TIMEOUT_LIMIT valgrind --leak-check=full --track-origins=yes --verbose --log-file="$output-valgrind.log" "$output"

            # Verifica se Valgrind encontrou problemas e se o tempo de execução foi excedido
            if [ $? -eq 0 ]; then
                echo "Análise do Valgrind concluída para $file. Executando com GDB..."

                # Executa o GDB no executável
                gdb "$output" 
            else
                echo "Valgrind não encontrou problemas ou o tempo de execução foi excedido para $file."
            fi
        else
            echo "Falha na compilação para $file."
        fi
    fi
done

# Limpar arquivos .log e executáveis
find "$SOURCE_DIR" -name "*.log" -type f -delete
find "$SOURCE_DIR" -name "*.out" -type f -delete
#!/bin/bash

# --- Script para rodar o simulador para varios arquivos e agregar os resultados ---

SIMULADOR="./bin/tp2.out"
ARQUIVO_DE_RESULTADOS="pacote.txt"

echo "--- Iniciando todas as simulacoes ---"

# Compila o simulador uma unica vez
make
if [ $? -ne 0 ]; then
    echo "Erro ao compilar o simulador! Abortando."
    exit 1
fi

# Encontra todos os arquivos que comecam com 'entrada' e terminam com '.txt'
for arquivo_de_entrada in entrada*.txt
do
    # Verifica se o arquivo realmente existe
    if [ -f "$arquivo_de_entrada" ]; then
        echo "Processando simulacao para: $arquivo_de_entrada"

        # Executa o simulador, lendo do arquivo de entrada e
        # adicionando (>>) a saida ao arquivo de resultados final
        "$SIMULADOR" "$arquivo_de_entrada" >> "$ARQUIVO_DE_RESULTADOS"
    fi
done

echo "--- Simulacoes concluidas! Resultados agregados em: $ARQUIVO_DE_RESULTADOS ---"
#!/bin/bash

# --- Script para executar uma lista de comandos e gerar os arquivos de entrada ---

ARQUIVO_DE_COMANDOS="comandos.txt"

echo "--- Iniciando geracao de todos os arquivos de entrada ---"

# Verifica se o arquivo com os comandos existe
if [ ! -f "$ARQUIVO_DE_COMANDOS" ]; then
    echo "Erro: Arquivo '$ARQUIVO_DE_COMANDOS' nao encontrado!"
    exit 1
fi

# Le o arquivo linha por linha e executa cada linha como um comando
while IFS= read -r comando
do
    eval "$comando"
done < "$ARQUIVO_DE_COMANDOS"

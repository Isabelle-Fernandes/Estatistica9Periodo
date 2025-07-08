#!/bin/bash

# --- SCRIPT PARA GERAR TODOS OS CENARIOS DE ENTRADA PARA O TP3 ---

echo "--- INICIANDO GERACAO DE CENARIOS ---"

# --- 1. CONFIGURACAO E COMPILACAO ---
echo "Compilando os programas necessarios..."

# Compila o gerador de cenarios (assumindo que ele foi modificado para ler argv)
gcc -o genwkl3 genwkl3.c -lm
if [ $? -ne 0 ]; then
    echo "ERRO: Falha ao compilar genwkl3.c. Abortando."
    exit 1
fi
# Verifica se o executavel 'sched' do TP2 existe
if [ ! -f ./sched ]; then
    echo "ERRO: Executavel './sched' nao encontrado. Abortando."
    exit 1
fi

echo "Programas prontos."

# --- 2. LOOP DE GERACAO ---
ARQUIVO_CENARIOS="cenarios.txt"
DIR_SAIDA="entradas_finais_tp3"
mkdir -p "$DIR_SAIDA" # Cria o diretorio para os resultados, se nao existir

contador=1
while read -r capacidade nos pacotes clientes
do
    echo "--> Gerando cenario $contador: (Capacidade: $capacidade, Nos: $nos, Pacotes: $pacotes, Clientes: $clientes)"
    
    # Define o nome do arquivo de saida final para esta iteracao
    ARQUIVO_FINAL="${DIR_SAIDA}/entrada_${contador}.txt"

    # --- EXECUTA O PIPELINE COMPLETO ---

    # 1. Gera os arquivos .wkl com os parametros da linha atual
    # CORRECAO: Passa cada parametro separadamente
    ./genwkl3 "$capacidade" "$nos" "$pacotes" "$clientes"
    
    # 2. Executa o simulador do TP2 para gerar o log de eventos
    # CORRECAO: Adiciona a saida para sched.log
    ./sched < tp2.wkl > sched.log
    
    # 3. Reformata a saida do TP2 para o formato de eventos do TP3
    sed -f tp2tp3.sed sched.log | awk -f intp3.awk > tmptp3.out
    
    # 4. Concatena os eventos gerados com as consultas e ordena, salvando no arquivo final
    cat tp3.wkl tmptp3.out | sort > "$ARQUIVO_FINAL"

    # Incrementa o contador para o proximo nome de arquivo
    ((contador++))
    
done < "$ARQUIVO_CENARIOS"


# --- 3. LIMPEZA ---
# CORRECAO: Limpa todos os arquivos temporarios no final
echo "Limpando arquivos temporarios..."
rm -f tp2.wkl tp3.wkl sched.log tmptp3.out

echo "--- PROCESSO CONCLUIDO ---"
echo "Todos os arquivos de entrada foram gerados na pasta: $DIR_SAIDA"

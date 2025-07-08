#!/bin/bash

# --- Script para rodar o simulador para varios arquivos e agregar os resultados ---

SIMULADOR="./bin/tp3.out"
# Alterado para .csv para facilitar a abertura em programas de planilha
ARQUIVO_DE_RESULTADOS="resultados_finais.csv" 
DIR_ENTRADA="entradas_finais_tp3"
ARQUIVO_CENARIOS="entradas_tipo" ### Adicionada a variavel para o arquivo de cenarios

echo "--- Iniciando todas as simulacoes ---"

# Compila o simulador uma unica vez
make
if [ $? -ne 0 ]; then
    echo "Erro ao compilar o simulador! Abortando."
    exit 1
fi

### Prepara o arquivo de resultados, limpando o antigo e adicionando um cabecalho
echo "Tempo Status Tipo Valor Tipo_Consulta" > "$ARQUIVO_DE_RESULTADOS"

### Abre o arquivo de cenarios para leitura em um "canal" separado (file descriptor 3)
exec 3<"$ARQUIVO_CENARIOS"

# Encontra todos os arquivos que comecam com 'entrada' e terminam com '.txt'
# A mudanca aqui e usar `sort -V` para garantir a ordem numerica correta (entrada_1, entrada_2, ... entrada_10)
find "$DIR_ENTRADA" -name "entrada_*.txt" | sort -V | while read -r arquivo_de_entrada
do
    # Verifica se o arquivo realmente existe
    if [ -f "$arquivo_de_entrada" ]; then
        
        ### Le a proxima linha do arquivo de cenarios e guarda as colunas em variaveis
        if read -r -u 3 col1 col2 col3 col4 col5; then
            echo "Processando: $(basename "$arquivo_de_entrada") com cenario: $col5"

            # Variaveis que serao passadas para o seu programa C++
            tipo=""
            valor=""

            ### Logica para definir 'tipo' e 'valor' com base na coluna 5
            case "$col5" in
                "\"pacote\"") # As aspas fazem parte do texto, entao precisamos incluí-las
                    tipo="pacote"
                    valor="$col3"
                    ;;
                "\"cliente\"")
                    tipo="cliente"
                    valor="$col4"
                    ;;
                "\"evento\"")
                    tipo="evento"
                    valor="$col1"
                    ;;
                *)
                    # Se nao for nenhum dos tipos esperados, pula esta iteracao
                    echo "AVISO: Tipo de cenario desconhecido ('$col5'). Pulando."
                    continue
                    ;;
            esac
            
            ### Executa o simulador com os 3 argumentos necessarios.
            # A saida de tempo (que voce imprime em stderr) e capturada.
            # A saida normal (as respostas das consultas) e descartada com >/dev/null.
	    "$SIMULADOR" "$arquivo_de_entrada" "$tipo" "$valor" >> "$ARQUIVO_DE_RESULTADOS"

        else
            echo "AVISO: Acabaram as linhas no arquivo de cenarios. Parando."
            break
        fi
    fi
done

### Fecha o "canal" de leitura do arquivo de cenarios
exec 3<&-

echo "--- Simulacoes concluidas! Resultados agregados em: $ARQUIVO_DE_RESULTADOS ---"

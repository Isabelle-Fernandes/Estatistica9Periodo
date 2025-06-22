# --- Configuracao ---
# Define a quantidade de pacotes que serao gerados
num_pacotes <- 100

# Define o numero de armazens (vertices) no seu grafo
num_armazens <- 15

# Define o nome do arquivo de saida
arquivo_saida <- "pacotes.txt"


# --- Geracao dos Dados ---

# 1. Gera a data/hora da postagem como inteiros
# Gera numeros aleatorios entre 0 e 200 para os tempos de chegada
# e depois ordena para que fiquem em ordem cronologica.
data_hora_postagem <- sort(sample(0:200, num_pacotes, replace = TRUE))

# 2. Gera os armazens de origem e destino
armazem_origem <- sample(0:(num_armazens - 1), num_pacotes, replace = TRUE)
armazem_destino <- sample(0:(num_armazens - 1), num_pacotes, replace = TRUE)

# 3. Garante que origem e destino nunca sejam iguais
# Enquanto houver qualquer pacote com origem igual ao destino...
while(any(armazem_origem == armazem_destino)) {
  # ...identifica quais sao esses pacotes...
  indices_iguais <- which(armazem_origem == armazem_destino)
  # ...e gera um novo destino *apenas* para eles.
  armazem_destino[indices_iguais] <- sample(0:(num_armazens - 1), length(indices_iguais), replace = TRUE)
}

# 4. Cria colunas placeholder para os outros campos
# Estes campos serao ignorados pelo seu codigo C++, mas mantem a estrutura
remetente <- "NULL"
destinatario <- "NULL"
tipo_pacote <- 0

# 5. Combina tudo em um data frame (uma tabela de dados)
# A ordem das colunas e a mesma que voce especificou
dados_pacotes <- data.frame(
  DataHora = data_hora_postagem,
  Remetente = remetente,
  Destinatario = destinatario,
  Tipo = tipo_pacote,
  Origem = armazem_origem,
  Destino = armazem_destino
)


# --- Salvando o Arquivo ---

# Escreve o data frame em um arquivo de texto
# Os parametros garantem que o arquivo seja limpo, sem nomes de linha/coluna
# e com valores separados por espaco.
write.table(
  dados_pacotes,
  file = arquivo_saida,
  row.names = FALSE,
  col.names = FALSE,
  sep = " ",
  quote = FALSE
)

# Mensagem de confirmacao no console do R
print(paste("Arquivo", arquivo_saida, "gerado com sucesso com", num_pacotes, "pacotes."))
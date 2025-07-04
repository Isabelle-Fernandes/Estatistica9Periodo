#include "../include/BancoDados.hpp"
#include "../include/ArvoreAVLPacote.hpp"
#include "../include/ArvoreAVLClientes.hpp"  
#include "../include/ListaPacotesCliente.hpp" 

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1;
    }
    
    std::string nome_arquivo = argv[1];
    std::ifstream arquivo_entrada(nome_arquivo);

    if (!arquivo_entrada.is_open()) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo de entrada: " << nome_arquivo << std::endl;
        return 1;
    }

    BancoDados banco = BancoDados();
    ArvoreAVLPacote indicePacotes = ArvoreAVLPacote(); // Indice para a consulta PC
    ArvoreAVLClientes indiceClientes = ArvoreAVLClientes(); // Indice para a consulta CL
    Evento e = Evento();

    int tempo;
    char identificador_entrada[3] = {0};
    
    while (arquivo_entrada >> tempo >> identificador_entrada) {
        
        if (strcmp(identificador_entrada, "EV") == 0) {
            char tipo_evento_str[3] = {0};
            int id_pacote;
            arquivo_entrada >> tipo_evento_str >> id_pacote;
            
            // Leitura e Criacao do Evento
            if (strcmp(tipo_evento_str, "RG") == 0) {
                char rem_str[100], dest_str[100]; 
                int orig, dest_final;
                arquivo_entrada >> rem_str >> dest_str >> orig >> dest_final;
                e.criarEventoRG(tempo, tipo_evento_str, id_pacote, rem_str, dest_str, orig, dest_final);
            } else if (strcmp(tipo_evento_str, "AR") == 0 || strcmp(tipo_evento_str, "RM") == 0 || strcmp(tipo_evento_str, "UR") == 0) {
                int armazem, secao;
                arquivo_entrada >> armazem >> secao;         
                e.criarEventoSimples(tempo, tipo_evento_str, id_pacote, armazem, secao);
            } else if (strcmp(tipo_evento_str, "TR") == 0) {
                int origem, destino;
                arquivo_entrada >> origem >> destino;
                e.criarEventoTransporte(tempo, tipo_evento_str, id_pacote, origem, destino);
            } else if (strcmp(tipo_evento_str, "EN") == 0) {
                int armazem;
                arquivo_entrada >> armazem;
                e.criarEventoEntrega(tempo, tipo_evento_str, id_pacote, armazem);
            }

            // Armazenamento e Indexacao
            banco.addEvento(e);
            int indiceDoNovoEvento = banco.tamanho - 1;
            Evento* ponteiroEvento = &banco.eventos[indiceDoNovoEvento];

            // Atualiza o Indice de Pacotes
            indicePacotes.insere(id_pacote, indiceDoNovoEvento, tempo);

            // Atualiza o Indice de Clientes
            Fila<int>* historico = indicePacotes.busca(id_pacote);
            if (historico != nullptr) {
                int indiceRG = historico->primeiro->indice;
                indiceClientes.insere(banco.eventos[indiceRG].cliente_remetente, ponteiroEvento);
                indiceClientes.insere(banco.eventos[indiceRG].cliente_destinatario, ponteiroEvento);
            }

        } else if (strcmp(identificador_entrada, "CL") == 0) {
            char nome_str_c[100] = {0};
            arquivo_entrada >> nome_str_c;
            std::string nome_consulta(nome_str_c);

            printf("%06d CL %s\n", tempo, nome_str_c);

            ListaPacotesCliente* historicoCliente = indiceClientes.busca(nome_consulta);
            if (historicoCliente != nullptr) {
                historicoCliente->imprimeResultados(tempo);
            } else {
                printf("0\n");
            }

        } else if (strcmp(identificador_entrada, "PC") == 0) {
            int id_consulta;
            arquivo_entrada >> id_consulta; 

            Fila<int>* indices = indicePacotes.busca(id_consulta);

            printf("%06d PC %03d\n", tempo, id_consulta);
            std::cout << indices->tamanho << std::endl;
            NoFila<int>* atual = indices->primeiro;

            for(int i = 0; i < indices->tamanho; i++){
                banco.eventos[atual->indice].imprime();
                atual = atual->prox;
            }
        }
    }

    return 0;
}
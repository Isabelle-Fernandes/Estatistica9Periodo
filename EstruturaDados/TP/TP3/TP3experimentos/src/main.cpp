#include "../include/BancoDados.hpp"
#include "../include/ArvoreAVLPacote.hpp"
#include "../include/ArvoreAVLClientes.hpp"  
#include "../include/ListaPacotesCliente.hpp" 

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <cstdlib>

int main(int argc, char* argv[]) {
    
    if (argc < 4){
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1;
    }
    
    std::string nome_arquivo = argv[1];
    std::ifstream arquivo_entrada(nome_arquivo);
    std::string tipo = argv[2];
    int valor = atoi(argv[3]); 

    if (!arquivo_entrada.is_open()) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo de entrada: " << nome_arquivo << std::endl;
        return 1;
    }

    BancoDados banco = BancoDados();
    ArvoreAVLPacote indicePacotes = ArvoreAVLPacote(); // Indice para a consulta PC
    ArvoreAVLClientes indiceClientes = ArvoreAVLClientes(); // Indice para a consulta CL

    int tempo;
    char identificador_entrada[3] = {0};
    
    while (arquivo_entrada >> tempo >> identificador_entrada) {
        
        if (strcmp(identificador_entrada, "EV") == 0) {
            char tipo_evento_str[3] = {0};
            int id_pacote;
            arquivo_entrada >> tipo_evento_str >> id_pacote;
            Evento e;
            
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
            Evento* ponteiroEvento = banco.eventos[indiceDoNovoEvento];

            // Atualiza o Indice de Pacotes
            indicePacotes.insere(id_pacote, indiceDoNovoEvento);

            // Atualiza o Indice de Clientes
            Fila<int>* historico = indicePacotes.busca(id_pacote);
            if (historico != nullptr) {
                int indiceRG = historico->primeiro->indice;
                indiceClientes.insere(banco.eventos[indiceRG]->cliente_remetente, ponteiroEvento);
                indiceClientes.insere(banco.eventos[indiceRG]->cliente_destinatario, ponteiroEvento);
            }
            
        } else if (strcmp(identificador_entrada, "CL") == 0) {

            char nome_str_c[100] = {0};
            arquivo_entrada >> nome_str_c;
            std::string nome_consulta(nome_str_c);

            auto start = std::chrono::high_resolution_clock::now();
        
            //printf("%07d CL %s\n", tempo, nome_str_c);
        
            // busca pelo cliente. Se ele nao existir, 'historicoCliente' sera nullptr.
            ListaPacotesCliente* historicoCliente = indiceClientes.busca(nome_consulta);
        
            // Ela impede que o programa tente usar um ponteiro nulo, caso o cliente nao exista no historico
            if (historicoCliente != nullptr) {
                // historicoCliente->imprimeResultados(tempo);
                auto end = std::chrono::high_resolution_clock::now();
                long long duracao = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << std::fixed << std::setprecision(7) << duracao << " " << "ok" << " " << tipo << " " << valor << " CL" << std::endl;
            } else {   
                // Se o cliente nao foi encontrado, imprime 0. Perfeito.
                std::cout << 0 << " " << "x" << " " << tipo << " " << valor << " CL" << std::endl;
            }
        
            } else if (strcmp(identificador_entrada, "PC") == 0) {
            int id_consulta;
            arquivo_entrada >> id_consulta; 

            auto start = std::chrono::high_resolution_clock::now();

            Fila<int>* indices = indicePacotes.busca(id_consulta);

            //printf("%06d PC %03d\n", tempo, id_consulta);
            
            if (indices != nullptr && !indices->estahVazia()) {
                // std::cout << indices->tamanho << std::endl;
                NoFila<int>* atual = indices->primeiro;

                for(int i = 0; i < indices->tamanho; i++){
                    //banco.eventos[atual->indice]->imprime();
                    atual = atual->prox;
                }
                auto end = std::chrono::high_resolution_clock::now();
                long long duracao = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << std::fixed << std::setprecision(7) << duracao << " " << "ok" << " "
                        << tipo << " " << valor << " PC" << std::endl;
            } else {
                // Se o pacote nao foi encontrado, a resposta e 0.
                std::cout << 0 << " " << "x" << " " << tipo << " " << valor << " PC" << std::endl;
                ;
            }
        }
    }
    return 0;

}
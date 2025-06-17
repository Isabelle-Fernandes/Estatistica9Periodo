#include "Grafo.hpp"
#include "CalculaRota.hpp"
#include <iostream>


int main(int argc, char* argv[]){

    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1;
    }
    
    std::string nome_arquivo = argv[1];
    std::ifstream arquivo_grafo(nome_arquivo);

    int numeroVertices;

    arquivo_grafo >> numeroVertices;
    Grafo grafo(numeroVertices);

    for(int i = 0; i < numeroVertices; i++){
        int qtdeVizinho;
        arquivo_grafo >> qtdeVizinho;
        for(int j = 0; j < qtdeVizinho; j++){
            int vizinho;
            arquivo_grafo >> vizinho;
            grafo.addAresta(i, vizinho);
        }
    }

    nome_arquivo = argv[2];
    std::ifstream arquivo_pacote(nome_arquivo);

    int qtdePacotes;
    arquivo_pacote >> qtdePacotes;
    
    Pacote pacotes[qtdePacotes];
    
    for(int i = 0; i < qtdePacotes; i++){
        int tempo, tipo, armazemOrigem, armazemDestino;
        char* remetente;
        char* destinatario;

        // Leitura dos dados do pacote
        arquivo_pacote >> tempo;
        remetente = lerPalavraDinamica(arquivo_pacote);
        destinatario = lerPalavraDinamica(arquivo_pacote);
        arquivo_pacote >> tipo >> armazemOrigem >> armazemDestino;

        pacotes[i].Inicializar(tempo, remetente, destinatario, tipo, armazemOrigem, armazemDestino);
        pacotes[i].rota = BuscaMenorRota(pacotes[i], grafo, pacotes[i].tamanhoRota); // calcula a rota para cada pacote
    }

    return 0;
}
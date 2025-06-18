#include "../include/Grafo.hpp"
#include "../include/CalculaRota.hpp"
#include <iostream>
#include <fstream>



int main(int argc, char* argv[]){

    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1;
    }
    
    std::string nome_arquivo = argv[1];
    std::ifstream arquivo_entrada(nome_arquivo);

    int capacidadeTransporte, latenciaTransporte, intervaloTransporte, custoRemocao, qtdeArmazem; 

    arquivo_entrada >> capacidadeTransporte >> latenciaTransporte >> intervaloTransporte >> custoRemocao >> qtdeArmazem;

    Grafo grafo(qtdeArmazem);

    // leitura do grafo
    for(int origem = 0; origem < qtdeArmazem; origem++){
        int vertice;
        for(int vizinho = 0; vizinho < qtdeArmazem; vizinho++){
            arquivo_entrada >> vertice;
            if(vertice == 1) grafo.addAresta(origem, vizinho);
        }
    }

    int qtdePacote;
    arquivo_entrada >> qtdePacote;
    Pacote pacotes[qtdePacote];
    
    // leitura dos dados do pacote
    for(int i = 0; i < qtdePacote; i++){
        char palavra[3];
        int tempoChegada, idPac, armazemOrigem, armazemDestino;
        arquivo_entrada >> tempoChegada >> palavra >> idPac >> palavra >> armazemOrigem >> palavra >> armazemDestino;
        pacotes[i].Inicializar(tempoChegada, idPac, armazemOrigem, armazemDestino);
        pacotes[i].rota = BuscaMenorRota(pacotes[i], grafo); // calcula a rota para cada pacote
    }

    return 0;
}
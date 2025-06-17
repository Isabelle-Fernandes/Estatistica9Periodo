#include "Grafo.hpp"
#include "CalculaRota.hpp"
#include <iostream>


int main(int argc, char* argv[]){

    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1;
    }
    
    std::string nome_arquivo = argv[1];
    std::ifstream arquivo_entrada(nome_arquivo);

    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;
    int custoRemocao;
    int qtdeArmazem;     

    arquivo_entrada >> capacidadeTransporte;
    arquivo_entrada >> latenciaTransporte;
    arquivo_entrada >> intervaloTransporte;
    arquivo_entrada >> custoRemocao;
    arquivo_entrada >> qtdeArmazem;

    Grafo grafo(qtdeArmazem);

    // leitura do grafo
    for(int origem = 0; origem < qtdeArmazem; origem++){
        for(int vizinho = 0; vizinho < qtdeArmazem; vizinho++){
            int vertice;
            arquivo_entrada >> vertice;
            if(vertice == 1){
                grafo.addAresta(origem, vizinho);
            }
        }
    }

    int qtdePacote;

    arquivo_entrada >> qtdePacote;
    
    Pacote pacotes[qtdePacote];
    
    // leitura dos dados do pacote
    for(int i = 0; i < qtdePacote; i++){
        char palavra;
        int tempoChegada, idPac, armazemOrigem, armazemDestino;

        arquivo_entrada >> tempoChegada;
        arquivo_entrada >> palavra;
        arquivo_entrada >> idPac;
        arquivo_entrada >> palavra;
        arquivo_entrada >> armazemOrigem;
        arquivo_entrada >> palavra;
        arquivo_entrada >> armazemDestino;

        pacotes[i].Inicializar(tempoChegada, idPac, armazemOrigem, armazemDestino);
        pacotes[i].rota = BuscaMenorRota(pacotes[i], grafo, pacotes[i].tamanhoRota); // calcula a rota para cada pacote
    }


    return 0;
}
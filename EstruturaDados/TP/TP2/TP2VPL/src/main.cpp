#include "../include/Grafo.hpp"
#include "../include/CalculaRota.hpp"
#include "../include/Armazem.hpp"
#include "../include/Escalonador.hpp"

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

    grafo.numeroLigacao = grafo.obterNumeroLigacao();

    // inicializa armazens
    Armazem armazens[qtdeArmazem];
    for (int i = 0; i < qtdeArmazem; i++) {
        armazens[i].inicializar(i, &grafo, custoRemocao);
    }

    // leitura dos dados do pacote
    int qtdePacote;
    arquivo_entrada >> qtdePacote;
    Pacote pacotes[qtdePacote];
    
    for(int i = 0; i < qtdePacote; i++){
        char palavra[3];
        int tempoChegada, idPac, armazemOrigem, armazemDestino;
        arquivo_entrada >> tempoChegada >> palavra >> idPac >> palavra >> armazemOrigem >> palavra >> armazemDestino;
        pacotes[i].Inicializar(tempoChegada, i, armazemOrigem, armazemDestino);
        pacotes[i].rota = BuscaMenorRota(pacotes[i], grafo); // calcula a rota para cada pacote
    }

//////////////   ESCALONADOR EM ACAO!!!  ///////////////////////////

    Escalonador escalonador(qtdePacote + grafo.numeroLigacao, intervaloTransporte);

    // inicializa relogio para o tempo do primeiro pacote que foi postado
    int relogioAtual = obterTempoPrimeiroPacotePostado(pacotes,  qtdePacote);

    // escalono evento transporte
    int tempoEscalonado = relogioAtual + intervaloTransporte;
    for(int vertice = 0; vertice < grafo.numeroVertices; vertice++) {
        Vertice* vizinho = grafo.listaAdjacencia[vertice]->origem->prox;
        while(vizinho != nullptr) {
            escalonador.insereEvento(Evento(tempoEscalonado, vertice, vizinho->vertice));
            vizinho = vizinho->prox; 
        }
    }
    
    // escalono evento pacote
    for (int i = 0; i < qtdePacote; i++) {
        escalonador.insereEvento(Evento(pacotes[i].tempoAtual, &pacotes[i], pacotes[i].armazemOrigem));
    }

    int pacotesEntregues = 0;
    
    while (pacotesEntregues < qtdePacote) {
        Evento evento = escalonador.retiraProximoEvento();
        relogioAtual = evento.tempoEscalonado;
    
        if (evento.tipo == PACOTE) {
            Pacote* p = evento.pacote;
            int armazemDeChegada = evento.IdArmazens[0];

            if(p->armazemDestino == armazemDeChegada){
                //std::cout << evento.chavePrioridade << " ";
                printf("%07d pacote %03d entregue em %03d\n", evento.tempoEscalonado, p->id, armazemDeChegada);
                pacotesEntregues ++;
            }
            else {
                armazens[armazemDeChegada].armazena(p, relogioAtual);
                //std::cout << evento.chavePrioridade << " ";
                printf("%07d pacote %03d armazenado em %03d na secao %03d\n", evento.tempoEscalonado, p->id, armazemDeChegada, p->getProximoDestinoNaRota());

            }
    
        } else if (evento.tipo == TRANSPORTE) {
            int origem = evento.IdArmazens[0];
            int destino = evento.IdArmazens[1];
            Armazem& armazemOrigem = armazens[origem];
            int indiceSecao = armazemOrigem.encontraIndiceDaSecao(destino);

            if (armazemOrigem.secoes[indiceSecao].estahVazia()) {
                escalonador.insereEvento(Evento(relogioAtual + intervaloTransporte, origem, destino));
                continue;
            }
    
            Pilha paraRearmazenar;
            int custoAcumulado = 0;
            
            while(!armazemOrigem.secoes[indiceSecao].estahVazia()) {
                Pacote* p = armazemOrigem.secoes[indiceSecao].desempilha();
                paraRearmazenar.empilha(p);
                custoAcumulado += custoRemocao;
                int tempoEvento = relogioAtual + custoAcumulado;
                //std::cout << evento.chavePrioridade << " ";
                printf("%07d pacote %03d removido de %03d na secao %03d\n", tempoEvento, p->id, origem, destino);
    
            }

            int tempoFinalOperacao = relogioAtual + custoAcumulado;
            int contador = 0;

            // Processa os pacotes para transporte
            while(!paraRearmazenar.estahVazia() && contador < capacidadeTransporte) {
                Pacote* p = paraRearmazenar.desempilha();
                //std::cout << evento.chavePrioridade << " ";
                printf("%07d pacote %03d em transito de %03d para %03d\n", tempoFinalOperacao, p->id, origem, destino);
    
                int tempoChegada = tempoFinalOperacao + latenciaTransporte;
                escalonador.insereEvento(Evento(tempoChegada, p, destino));
                contador++;
            }       
    
            // Processa os pacotes para rearmazenamento
            while(!paraRearmazenar.estahVazia()) {
                Pacote* p = paraRearmazenar.desempilha();
                //std::cout << evento.chavePrioridade << " ";
                printf("%07d pacote %03d rearmazenado em %03d na secao %03d\n", tempoFinalOperacao, p->id, origem, destino);
                armazemOrigem.secoes[indiceSecao].empilha(p);
            }
    
            // escalona o proximo transporte apenas para esta rota
            escalonador.insereEvento(Evento(relogioAtual + intervaloTransporte, origem, destino));
        }

    }

    return 0;

}
    



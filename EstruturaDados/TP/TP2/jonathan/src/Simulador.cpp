#include "Simulador.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

int ordemId[10000];
int ordemAtual = 0;

Simulador::Simulador() : totalPacotes(0) { // Inicializa totalPacotes
    memset(pacotesPorId, 0, sizeof(pacotesPorId));
}

Simulador::~Simulador() {
    for (int i = 0; i < 10000; i++) {
        if (pacotesPorId[i] != nullptr) {
            delete pacotesPorId[i];
            pacotesPorId[i] = nullptr;
        }
    }
}

void Simulador::lerEntrada(const char* nomeArquivo) {
    ifstream arq(nomeArquivo);
    if (!arq) {
        cerr << "Erro ao abrir o arquivo de entrada\n";
        return;
    }

    arq >> capacidadeTransporte;
    arq >> latenciaTransporte;
    arq >> intervaloTransportes;
    arq >> custoRemocao;
    arq >> numeroArmazens;

    for (int i = 0; i < numeroArmazens; i++)
        for (int j = 0; j < numeroArmazens; j++)
            arq >> grafo[i][j];

    int numPacotes;
    arq >> numPacotes;
    this->totalPacotes = numPacotes; // Armazena o total de pacotes

    long long menorChegada = -1;

    for (int i = 0; i < numPacotes; i++) {
        long long chegada;
        int id, origem, destino;
        string lixo;
        // O ID original do pacote (ex: 1201) é lido, mas o sistema usa um ID sequencial (0, 1, 2...)
        arq >> chegada >> lixo >> id >> lixo >> origem >> lixo >> destino;

        // Atualiza o tempo da primeira chegada
        if (menorChegada == -1 || chegada < menorChegada) {
            menorChegada = chegada;
        }
        
        // Usa o ID sequencial 'i' para o array, mas guarda o ID original (ordemId) para a impressão
        pacotesPorId[i] = new Pacote();
        pacotesPorId[i]->setId(i);
        pacotesPorId[i]->setOrigem(origem);
        pacotesPorId[i]->setDestino(destino);
        pacotesPorId[i]->setTempoUltimoTransporte(chegada);

        calcularRota(*pacotesPorId[i]);

        ordemId[i] = i; // O ID de ordem é o próprio ID sequencial

        Evento e;
        e.tempo = chegada;
        e.tipo = CHEGADA;
        e.pacoteID = i; // Usa o ID sequencial
        e.origem = origem;
        e.destino = destino;
        escalonador.insereEvento(e);
    }

    arq.close();
    
    // Agenda os transportes iniciais com base no tempo da primeira chegada
    if (menorChegada != -1) {
        agendarTransportes(menorChegada);
    }
}

// A função agendarTransportes agora agenda apenas o primeiro ciclo de transportes
void Simulador::agendarTransportes(long long tempoInicial) {
    long long tempoPrimeiroTransporte = tempoInicial + intervaloTransportes;
    for (int i = 0; i < numeroArmazens; i++) {
        for (int j = 0; j < numeroArmazens; j++) {
            if (grafo[i][j]) {
                Evento e;
                e.tempo = tempoPrimeiroTransporte;
                e.tipo = TRANSPORTE;
                e.origem = i;
                e.destino = j;
                e.pacoteID = -1;
                escalonador.insereEvento(e);
            }
        }
    }
}


void Simulador::calcularRota(Pacote& pacote) {
    int tam = 0;
    bfs(pacote.getOrigem(), pacote.getDestino(), pacote.getRota(), tam);
    pacote.setTamanhoRota(tam);
    pacote.setEstado(NAO_POSTADO);
}

void Simulador::bfs(int origem, int destino, int rota[], int& tamanho) {
    int anterior[100], visitado[100] = {0};
    for (int i = 0; i < 100; i++) anterior[i] = -1;

    int fila[100], ini = 0, fim = 0;
    fila[fim++] = origem;
    visitado[origem] = 1;

    while (ini < fim) {
        int atual = fila[ini++];
        if (atual == destino) break;
        for (int i = 0; i < numeroArmazens; i++) {
            if (grafo[atual][i] && !visitado[i]) {
                fila[fim++] = i;
                visitado[i] = 1;
                anterior[i] = atual;
            }
        }
    }

    int caminho[100], idx = 0;
    for (int v = destino; v != -1; v = anterior[v])
        caminho[idx++] = v;

    tamanho = idx;
    for (int i = 0; i < idx; i++)
        rota[i] = caminho[idx - i - 1];
}


void Simulador::rodarSimulacao() {
    int pacotesEntregues = 0;
    // A condição de parada agora é baseada na entrega de todos os pacotes.
    // A verificação 'haEventos' é uma segurança contra loops infinitos.
    while (pacotesEntregues < totalPacotes && escalonador.haEventos()) {
        Evento atual = escalonador.proximoEvento();

        if (atual.tipo == CHEGADA) {
            Pacote* p = pacotesPorId[atual.pacoteID];
            if (!p) continue;

            p->registraTempoTransporte(atual.tempo - p->getTempoUltimoTransporte());

            int armazemDeChegada = atual.origem;

            if (armazemDeChegada == p->getDestino()) {
                p->setEstado(ENTREGUE);
                cout << setw(7) << setfill('0') << atual.tempo
                     << " pacote " << setw(3) << ordemId[p->getId()]
                     << " entregue em " << setw(3) << p->getDestino() << "\n";
                pacotesEntregues++; // Incrementa o contador de pacotes entregues
            } else {
                p->avancaNaRota();
                int proximaSecao = p->getRota()[p->getPosicaoRota()];
                p->setTempoUltimoArmazenamento(atual.tempo);
                p->setEstado(EM_ARMAZEM);
                armazens[armazemDeChegada].armazenaPacote(p, proximaSecao);
                cout << setw(7) << setfill('0') << atual.tempo
                     << " pacote " << setw(3) << ordemId[p->getId()]
                     << " armazenado em " << setw(3) << armazemDeChegada
                     << " na secao " << setw(3) << proximaSecao << "\n";
            }
        } else if (atual.tipo == TRANSPORTE) {
            int origem = atual.origem;
            int destino = atual.destino;

            Pilha buffer, pilhaOrdenada;
            while (!armazens[origem].secaoVazia(destino)) {
                buffer.push(armazens[origem].recuperaPacote(destino));
            }
            while(!buffer.vazia()){
                pilhaOrdenada.push(buffer.pop());
            }

            long long tempoCorrente = atual.tempo;
            Pilha pacotesProntosParaTransporte;

            while(!pilhaOrdenada.vazia()){
                Pacote* p = pilhaOrdenada.pop();
                tempoCorrente += custoRemocao;
                cout << setw(7) << setfill('0') << tempoCorrente
                     << " pacote " << setw(3) << ordemId[p->getId()]
                     << " removido de " << setw(3) << origem
                     << " na secao " << setw(3) << destino << "\n";
                pacotesProntosParaTransporte.push(p);
            }

            int enviados = 0;
            Pilha paraRearmazenar;

            while(!pacotesProntosParaTransporte.vazia()){
                Pacote* p = pacotesProntosParaTransporte.pop();
                if(enviados < capacidadeTransporte){
                    p->registraTempoArmazenado(tempoCorrente - p->getTempoUltimoArmazenamento());
                    p->setTempoUltimoTransporte(tempoCorrente);
                    p->setEstado(EM_TRANSITO);

                    Evento e;
                    e.tempo = tempoCorrente + latenciaTransporte;
                    e.tipo = CHEGADA;
                    e.origem = destino;
                    e.destino = p->getDestino();
                    e.pacoteID = p->getId();
                    escalonador.insereEvento(e);

                    cout << setw(7) << setfill('0') << tempoCorrente
                         << " pacote " << setw(3) << ordemId[p->getId()]
                         << " em transito de " << setw(3) << origem
                         << " para " << setw(3) << destino << "\n";
                    enviados++;
                } else {
                    paraRearmazenar.push(p);
                }
            }

            while(!paraRearmazenar.vazia()){
                Pacote* p = paraRearmazenar.pop();
                p->setEstado(EM_ARMAZEM);
                armazens[origem].armazenaPacote(p, destino);
                cout << setw(7) << setfill('0') << tempoCorrente
                     << " pacote " << setw(3) << ordemId[p->getId()]
                     << " rearmazenado em " << setw(3) << origem
                     << " na secao " << setw(3) << destino << "\n";
            }
            
            // Agenda o próximo evento de transporte para esta rota específica.
            Evento proximoTransporte;
            proximoTransporte.tempo = atual.tempo + intervaloTransportes;
            proximoTransporte.tipo = TRANSPORTE;
            proximoTransporte.origem = origem;
            proximoTransporte.destino = destino;
            proximoTransporte.pacoteID = -1;
            escalonador.insereEvento(proximoTransporte);
        }
    }
}
#include "MinHeap.hpp"
#include <iostream>

MinHeap::MinHeap() {
    tamanho = 0;
}

// *** LÓGICA DE COMPARAÇÃO CORRIGIDA ***
// A lógica de desempate foi ajustada para corresponder à saída esperada.
bool MinHeap::compara(const Evento& a, const Evento& b) {
    // 1. Critério principal: Tempo
    if (a.tempo != b.tempo) return a.tempo < b.tempo;

    // 2. Critério de desempate: Tipo de Evento
    // CHEGADA (0) tem prioridade sobre TRANSPORTE (1)
    if (a.tipo != b.tipo) return a.tipo < b.tipo;

    // 3. Critério de desempate específico para cada tipo de evento
    if (a.tipo == CHEGADA) {
        // Se ambos são eventos de CHEGADA, desempata pelo ID do pacote.
        return a.pacoteID < b.pacoteID;
    } else { // a.tipo == TRANSPORTE
        // Se ambos são eventos de TRANSPORTE, desempata pela origem e depois destino.
        if (a.origem != b.origem) return a.origem < b.origem;
        return a.destino < b.destino;
    }
}

void MinHeap::corrigeSubindo(int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (compara(heap[i], heap[pai])) {
            Evento tmp = heap[i];
            heap[i] = heap[pai];
            heap[pai] = tmp;
            i = pai;
        } else break;
    }
}

void MinHeap::corrigeDescendo(int i) {
    int filho;
    while (2 * i + 1 < tamanho) {
        filho = 2 * i + 1;
        if (filho + 1 < tamanho && compara(heap[filho + 1], heap[filho])) {
            filho++;
        }
        if (compara(heap[filho], heap[i])) {
            Evento tmp = heap[i];
            heap[i] = heap[filho];
            heap[filho] = tmp;
            i = filho;
        } else break;
    }
}

void MinHeap::insere(const Evento& e) {
    if (tamanho >= 100000) {
        std::cerr << "Erro: Capacidade máxima do heap atingida." << std::endl;
        return;
    }
    heap[tamanho] = e;
    corrigeSubindo(tamanho);
    tamanho++;
}

Evento MinHeap::retira() {
    if (vazio()) {
        std::cerr << "Erro: Tentativa de retirar de um heap vazio." << std::endl;
        return {-1, CHEGADA, -1, -1, -1};
    }
    Evento topo = heap[0];
    tamanho--;
    if (tamanho > 0) {
        heap[0] = heap[tamanho];
        corrigeDescendo(0);
    }
    return topo;
}

bool MinHeap::vazio() const {
    return tamanho == 0;
}
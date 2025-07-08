#include "../include/ListaPacotesCliente.hpp"
#include <cstdio>
#include <cstring>

// NoListaPacote e construtores não mudam...
NoListaPacote::NoListaPacote(Evento* evento_) {
    this->evento = evento_;
    this->id_pacote = evento_->id_pacote;
    this->tempo = evento_->tempo;
    // A chave de ordenacao prioriza o tempo.
    // Para desempate, usa o ID do pacote (assumindo que IDs nao sao enormes)
    this->chave = (long long)evento_->tempo * 10000 + (long long)evento_->id_pacote;
    this->prox = nullptr;
}

char* NoListaPacote::getTipoEvento(){
    return this->evento->tipo_evento;
}

ListaPacotesCliente::ListaPacotesCliente() {
    cabeca = nullptr;
}

ListaPacotesCliente::ListaPacotesCliente(Evento* evento_){
    NoListaPacote* novoNo = new NoListaPacote(evento_);
    this->cabeca = novoNo;
}

ListaPacotesCliente::~ListaPacotesCliente() {
    NoListaPacote* atual = cabeca;
    while (atual != nullptr) {
        NoListaPacote* proximo = atual->prox;
        delete atual;
        atual = proximo;
    }
}

void ListaPacotesCliente::insereOrdenado(Evento* evento_) {
    NoListaPacote* novoNo = new NoListaPacote(evento_);
    if (this->cabeca == nullptr || this->cabeca->chave > novoNo->chave) {
        novoNo->prox = cabeca;
        cabeca = novoNo;
        return;
    }
    NoListaPacote* atual = cabeca;
    while (atual->prox != nullptr && atual->prox->chave < novoNo->chave) {
        atual = atual->prox;
    }
    novoNo->prox = atual->prox;
    atual->prox = novoNo;
}

void ListaPacotesCliente::remove(Evento *evento_) {
    NoListaPacote* atual = cabeca;
    NoListaPacote* anterior = nullptr;

    // Procura o no que tem o mesmo ID de pacote e nao eh um evento RG.
    while (atual != nullptr) {
        if (atual->id_pacote == evento_->id_pacote && strcmp(atual->getTipoEvento(), "RG") != 0) {
            // Encontrou o no a ser removido
            break; 
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se 'atual' for nulo, significa que nao encontrou um no para remover
    // (ou o unico evento para aquele pacote era um RG)
    if (atual == nullptr) {
        return;
    }

    // Remove o no atual da lista.
    if (anterior == nullptr) { // O no a ser removido eh a cabeca da lista
        cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    delete atual;
}

void ListaPacotesCliente::atualiza(Evento* evento_) {
    // para cada pacote, manter o evento RG e o evento mais recente.
    // Primeiro, remove-se o "mais recente" anterior.
    this->remove(evento_);
    // Depois, insere-se o novo "mais recente".
    this->insereOrdenado(evento_);
}

void ListaPacotesCliente::imprimeResultados(int tempoConsulta) const {
    NoListaPacote* atual = cabeca;
    int contador = 0;
    while (atual != nullptr) {
        if (atual->tempo <= tempoConsulta) {
            contador++;
        }
        atual = atual->prox;
    }
    printf("%d\n", contador);

    atual = cabeca;
    while (atual != nullptr) {
        if (atual->tempo <= tempoConsulta) {
            atual->evento->imprime();
        }
        atual = atual->prox;
    }
}
#include "../include/ListaPacotesCliente.hpp"
#include <cstdio>
#include <cstring>

NoListaPacote::NoListaPacote(Evento* evento_) {
    this->evento = evento_;
    this->id_pacote = evento_->id_pacote;
    this->tempo = evento_->tempo;
    this->chave = id_pacote + 100000 * tempo;
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
    while (atual->prox != nullptr && atual->chave < novoNo->chave) {
        atual = atual->prox;
    }
    novoNo->prox = atual->prox;
    atual->prox = novoNo;
}

void ListaPacotesCliente::remove(Evento *evento_) {
    NoListaPacote* atual = cabeca;
    NoListaPacote* anterior = nullptr;
    char tipo_evento_[3];
    strncpy(tipo_evento_, atual->getTipoEvento(), 2);

    while (atual != nullptr && (atual->id_pacote != evento_->id_pacote || strcmp(tipo_evento_, "RG") == 0)){
        anterior = atual;
        atual = atual->prox;
        if(atual != nullptr) strncpy(tipo_evento_, atual->getTipoEvento(), 2);
    }
    if (atual == nullptr) return;

    if (anterior == nullptr) {
        cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    delete atual;
}

void ListaPacotesCliente::atualiza(Evento* evento_) {
    this->remove(evento_);
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
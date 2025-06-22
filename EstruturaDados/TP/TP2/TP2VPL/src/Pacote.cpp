#include "../include/Pacote.hpp"
#include <iostream>

void Pacote::Inicializar(int tempo, int _id, int _armazemOrigem,
                         int _armazemDestino) {
  this->tempoAtual = tempo;
  this->id = _id;
  this->armazemOrigem = _armazemOrigem;
  this->armazemDestino = _armazemDestino;
  this->armazemAtual = _armazemOrigem;
  this->estadoPacote = naoPostado;
  // this->estatisticas = new Estatistica(); // Cria uma nova estatística para o
  // pacote
  this->rota = nullptr;
  this->tamanhoRota = -1;
  //this->indiceRotaAtual = 0;
}

Pacote::~Pacote() {
  if (rota != nullptr) {
    delete[] rota;
  }
}

void Pacote::imprimePacote() {
  std::cout << "id: " << this->id << std::endl;
  std::cout << "armazemOrigem: " << this->armazemOrigem << std::endl;
  std::cout << "armazemDestino: " << this->armazemDestino << std::endl;
  std::cout << "tamanhoRota: " << this->tamanhoRota << std::endl;
  std::cout << "tempoAtual: " << this->tempoAtual << std::endl;
}

int Pacote::getProximoDestinoNaRota() {
  for (int i = 0; i < tamanhoRota; i++) {
    if (rota[i] == armazemAtual)
      return rota[i + 1];
  }
  return -1; // acontece quando o armazem atual ja eh o ultimo armazem da rota
             // do pacote
}

int obterTempoPrimeiroPacotePostado(Pacote *pacote, int qtdePacotes) {
  int tempo = pacote[0].tempoAtual;

  for (int i = 1; i < qtdePacotes; i++) {
    if (tempo > pacote[i].tempoAtual)
      tempo = pacote[i].tempoAtual;
  }

  return tempo;
};


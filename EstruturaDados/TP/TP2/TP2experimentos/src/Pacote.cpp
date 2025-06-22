#include "../include/Pacote.hpp"
#include <iostream>
#include <cstdio>


void Pacote::Inicializar(int tempo, int _id, int _armazemOrigem, int _armazemDestino) {
  this->tempoAtual = tempo;
  this->id = _id;
  this->armazemOrigem = _armazemOrigem;
  this->armazemDestino = _armazemDestino;
  this->armazemAtual = _armazemOrigem;
  this->estadoPacote = naoPostado;
  this->estatisticas.tempoPostagem = tempo;
  this->estatisticas.tempoUltimaMudancaDeEstado = tempo;
  this->rota = nullptr;
  this->tamanhoRota = -1;
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

void Pacote::mudarEstado(int novoEstado, double tempoEvento) {
  // Primeiro, registra a duracao do estado em que o pacote ESTAVA
  this->estatisticas.registrarMudanca(this->estadoPacote, tempoEvento);
  // Depois, atualiza o pacote para o NOVO estado
  this->estadoPacote = novoEstado;
}

int obterTempoPrimeiroPacotePostado(Pacote *pacote, int qtdePacotes) {
  int tempo = pacote[0].tempoAtual;

  for (int i = 1; i < qtdePacotes; i++) {
    if (tempo > pacote[i].tempoAtual)
      tempo = pacote[i].tempoAtual;
  }

  return tempo;
};

// Construtor: zera todas as variaveis
Estatistica::Estatistica() {
    tempoTotalArmazenado = 0.0;
    tempoTotalRearmazenado = 0.0;
    tempoTotalEmTransito = 0.0;
    tempoPostagem = 0.0;
    tempoUltimaMudancaDeEstado = 0.0;
}

// O coracao da logica de estatisticas
void Estatistica::registrarMudanca(int estadoAntigo, double tempoDoEvento) {
    // Calcula quanto tempo se passou desde a ultima mudanca de estado
    double duracao = tempoDoEvento - this->tempoUltimaMudancaDeEstado;

    // Acumula essa duracao na variavel correta, com base no estado em que o pacote estava
    if (estadoAntigo == armazenado) {
        this->tempoTotalArmazenado += duracao;
    } else if (estadoAntigo == rearmazenado) {
        this->tempoTotalRearmazenado += duracao;
    } else if (estadoAntigo == alocadoTransporte) {
        // 'alocadoTransporte' e o estado que representa "em transito"
        this->tempoTotalEmTransito += duracao;
    }
    // Para outros estados como 'naoPostado' ou 'entregue', nao acumulamos duracao.

    // Atualiza o tempo da ultima mudanca para o tempo atual
    this->tempoUltimaMudancaDeEstado = tempoDoEvento;
}

void Estatistica::imprimir(int idPacote, double tempoEntrega) {
    double tempoTotalJornada = tempoEntrega - this->tempoPostagem;

    printf("%03d;", idPacote);
    printf("%.2f;", tempoTotalJornada);
    printf("%.2f;", tempoTotalEmTransito);
    printf("%.2f;", tempoTotalArmazenado);
    printf("%.2f;", tempoTotalRearmazenado);
    printf("\n");
}

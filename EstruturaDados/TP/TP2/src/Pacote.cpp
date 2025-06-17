#include "Pacote.hpp"

void Pacote::Inicializar(int tempo, int _id, int _armazemOrigem, int _armazemDestino) {
    this->tempoAtual = tempo;
    this->id = _id;
    this->armazemOrigem = _armazemOrigem;
    this->armazemDestino = _armazemDestino;
    this->estadoPacote = naoPostado; // Estado inicial do pacote
    //this->estatisticas = new Estatistica(); // Cria uma nova estatística para o pacote
    this->rota = nullptr;
    this->tamanhoRota = 0;
    this->proximoDestino = 1;
}

Pacote::~Pacote() {    
    if (rota != nullptr) {
        delete[] rota;
    }
}

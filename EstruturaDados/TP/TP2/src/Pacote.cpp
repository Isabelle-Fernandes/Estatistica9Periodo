#include "Pacote.hpp"

void Pacote::Inicializar(int tempo, char * _remetente, char * _destinatario, int _tipo, int _armazemOrigem, int _armazemDestino) {
    this->tempoAtual = tempo;
    this->nomeRemetente = _remetente;
    this->nomeDestinatario = _destinatario;
    this->tipo = _tipo;
    this->armazemOrigem = _armazemOrigem;
    this->armazemDestino = _armazemDestino;
    this->estadoPacote = naoPostado; // Estado inicial do pacote
    //this->estatisticas = new Estatistica(); // Cria uma nova estatística para o pacote
    this->rota = nullptr;
    this->tamanhoRota = 0;
    this->proximoDestino = 1;
}

Pacote::~Pacote() {
    delete[] nomeRemetente;
    delete[] nomeDestinatario;
    
    if (rota != nullptr) {
        delete[] rota;
    }
}

char* lerPalavraDinamica(std::ifstream& arquivo) {
    // Cria um buffer temporario na stack.
    // 256 caracteres e um tamanho seguro para nomes de remetentes e destinatarios.
    char buffer_temporario[256];

    // 'width(256)' garante que a leitura nao excedera o tamanho do buffer,
    // prevenindo buffer overflows.
    arquivo.width(256);
    arquivo >> buffer_temporario;

    // Verifica se a leitura falhou (ex: fim de arquivo)
    if (arquivo.fail()) {
        return nullptr;
    }

    // Mede o tamanho exato da palavra lida.
    int tamanho = strlen(buffer_temporario);

    // Aloca o buffer final no heap com o tamanho exato (+1 para o '\0').
    char* buffer_final = new char[tamanho + 1];

    // Copia a string do buffer temporario para o final.
    strcpy(buffer_final, buffer_temporario);

    // Retorna o ponteiro para o buffer final, perfeitamente ajustado.
    return buffer_final;
}
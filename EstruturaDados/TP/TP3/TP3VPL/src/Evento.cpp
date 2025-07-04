 #include "../include/Evento.hpp"
 #include <cstring>
 #include <cstdio> 
 
 // evento RG
 void Evento::criarEventoRG(int tempo, const char* tipo, int id, const char* rem, const char* dest, int orig, int dest_final) {
    this->tempo = tempo;
    this->id_pacote = id;
    this->armazem_origem = orig;
    this->armazem_destino = dest_final;
    strcpy(this->tipo_evento, tipo); // CORRECAO: Usa strcpy para copiar

    // Aloca memoria e faz uma copia profunda das strings
    this->cliente_remetente = new char[strlen(rem) + 1];
    strcpy(this->cliente_remetente, rem);

    this->cliente_destinatario = new char[strlen(dest) + 1];
    strcpy(this->cliente_destinatario, dest);

    this->secao_destino = -1;
}

void Evento::criarEventoSimples(int tempo, const char* tipo, int id, int armazem, int secao) {
    this->tempo = tempo;
    this->id_pacote = id;
    this->armazem_destino = armazem; // Para AR e RM, este e o armazem onde a acao ocorre
    this->secao_destino = secao;     // E esta e a secao
    strcpy(this->tipo_evento, tipo);

    this->cliente_remetente = nullptr;
    this->cliente_destinatario = nullptr;
    this->armazem_origem = -1;
 
}

// Implementacao para eventos do tipo TR
void Evento::criarEventoTransporte(int tempo, const char* tipo, int id, int armazemOrigem, int armazemDestino) {
    this->tempo = tempo;
    this->id_pacote = id;
    this->armazem_origem = armazemOrigem;
    this->armazem_destino = armazemDestino;
    strcpy(this->tipo_evento, tipo);

    this->cliente_remetente = nullptr;
    this->cliente_destinatario = nullptr;
    this->secao_destino = -1;
}

// Implementacao para eventos do tipo EN
void Evento::criarEventoEntrega(int tempo, const char* tipo, int id, int armazemEntrega) {
    this->tempo = tempo;
    this->id_pacote = id;
    this->armazem_destino = armazemEntrega; // O armazem onde foi entregue
    strcpy(this->tipo_evento, tipo);

    this->cliente_remetente = nullptr;
    this->cliente_destinatario = nullptr;
    this->armazem_origem = -1;
    this->secao_destino = -1;
}

Evento::Evento(){
    this->tempo = -1;
    this->cliente_remetente = nullptr;
    this->cliente_destinatario = nullptr;
    this->id_pacote = -1;
    strcpy(this->tipo_evento, "XX"); // tipo evento pacote RG, AR, RM... etc
    this->armazem_origem = -1;
    this->armazem_destino = -1;
    this->secao_destino = -1;
}

Evento::~Evento(){
    delete[] cliente_remetente;
    delete[] cliente_destinatario;
}

void Evento::imprime() const {
    printf("%07d EV %s %03d", this->tempo, this->tipo_evento, this->id_pacote);

    if (strcmp(this->tipo_evento, "RG") == 0) {
        printf(" %s %s %03d %03d\n", 
            this->cliente_remetente, this->cliente_destinatario, 
            this->armazem_origem, this->armazem_destino);
    
    } else if (strcmp(this->tipo_evento, "TR") == 0) {
        printf(" %03d %03d\n", this->armazem_origem, this->armazem_destino);
    
    } else if (strcmp(this->tipo_evento, "AR") == 0 || strcmp(this->tipo_evento, "RM") == 0 || strcmp(this->tipo_evento, "UR") == 0) {
        printf(" %03d %03d\n", this->armazem_destino, this->secao_destino);
    
    } else if (strcmp(this->tipo_evento, "EN") == 0) {
        printf(" %03d\n", this->armazem_destino);
    
    } else {
        // tipo desconhecido
    }

}

// Construtor de Copia
Evento::Evento(const Evento& outro) {
    // Inicializa ponteiros para evitar problemas
    this->cliente_remetente = nullptr;
    this->cliente_destinatario = nullptr;
    // Chama o operador de atribuicao para fazer o trabalho pesado da copia
    *this = outro;
}

// Operador de Atribuicao: Usado para sobrescrever um evento EXISTENTE com outro.
Evento& Evento::operator=(const Evento& outro) {
    // Verifica se nao e uma auto-atribuicao (ex: evento1 = evento1)
    if (this == &outro) {
        return *this;
    }

    // Libera a memoria antiga que este objeto possa ter, para evitar leaks
    delete[] this->cliente_remetente;
    delete[] this->cliente_destinatario;

    // Copia todos os dados nao-ponteiros
    this->tempo = outro.tempo;
    this->id_pacote = outro.id_pacote;
    strcpy(this->tipo_evento, outro.tipo_evento);
    this->armazem_origem = outro.armazem_origem;
    this->armazem_destino = outro.armazem_destino;
    this->secao_destino = outro.secao_destino;

    // Aloca NOVA memoria e copia as strings (copia profunda)
    if (outro.cliente_remetente != nullptr) {
        this->cliente_remetente = new char[strlen(outro.cliente_remetente) + 1];
        strcpy(this->cliente_remetente, outro.cliente_remetente);
    } else {
        this->cliente_remetente = nullptr;
    }

    if (outro.cliente_destinatario != nullptr) {
        this->cliente_destinatario = new char[strlen(outro.cliente_destinatario) + 1];
        strcpy(this->cliente_destinatario, outro.cliente_destinatario);
    } else {
        this->cliente_destinatario = nullptr;
    }
    
    return *this; // Retorna o proprio objeto modificado
}
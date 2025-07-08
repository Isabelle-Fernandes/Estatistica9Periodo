#ifndef EVENTO_HPP
#define EVENTO_HPP 

class Evento {
public:
    int tempo;
    char* cliente_remetente;
    char* cliente_destinatario;
    int id_pacote;
    char tipo_evento[3]; // tipo evento pacote RG, AR, RM... etc
    int armazem_origem;
    int armazem_destino;
    int secao_destino;
    
    Evento();
    ~Evento();

    Evento(const Evento& outro);                // 1. Construtor de Copia
    Evento& operator=(const Evento& outro);

    //eventos AR, RM, UR
    void criarEventoSimples(int tempo, const char* tipo, int id, int armazem, int secao);
    
    //evento RG
    void criarEventoRG(int tempo, const char* tipo, int id, const char* rem, const char* dest, int orig, int dest_final);

    //evento TR
    void criarEventoTransporte(int tempo, const char* tipo, int id, int armazemOrigem, int armazemDestino);
    
    //evento EN
    void criarEventoEntrega(int tempo, const char* tipo, int id, int armazemEntrega);
    
    void imprime() const; 

};

#endif
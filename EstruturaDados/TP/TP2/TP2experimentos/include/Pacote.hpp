#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <cstring>


// aqui estao os estados do pacote
#define naoPostado 1
#define chegadaEscalonadaArmazem 2
#define armazenado 3
#define alocadoTransporte 4
#define entregue 5
#define rearmazenado 6

class Estatistica {
public:
    // Variaveis para acumular os tempos
    double tempoTotalArmazenado;
    double tempoTotalRearmazenado;
    double tempoTotalEmTransito;

    // Variaveis de controle
    double tempoPostagem;
    double tempoUltimaMudancaDeEstado;

    // Construtor
    Estatistica();

    // Metodo principal para atualizar as estatisticas
    // Ele calcula a duracao do estado antigo e a acumula no local correto.
    void registrarMudanca(int estadoAntigo, double tempoDoEvento);

    // Metodo para imprimir um relatorio final
    void imprimir(int idPacote, double tempoEntrega);
};

class Pacote {
    public:
        ~Pacote();
        void Inicializar(int tempo, int _id, int _armazemOrigem, int _armazemDestino);
        int tempoAtual;
        int id;
        int armazemOrigem;
        int armazemDestino;
        int armazemAtual;
        int estadoPacote;
        Estatistica estatisticas;
        int* rota;
        int tamanhoRota;
        void mudarEstado(int novoEstado, double tempoEvento);
        int getProximoDestinoNaRota();
        void imprimePacote();
    };
        
int obterTempoPrimeiroPacotePostado(Pacote* pacote, int qtdePacotes);

#endif
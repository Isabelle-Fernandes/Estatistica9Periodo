#ifndef EVENTO_HPP
#define EVENTO_HPP

#define CHEGADA 1
#define TRANSPORTE 2

struct Evento {
    long long tempo;
    int pacoteID;
    int origem;
    int destino;
    int tipo;

    Evento() {
        tempo = 0;
        pacoteID = 0;
        origem = 0;
        destino = 0;
        tipo = CHEGADA;
    }

  
    Evento(long long t, int pid, int o, int d, int tp) {
        tempo = t;
        pacoteID = pid;
        origem = o;
        destino = d;
        tipo = tp;
    }
};

#endif

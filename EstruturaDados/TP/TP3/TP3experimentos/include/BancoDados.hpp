#ifndef BANCO_HPP
#define BANCO_HPP 

#include "Evento.hpp"

class BancoDados {
    public:
        Evento** eventos; 
        int capacidade; 
        int tamanho; 
        
        BancoDados();
        ~BancoDados();
        void addEvento(const Evento& evento); 
        void redimensionar();
    };
   
#endif

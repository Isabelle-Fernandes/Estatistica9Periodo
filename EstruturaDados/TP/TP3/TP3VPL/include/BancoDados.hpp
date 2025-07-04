#ifndef BANCO_HPP
#define BANCO_HPP 

#include "Evento.hpp"

class BancoDados {
    public:
        Evento* eventos;
        int capacidade = 100; 
        int tamanho; 
        BancoDados();
        ~BancoDados();
        void addEvento(const Evento &evento); 
        void redimensionar(); // redimensiona o tamanho do vetor Eventos
    
};
   
#endif

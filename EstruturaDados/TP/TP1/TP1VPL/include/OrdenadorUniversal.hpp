#ifndef ORDENADORUNIVERSAL_H
#define ORDENADORUNIVERSAL_H
#include "Vetor.hpp"
#include "QuicksortIns.hpp"

class OrdenadorUniversal {
public:
    OrdenadorUniversal();   
    Insertion insertion;
    QuicksortIns quicksortIns;
    
    void Ordena(Vetor &vetor, int tam, int minTamParticao, int limiarQuebras, int numQuebras);

};

#endif

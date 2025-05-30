#include "Insertion.hpp"

Insertion::Insertion() {}

Insertion::~Insertion() {}

void Insertion::insertionSort(Vetor &vetor, int esq, int dir) {
    vetor.inccalls(1);
    for(int i = esq+1; i <= dir; i++){  
        Item aux = vetor.itens[i];
        vetor.inccmp(1);
        int j = i - 1;
        vetor.incmov(1);
      
        while((j >= esq) && (aux < vetor.itens[j])){
            vetor.itens[j + 1] = vetor.itens[j];
            vetor.incmov(1);
            j = j - 1;
            vetor.inccmp(1);    
        }
        vetor.itens[j + 1] = aux;
        vetor.incmov(1);
     
    }
    return;
}


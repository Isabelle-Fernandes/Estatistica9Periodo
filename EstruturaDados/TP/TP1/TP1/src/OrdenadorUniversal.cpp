#include "OrdenadorUniversal.hpp"

OrdenadorUniversal::OrdenadorUniversal() {}

void OrdenadorUniversal::Ordena(Vetor &vetor, int tam, int minTamParticao, int limiarQuebras, int numeroQuebras){
    int dir = tam - 1;
    int esq = 0;

   if (numeroQuebras < limiarQuebras){
        insertion.insertionSort(vetor, esq, dir);
    } else {
        if (tam > minTamParticao){
            quicksortIns.quickSort3Ins(vetor, esq, dir, minTamParticao);
        } else {
            insertion.insertionSort(vetor, esq, dir);
        }
    }
};


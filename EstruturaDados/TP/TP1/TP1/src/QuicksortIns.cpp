#include "QuicksortIns.hpp"

void QuicksortIns::swap(int *xp, int *yp, Vetor &_vetor) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    _vetor.incmov(3);
}

QuicksortIns::QuicksortIns() {}

QuicksortIns::~QuicksortIns() {}

int QuicksortIns::median(int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

void QuicksortIns::partition3(Vetor &vetor, int esq, int dir, int *i, int *j) {
    vetor.inccalls(1);
    *i = esq;
    *j = dir;
    
    int pivo = median(vetor.vetor[(*i + *j)/2], vetor.vetor[*i], vetor.vetor[*j]);
  
    while (*i <= *j) {
        while(vetor.vetor[*i] < pivo){
            (*i)++;
            vetor.inccmp(1);
        }
        while(vetor.vetor[*j] > pivo){
            (*j)--;
            vetor.inccmp(1);
        }     

        if(*i <= *j){
            swap(&vetor.vetor[*i], &vetor.vetor[*j], vetor);
            (*i)++; 
            (*j)--;
        }  
        vetor.inccmp(2); 
    }
    return;
};

void QuicksortIns::quickSort3Ins(Vetor &vetor, int esq, int dir, int minTamParticao) {
    vetor.inccalls(1);
    int i;
    int j;
    partition3(vetor, esq, dir, &i, &j);
    
    if(esq < j){
        if((j - esq + 1) > minTamParticao) {
            quickSort3Ins(vetor, esq, j, minTamParticao);
        } else insertion.insertionSort(vetor, esq, j);
    }

    if(dir > i){
        if((dir - i + 1) > minTamParticao){
        quickSort3Ins(vetor, i, dir, minTamParticao);
        } else insertion.insertionSort(vetor, i, dir);
    }
    return;
}
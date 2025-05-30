#include "QuicksortIns.hpp"

void QuicksortIns::swap(Item *xp, Item *yp, Vetor &_vetor) {
    Item temp = *xp;
    *xp = *yp;
    *yp = temp;
    _vetor.incmov(3);
}

QuicksortIns::QuicksortIns() {}

QuicksortIns::~QuicksortIns() {}

int QuicksortIns::median(Vetor &vetor, int a, int b, int c) {
    Item &A = vetor.itens[a];
    Item &B = vetor.itens[b];
    Item &C = vetor.itens[c];

    if ((A < B && B < C) || (C < B && B < A)) return b;
    if ((B < A && A < C) || (C < A && A < B)) return a;
    return c;
}

void QuicksortIns::partition3(Vetor &vetor, int esq, int dir, int *i, int *j) {
    vetor.inccalls(1);
    *i = esq;
    *j = dir;
    
    int m = median(vetor, (*i + *j) / 2, *i, *j);
    Item pivo = vetor.itens[m];
  
    while (*i <= *j) {
        while(vetor.itens[*i] < pivo){
            (*i)++;
            vetor.inccmp(1);
        }
        while(vetor.itens[*j] > pivo){
            (*j)--;
            vetor.inccmp(1);
        }     

        if(*i <= *j){
            swap(&vetor.itens[*i], &vetor.itens[*j], vetor);
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
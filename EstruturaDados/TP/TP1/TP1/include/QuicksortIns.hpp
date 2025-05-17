#ifndef QUICKSORTINS_H
#define QUICKSORTINS_H

#include "Insertion.hpp"
#include "Vetor.hpp"


class QuicksortIns {
public:
    QuicksortIns();
    ~QuicksortIns();

    Insertion insertion;

    int median(int a, int b, int c);
    void swap(int *xp, int *yp, Vetor &v);
    void partition3(Vetor &vetor, int esq, int dir, int *i, int *j);
    void quickSort3Ins(Vetor &vetor, int esq, int dir, int minTamParticao);
};


#endif 
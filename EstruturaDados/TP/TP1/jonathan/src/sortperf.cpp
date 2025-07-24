#include "../include/sortperf.hpp"
#include <cstdlib> 

void resetcounter(sortperf_t *s) {
    s->cmp = 0;
    s->move = 0;
    s->calls = 0;
}

void inccmp(sortperf_t *s, int num) {
    s->cmp += num;
}

void incmove(sortperf_t *s, int num) {
    s->move += num;
}

void inccalls(sortperf_t *s, int num) {
    s->calls += num;
}

long double getCost(sortperf_t *s, long double a, long double b, long double c) {
    return a * s->cmp + b * s->move + c * s->calls;
}

void shuffleVector(int *vet, int size, int numShuffle, int seed){
    srand48(seed);
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++) {
        /* Gera dois índices distintos no intervalo [0..size-1] */
        while (p1 == p2) {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        /* Realiza a troca para introduzir uma quebra */
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }
}
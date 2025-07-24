// Arquivo: ordenador.cpp (Versão Final para o VPL)

#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/ordenador.hpp"
#include "../include/sortperf.hpp"

using namespace std;

// Funções base e de ordenação com contagem correta (sem alterações)
// ... (swap, contaQuebras, insertionSort, median) ...
void swap(int *xp, int *yp, sortperf_t *s) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s, 3);
}

int contaQuebras(int *vet, int tam) {
    int quebras = 0;
    for (int i = 1; i < tam; ++i) {
        if (vet[i] < vet[i - 1]) ++quebras;
    }
    return quebras;
}

void insertionSort(int v[], int l, int r, sortperf_t *s) {
    inccalls(s, 1);
    int key, j;
    for (int i = l + 1; i <= r; i++) {
        key = v[i]; incmove(s, 1);
        j = i - 1; inccmp(s, 1);
        while (j >= l && v[j] > key) {
            v[j + 1] = v[j]; incmove(s, 1);
            j--; inccmp(s, 1);
        }
        v[j + 1] = key; incmove(s, 1);
    }
}

int median(int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;
    if ((a <= c) && (c <= b)) return c;
    if ((b <= a) && (a <= c)) return a;
    if ((b <= c) && (c <= a)) return c;
    if ((c <= a) && (a <= b)) return a;
    return b;
}

void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    inccalls(s, 1);
    *i = l; *j = r;
    int pivo = median(A[*i], A[(*i + *j) / 2], A[*j]);
    while (*i <= *j) {
        while(A[*i] < pivo) { (*i)++; inccmp(s, 1); }
        while(A[*j] > pivo) { (*j)--; inccmp(s, 1); }
        if(*i <= *j) {
            swap(&A[*i], &A[*j], s);
            (*i)++; (*j)--;
        }
        inccmp(s, 2);
    }
}

void quickSort3Ins(int *A, int l, int r, int limit, sortperf_t *s) {
    inccalls(s, 1);
    int i = l, j = r;
    partition3(A, l, r, &i, &j, s);
    if (j > l) {
        if ((j - l + 1) > limit) quickSort3Ins(A, l, j, limit, s);
        else insertionSort(A, l, j, s);
    }
    if (i < r) {
        if ((r - i + 1) > limit) quickSort3Ins(A, i, r, limit, s);
        else insertionSort(A, i, r, s);
    }
}

void ordenadorUniversal(int *vet, int tam, int minPart, int limQuebras, sortperf_t *perf) {
    resetcounter(perf);
    int quebras = contaQuebras(vet, tam);
    if (quebras <= limQuebras)
        insertionSort(vet, 0, tam - 1, perf);
    else
        quickSort3Ins(vet, 0, tam - 1, minPart, perf);
}

// Lógica de busca original, porém tornada segura
// -------------------------------------------------------------

// Sua função original de refinar a busca
void calculaNovaFaixa(int limParticao, int *mpsValores, int &minMPS, int &maxMPS, int &passoMPS, int numTestes) {
    int newMin, newMax;
    // Lógica original, mas protegida contra poucos testes
    if (limParticao == 0) {
        newMin = 0;
        newMax = (numTestes > 2) ? 2 : numTestes - 1;
    } else if (limParticao == numTestes - 1) {
        newMin = (numTestes > 2) ? numTestes - 3 : 0;
        newMax = numTestes - 1;
    } else {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }

    minMPS = mpsValores[newMin];
    maxMPS = mpsValores[newMax];
    passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS = 1;
}

// Sua função determinaLimiarParticao com o diff original, mas seguro
int determinaLimiarParticao(int *vetOriginal, int tam, double limiarCusto, double a, double b, double c) {
    int minMPS = 2, maxMPS = tam;
    if(maxMPS <= minMPS) maxMPS = minMPS + 1;
    int passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS = 1;

    int melhorParticao_idx = 0;
    double custo[20];
    int mpsValores[20];
    int iterador = 0;

    while (iterador < 10 && passoMPS > 0) {
        int numMPS = 0;
        double menorCusto = 1e9;
        cout << "iter " << iterador++ << endl;

        for (int t = minMPS; t <= maxMPS && numMPS < 20; t += passoMPS) {
            int* copia = new int[tam];
            for (int i = 0; i < tam; ++i) copia[i] = vetOriginal[i];
            sortperf_t perf;
            resetcounter(&perf);
            quickSort3Ins(copia, 0, tam - 1, t, &perf);

            custo[numMPS] = getCost(&perf, a, b, c);
            mpsValores[numMPS] = t;

            cout << "mps " << t << " cost " << fixed << setprecision(9) << custo[numMPS] << " cmp " << perf.cmp << " move " << perf.move << " calls " << perf.calls << endl;

            if (custo[numMPS] < menorCusto) {
                menorCusto = custo[numMPS];
                melhorParticao_idx = numMPS;
            }
            delete[] copia;
            numMPS++;
        }

        // LÓGICA DE DIFF ORIGINAL, MAS SEGURA
        float diffCusto = 0;
        if (numMPS >= 3) { // Só executa a lógica se for seguro
            if (melhorParticao_idx == 0) {
                diffCusto = fabsl(custo[melhorParticao_idx] - custo[2]);
            } else if (melhorParticao_idx == numMPS - 1) {
                diffCusto = fabsl(custo[melhorParticao_idx] - custo[numMPS - 2]);
            } else {
                diffCusto = fabsl(custo[melhorParticao_idx - 1] - custo[melhorParticao_idx + 1]);
            }
        } else if (numMPS == 2) {
             diffCusto = fabsl(custo[0] - custo[1]);
        }

        cout << "nummps " << numMPS << " limParticao " << mpsValores[melhorParticao_idx] << " mpsdiff " << fixed << setprecision(6) << diffCusto << endl << endl;

        if (diffCusto <= limiarCusto || numMPS < 5)
            return mpsValores[melhorParticao_idx];

        calculaNovaFaixa(melhorParticao_idx, mpsValores, minMPS, maxMPS, passoMPS, numMPS);
    }
    return mpsValores[melhorParticao_idx];
}


// Sua função determinaLimiarQuebras com o diff original, mas seguro
int determinaLimiarQuebras(double limiarCusto, int *vetOriginal, int tam, int limPart, double a, double b, double c, int seed) {
    int minLQ = 1, maxLQ = tam / 2;
    if(maxLQ <= minLQ) maxLQ = minLQ + 1;
    int passoLQ = (maxLQ - minLQ) / 5;
    if (passoLQ == 0) passoLQ = 1;

    int melhorLQ_idx = 0;
    double custo_diff[20];
    double custosIN[20];
    int lqValores[20];
    int iter = 0;

    while (iter < 10 && passoLQ > 0) {
        double menorCusto = 1e9;
        cout << "iter " << iter++ << endl;
        int numLQ = 0;
        
        for (int t = minLQ; t <= maxLQ && numLQ < 20; t += passoLQ) {
            int* copiaQS = new int[tam];
            int* copiaIN = new int[tam];
            for (int i = 0; i < tam; ++i) {
                copiaQS[i] = vetOriginal[i];
                copiaIN[i] = vetOriginal[i];
            }
            sortperf_t perfQ, perfI;
            resetcounter(&perfQ);
            resetcounter(&perfI);

            shuffleVector(copiaQS, tam, t, seed);
            shuffleVector(copiaIN, tam, t, seed);

            quickSort3Ins(copiaQS, 0, tam - 1, limPart, &perfQ);
            insertionSort(copiaIN, 0, tam - 1, &perfI);

            double custoQS = getCost(&perfQ, a, b, c);
            custosIN[numLQ] = getCost(&perfI, a, b, c);
            custo_diff[numLQ] = fabsl(custoQS - custosIN[numLQ]);
            lqValores[numLQ] = t;

            cout << "qs lq " << t << " cost " << fixed << setprecision(9) << custoQS << " cmp " << perfQ.cmp << " move " << perfQ.move << " calls " << perfQ.calls << endl;
            cout << "in lq " << t << " cost " << fixed << setprecision(9) << custosIN[numLQ] << " cmp " << perfI.cmp << " move " << perfI.move << " calls " << perfI.calls << endl;

            if (custo_diff[numLQ] < menorCusto) {
                menorCusto = custo_diff[numLQ];
                melhorLQ_idx = numLQ;
            }
            delete[] copiaQS;
            delete[] copiaIN;
            numLQ++;
        }

        // LÓGICA DE DIFF ORIGINAL, MAS SEGURA
        float diffCusto = 0;
        if (numLQ >= 3) { // Só executa a lógica se for seguro
            if (melhorLQ_idx == 0) {
                diffCusto = fabsl(custosIN[melhorLQ_idx] - custosIN[2]);
            } else if (melhorLQ_idx == numLQ - 1) {
                diffCusto = fabsl(custosIN[melhorLQ_idx] - custosIN[numLQ - 2]);
            } else {
                diffCusto = fabsl(custosIN[melhorLQ_idx - 1] - custosIN[melhorLQ_idx + 1]);
            }
        } else if (numLQ == 2) {
             diffCusto = fabsl(custosIN[0] - custosIN[1]);
        }


        cout << "numlq " << numLQ << " limQuebras " << lqValores[melhorLQ_idx] << " lqdiff " << fixed << setprecision(6) << diffCusto << endl << endl;

        if (diffCusto <= limiarCusto || numLQ < 5)
            return lqValores[melhorLQ_idx];
        
        calculaNovaFaixa(melhorLQ_idx, lqValores, minLQ, maxLQ, passoLQ, numLQ);
    }

    return lqValores[melhorLQ_idx];
}
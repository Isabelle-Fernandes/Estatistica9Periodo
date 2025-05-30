#include "heap.hpp"
#include <iostream>

Heap::Heap(int tamanho){
    aresta = new Aresta[tamanho];
    tamAtual = 0;
}

int Heap::GetAncestral(int i){
    return (i-1)/2;
}

int Heap::GetSucessorEsq(int i){
    return 2 * i + 1;
}

int Heap::GetSucessorDir(int i){
    return 2 * i + 2;
}

int Heap::GetMenorSucessor(int i){
    int esq = GetSucessorEsq(i);
    int dir = GetSucessorDir(i);


    if (esq >= tamAtual) return esq;
    if (dir >= tamAtual) return esq;
    
    Aresta aresta_dir = this->aresta[dir];
    Aresta aresta_esq = this->aresta[esq];

    if (aresta_dir < aresta_esq) return dir;
    
    return esq;
}

void Heap::Insere(Aresta x){
    aresta[tamAtual] = x;
    int i = tamAtual;
    int p = GetAncestral(i);
    while(aresta[i] < aresta[p]){
        Aresta temp = aresta[i];
        aresta[i] = aresta[p];
        aresta[p] = temp;    
        i = p;
        p = GetAncestral(i);
    }
    tamAtual++;
}


Aresta Heap::Remove(){
    Aresta x = aresta[0];
    aresta[0] = aresta[tamAtual-1];
    tamAtual--;
    int i = 0;
    int s = GetMenorSucessor(i);
    while (aresta[i] > aresta[s] && s < tamAtual){
        Aresta temp = aresta[s];
        aresta[s] = aresta[i];
        aresta[i] = temp;
        i = s;
        s = GetMenorSucessor(i);
    }
    return x;
}

void Heap::Conserta(){
    int i = 0;
    while (i < tamAtual){
        int s = GetMenorSucessor(i);
        if (s >= tamAtual) break;
        if (aresta[i] < aresta[s]){
            Aresta temp = aresta[i];
            aresta[i] = aresta[s];
            aresta[s] = temp;
            i = s;
        } else {
            break;
        }
    }
}

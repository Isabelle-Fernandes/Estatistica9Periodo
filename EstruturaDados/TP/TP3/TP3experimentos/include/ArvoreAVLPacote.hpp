#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

#include "Fila.hpp"

class No {
public:
    int id_pacote;             
    Fila<int> indices_eventos; // array dinamico que guarda os indices (entende-se como a posicao do arrya Eventos) do pacote
    int altura;
    long chave;
    No *esquerda;
    No *direita;

    No(int id);
};

class ArvoreAVLPacote {
private:
    No* raiz;

    int altura(No* no);
    int fatorBalanceamento(No* no);
    void atualizarAltura(No* no);

    No* rotacaoDireita(No* y);
    No* rotacaoEsquerda(No* x);

    No* insereRecursivo(No* no, int id, int indice_evento);
    No* removeRecursivo(No* no, int id);
    
    void deletaArvore(No* no);

public:
    ArvoreAVLPacote();
    ~ArvoreAVLPacote();

    void insere(int id, int indice_evento);
    void remove(int id);
    Fila<int>* busca(int id);
};

#endif
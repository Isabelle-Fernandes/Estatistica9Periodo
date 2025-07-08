#include "../include/ArvoreAVLPacote.hpp"

No::No(int id) {
    this->id_pacote = id;
    this->altura = 1; 
    this->esquerda = nullptr;
    this->direita = nullptr;
    this->indices_eventos = Fila<int>();
}

ArvoreAVLPacote::ArvoreAVLPacote() {
    raiz = nullptr;
}

ArvoreAVLPacote::~ArvoreAVLPacote() {
    deletaArvore(raiz);
}

void ArvoreAVLPacote::deletaArvore(No* no) {
    if (no == nullptr) return;
    deletaArvore(no->esquerda);
    deletaArvore(no->direita);
    delete no;
}


int ArvoreAVLPacote::altura(No* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

void ArvoreAVLPacote::atualizarAltura(No* no) {
    if (no != nullptr) {
        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    }
}

int ArvoreAVLPacote::fatorBalanceamento(No* no) {
    if (no == nullptr) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// Rotacao Simples a Direita RR
No* ArvoreAVLPacote::rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rotacao
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    atualizarAltura(y);
    atualizarAltura(x);

    return x; // Nova raiz da subarvore
}

// Rotacao Simples a Esquerda LL
No* ArvoreAVLPacote::rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rotacao
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    atualizarAltura(x);
    atualizarAltura(y);

    return y; // Nova raiz da subarvore
}

void ArvoreAVLPacote::insere(int id, int indice_evento) {
    raiz = insereRecursivo(raiz, id, indice_evento);
}

No* ArvoreAVLPacote::insereRecursivo(No* no, int id, int indice_evento) {
    if (no == nullptr) {
        No* novoNo = new No(id);
        novoNo->indices_eventos.enfileira(indice_evento);
        return novoNo;
    }

    if (id < no->id_pacote) {
        no->esquerda = insereRecursivo(no->esquerda, id, indice_evento);
    } else if (id > no->id_pacote) {
        no->direita = insereRecursivo(no->direita, id, indice_evento);
    } else {
        // ID ja existe, apenas adiciona o novo indice de evento a fila
        no->indices_eventos.enfileira(indice_evento);
        return no;
    }

    atualizarAltura(no);

    // Calcula o fator de balanceamento para ver se precisa rebalancear
    int fb = fatorBalanceamento(no);

    // Caso Esquerda-Esquerda (LL)
    if (fb > 1 && id < no->esquerda->id_pacote) {
        return rotacaoDireita(no);
    }
    // Caso Direita-Direita (RR)
    if (fb < -1 && id > no->direita->id_pacote) {
        return rotacaoEsquerda(no);
    }
    // Caso Esquerda-Direita (LR)
    if (fb > 1 && id > no->esquerda->id_pacote) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    // Caso Direita-Esquerda (RL)
    if (fb < -1 && id < no->direita->id_pacote) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}


Fila<int>* ArvoreAVLPacote::busca(int id) {
    No* atual = raiz;
    while (atual != nullptr) {
        if (id < atual->id_pacote) {
            atual = atual->esquerda;
        } else if (id > atual->id_pacote) {
            atual = atual->direita;
        } else {
            // Retorna um ponteiro para a fila de indices.
            return &(atual->indices_eventos);
        }
    }
    return nullptr; // Nao encontrou
}
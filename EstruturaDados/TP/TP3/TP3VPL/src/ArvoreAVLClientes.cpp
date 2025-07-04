#include "../include/ArvoreAVLClientes.hpp"
#include <string>

NoCliente::NoCliente(std::string c, Evento* evento_) {
    cliente = c;
    listaPacotesCliente = new ListaPacotesCliente(evento_);
    altura = 1;
    esquerda = nullptr;
    direita = nullptr;
}

ArvoreAVLClientes::ArvoreAVLClientes() {
    raiz = nullptr;
}

ArvoreAVLClientes::~ArvoreAVLClientes() {
    deletaArvore(raiz);
}

void ArvoreAVLClientes::deletaArvore(NoCliente* no) {
    if (no == nullptr) return;
    deletaArvore(no->esquerda);
    deletaArvore(no->direita);

    delete no->listaPacotesCliente;
    delete no;
}

int ArvoreAVLClientes::altura(NoCliente* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

static int max(int a, int b) { 
    return (a > b) ? a : b;
}

void ArvoreAVLClientes::atualizarAltura(NoCliente* no) {
    if (no != nullptr) {
        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    }
}

int ArvoreAVLClientes::fatorBalanceamento(NoCliente* no) {
    if (no == nullptr) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// --- Rotacoes ---
NoCliente* ArvoreAVLClientes::rotacaoDireita(NoCliente* y) {
    NoCliente* x = y->esquerda;
    NoCliente* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

NoCliente* ArvoreAVLClientes::rotacaoEsquerda(NoCliente* x) {
    NoCliente* y = x->direita;
    NoCliente* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

void ArvoreAVLClientes::insere(std::string cliente, Evento* evento_) {
    raiz = insereRecursivo(raiz, cliente, evento_);
}

NoCliente* ArvoreAVLClientes::insereRecursivo(NoCliente* no, std::string cliente, Evento* evento_) {
    if (no == nullptr) {

        return new NoCliente(cliente, evento_);
    }
    
    if (cliente < no->cliente) {
        no->esquerda = insereRecursivo(no->esquerda, cliente, evento_);
    } else if (cliente > no->cliente) {
        no->direita = insereRecursivo(no->direita, cliente, evento_);
    } else {
        no->listaPacotesCliente->atualiza(evento_);
        // cliente ja existe, atualiza
        return no;
    }

    atualizarAltura(no);
    int fb = fatorBalanceamento(no);

    // Rebalanceamento
    if (fb > 1 && cliente < no->esquerda->cliente)
        return rotacaoDireita(no);
    if (fb < -1 && cliente > no->direita->cliente)
        return rotacaoEsquerda(no);
    if (fb > 1 && cliente > no->esquerda->cliente) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    if (fb < -1 && cliente < no->direita->cliente) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

ListaPacotesCliente* ArvoreAVLClientes::busca(std::string cliente) {
    NoCliente* atual = raiz;
    while (atual != nullptr) {
        if (cliente < atual->cliente) {
            atual = atual->esquerda;
        } else if (cliente > atual->cliente) {
            atual = atual->direita;
        } else {
            // Encontrou
            return atual->listaPacotesCliente;
        }
    }
    return nullptr; // Nao encontrou
}
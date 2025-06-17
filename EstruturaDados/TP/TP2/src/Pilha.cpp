#include "Pilha.hpp"

Item::Item(Pacote* p){
    pacote = p;
    prox = nullptr;
}

Pilha::Pilha() {
    topo = nullptr;
    tamanho = 0;
}

Pilha::~Pilha() {
    while (!estahVazia()) {
        desempilha();
    }
}

bool Pilha::estahVazia() {
    return (topo == nullptr);
}


void Pilha::empilha(Pacote* p) {
    Item* novoItem = new Item(p);
    novoItem->prox = topo; // O novo no aponta para o antigo topo
    topo = novoItem;       // O novo no se torna o topo
    tamanho++;
}

Pacote* Pilha::desempilha() {
    if (estahVazia()) {
        return nullptr; 
    }

    Item* itemRemovido = topo;
    Pacote* pacoteRemovido = itemRemovido->pacote;

    topo = topo->prox; // O topo agora e o proximo elemento
    
    delete itemRemovido;
    tamanho--;

    return pacoteRemovido;
}

ResultadoRetirada Pilha::retiraMaisAntigo() {
    ResultadoRetirada resultado;
    resultado.pacote = nullptr;
    resultado.custoManipulacao = 0;

    if (estahVazia()) {
        return resultado; // Retorna resultado vazio se a pilha estiver vazia
    }

    //Caso 1: A pilha so tem um elemento. Ele e o mais antigo.
    if (this->tamanho == 1) {
        resultado.pacote = this->desempilha();
        // Custo e zero porque nao precisamos mover outros pacotes.
        resultado.custoManipulacao = 0; 
        return resultado;
    }

    // Caso 2: A pilha tem mais de um elemento.
    // Precisamos de uma pilha auxiliar para guardar os pacotes temporariamente.
    Pilha auxiliar;

    // Passo 1: Mover todos os pacotes, exceto o ultimo (o do fundo),
    // da pilha principal para a pilha auxiliar.
    while (this->tamanho > 1) {
        auxiliar.empilha(this->desempilha());
        resultado.custoManipulacao++; // Cada movimento tem um custo
    }

    // Passo 2: Agora, o unico pacote que sobrou na pilha principal e o do fundo.
    // Este e o nosso alvo.
    resultado.pacote = this->desempilha();
    // Nao contamos custo para a retirada do pacote alvo em si.

    // Passo 3: Devolver os pacotes da pilha auxiliar para a pilha principal,
    // restaurando a ordem original.
    while (!auxiliar.estahVazia()) {
        this->empilha(auxiliar.desempilha());
    }
    
    return resultado;
}
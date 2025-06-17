#include "Armazem.hpp"
#include <iostream>

Armazem::Armazem() {
    id = -1;
    grau = 0;
    secoes = nullptr;
    mapaDeDestinos = nullptr;
}

Armazem::~Armazem() {
    delete[] secoes;
    delete[] mapaDeDestinos;
}

// Configura o armazem com base na topologia do grafo
void Armazem::inicializar(int idArmazem, int grauDoVertice, int* idsDosVizinhos) {
    this->id = idArmazem;
    this->grau = grauDoVertice;
    
    // Aloca memoria para o array de secoes (pilhas) e para o mapa de destinos
    if (this->grau > 0) {
        this->secoes = new Pilha[this->grau];
        this->mapaDeDestinos = new int[this->grau];

        // Preenche o mapa de destinos com os IDs dos vizinhos
        for (int i = 0; i < this->grau; i++) {
            this->mapaDeDestinos[i] = idsDosVizinhos[i];
        }
    }
}

// Funcao auxiliar para encontrar o indice da pilha correta
int Armazem::encontraIndiceDaSecao(int idDestino) {
    for (int i = 0; i < this->grau; i++) {
        if (this->mapaDeDestinos[i] == idDestino) {
            return i;
        }
    }
    return -1; // Retorna -1 se nao ha uma conexao direta (erro de rota)
}

// Coloca um pacote na secao (pilha) correta
void Armazem::armazena(Pacote* p) {

    int proximoDestino = p->proximoDestino; 

    int indiceSecao = encontraIndiceDaSecao(proximoDestino);

    if (indiceSecao != -1) {
        this->secoes[indiceSecao].empilha(p);
        // std::cout << "Pacote " << p->id << " armazenado no armazem " << this->id << " para o proximo destino " << proximoDestino << std::endl;
    } else {
        std::cerr << "ERRO: No armazem " << this->id << ", rota invalida! Nao ha secao para o destino " << proximoDestino << std::endl;
    }
}

// Retira os pacotes mais antigos de uma secao para transporte
ResultadoTransporte Armazem::recuperaParaTransporte(int idDestino, int capacidade) {
    ResultadoTransporte resultado;
    resultado.custoTotalManipulacao = 0;

    int indiceSecao = encontraIndiceDaSecao(idDestino);

    if (indiceSecao == -1) {
        std::cerr << "ERRO: Tentativa de recuperar pacotes para um destino invalido " << idDestino << std::endl;
        return resultado; // Retorna um resultado vazio
    }

    Pilha& secaoAlvo = this->secoes[indiceSecao];

    // Itera ate a capacidade do transporte ou ate a secao esvaziar
    for (int i = 0; i < capacidade && !secaoAlvo.estaVazia(); i++) {
        // Usa a funcao especial da pilha para pegar o mais antigo
        ResultadoRetirada res = secaoAlvo.retiraMaisAntigo();
        
        if (res.pacote != nullptr) {
            // Adiciona o pacote recuperado a pilha de pacotes a serem transportados
            resultado.pacotes.empilha(res.pacote);
            // Acumula o custo de manipulacao
            resultado.custoTotalManipulacao += res.custoManipulacao;
        }
    }
    
    return resultado;
}

// Verifica se todas as secoes do armazem estao vazias
bool Armazem::estaVazio() {
    for (int i = 0; i < this->grau; i++) {
        if (!this->secoes[i].estaVazia()) {
            return false; // Encontrou uma secao com pacotes, entao o armazem nao esta vazio
        }
    }
    return true; // Se o laco terminar, todas as secoes estao vazias
}
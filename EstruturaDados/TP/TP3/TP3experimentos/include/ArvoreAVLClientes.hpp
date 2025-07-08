#ifndef ARVORE_AVL_CLIENTES_HPP
#define ARVORE_AVL_CLIENTES_HPP

#include "Evento.hpp"
#include "ListaPacotesCliente.hpp" 
#include <string>                

class NoCliente {
public:
    std::string cliente;  // A chave da ALV eh o nome do cliente
    ListaPacotesCliente* listaPacotesCliente;   
    int altura;
    NoCliente *esquerda;
    NoCliente *direita;

    NoCliente(std::string c, Evento* evento_);
};

class ArvoreAVLClientes {
private:
    NoCliente* raiz;

    // Metodos auxiliares privados
    int altura(NoCliente* no);
    int fatorBalanceamento(NoCliente* no);
    void atualizarAltura(NoCliente* no);

    NoCliente* rotacaoDireita(NoCliente* y);
    NoCliente* rotacaoEsquerda(NoCliente* x);

    NoCliente* insereRecursivo(NoCliente* no, std::string cliente, Evento* evento_);
    
    void deletaArvore(NoCliente* no);

public:
    ArvoreAVLClientes();
    ~ArvoreAVLClientes();

    void insere(std::string cliente, Evento* evento_);
    ListaPacotesCliente* busca(std::string cliente); 
};

#endif
#include "Evento.hpp"

class Escalonador {
public:
    int quantidadeEventos;
    int capacidade; // tamanho maximo do array de eventos
    Evento* eventos;
    int intervaloTransporte;
    Escalonador(int _capacidade, int _intervaloTransporte);
    ~Escalonador();

    // metodos basicos aplicados ao min heap
    int GetAncestral(int i);
    int GetSucessorEsq(int i);
    int GetSucessorDir(int i);
    int GetMenorSucessor(int i);
    void insereEvento(Evento e);
    Evento retiraProximoEvento();
    void Conserta();
    bool estaVazio();
    void redimensionar(int novaCapacidade); // metodo para redimensionar o array de eventos
    bool heapVazio();

};



#include <iostream>
#include <cstdlib>  
#include <cmath> 
#include <chrono>
#include <fstream>
#include <iomanip>
#include "Vetor.hpp"
#include "QuicksortIns.hpp"

#define MINPART 10 // estou definindo o tamanho mínimo da partição para o algoritmo quicksortIns arbitrariamente

int main() {

    Vetor vet = Vetor();
    int i, j, p;
    long mult = (long)pow(10, KEYSZ - 1);

    srand48(1);  // inicializa o gerador com uma semente

    for (i = 0; i < VETSZ; i++) {
        // gera uma chave aleatória e extrai cada dígito
        for (j = (int)(drand48() * mult), p = KEYSZ - 2; p >= 0; j /= 10, p--)
            vet.itens[i].key[p] = '0'+ (j % 10);
        vet.itens[i].key[KEYSZ - 1] = '\0';  // termina a string

        // preenche o payload com '0', '1', ..., até PLSZ-2
        for (j = 0; j < PLSZ - 1; j++)
            vet.itens[i].payload[j] = '0' + (j % 10);
        vet.itens[i].payload[PLSZ - 1] = '\0';
    }
    
    QuicksortIns quicksort = QuicksortIns();

    auto start = std::chrono::high_resolution_clock::now();

    quicksort.quickSort3Ins(vet, 0, VETSZ - 1, MINPART);

    auto end = std::chrono::high_resolution_clock::now();

    auto tempo_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); //pego em nanosegundos
    long double tempo_ms = tempo_nano / 1e6; // converto para milissegundos

    std::ofstream outfile("resultados.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << VETSZ << ";"
                << vet.comparacoes << ";"
                << vet.movimentacoes << ";"
                << vet.chamadas << ";"
                << std::fixed << std::setprecision(7) << tempo_ms << std::endl; // gravo o tempo em milissegundos com 7 casas decimais
        outfile.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    }

    return 0;
}


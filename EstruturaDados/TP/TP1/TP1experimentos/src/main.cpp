
#include <cstdlib>  
#include <chrono>
#include <fstream>
#include <iomanip>
#include "LimiarParticao.hpp"
#include "LimiarQuebra.hpp"


#ifndef QUEBRA
#define QUEBRA 6  // Na verdade o numero de quebras nao é 6, mas sim o valor informado no momento de compilar o executável
#endif

int main() {

    int seed, tam; 
    double limiarCusto, parametroA, parametroB, parametroC;

    parametroA = 0.0000078130315;
    parametroB = -0.00000017861427;
    parametroC = 0.00045075496;
    limiarCusto = 10.000000;
    seed = 1;
    tam = VETSZ;

    QuicksortIns quickSort =  QuicksortIns(); 
    Insertion insertion = Insertion();
    OrdenadorUniversal ordenadorUniversal = OrdenadorUniversal();

    Vetor vetor = Vetor(seed);
    
    LimiarParticao limiarParticao = LimiarParticao(parametroA, parametroB, parametroC);
    int limiteParticao = limiarParticao.DeterminaLimiarParticao(vetor, tam, limiarCusto);

    quickSort.quickSort3Ins(vetor, 0, tam - 1, limiteParticao); // ordeno o vetor para induzir o numero de quebras no vetor ordenado
    vetor.resetCounter();

    LimiarQuebra limiarQuebra = LimiarQuebra(parametroA, parametroB, parametroC);
    int limiteQuebras = limiarQuebra.DeterminaLimiarQuebra(vetor, tam, limiarCusto, limiteParticao, seed);

    /* Depois de ter os limites de quebra e particao, ordeno o vetor com o OrdenadorUniversal e computo o tempo
    Nessa parte, salvo em um arquivo o tempo de execução, o número de comparações, movimentações, chamadas,
    o limiteParticao, o limiteQuebras, o numero de quebras do vetor, o tamanho do vetor, tamanho da chave, 
    tamanho payload */

    vetor.resetCounter();
    vetor.InduzirQuebras(QUEBRA, seed); // induzo as quebras no vetor informada no compilador

    auto start = std::chrono::high_resolution_clock::now();
    ordenadorUniversal.Ordena(vetor, tam, limiteParticao, limiteQuebras, QUEBRA);
    auto end = std::chrono::high_resolution_clock::now();
    auto tempo_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); //pego em nanosegundos
    long double tempo_ms_ordenador = tempo_nano / 1e6; // converto para milissegundos
    int chamada_ordenador = vetor.chamadas; // pego o número de chamadas do ordenador universal
    int comparacoes_ordenador = vetor.comparacoes; // pego o número de comparações do ordenador universal
    int movimentacoes_ordenador = vetor.movimentacoes; // pego o número de movimentações do ordenador universal

    vetor.resetCounter();
    vetor.InduzirQuebras(QUEBRA, seed); // induzo as quebras no vetor informada no compilador

    auto start_quick = std::chrono::high_resolution_clock::now();
    quickSort.quickSort3Ins(vetor, 0, tam - 1, 1); // ordeno o vetor pelo quickSortIns sem otimização com número arbitrário de partição igual a 10
    auto end_quick = std::chrono::high_resolution_clock::now();
    auto tempo_nano_quick = std::chrono::duration_cast<std::chrono::nanoseconds>(end_quick - start_quick).count(); //pego em nanosegundos
    long double tempo_ms_quick = tempo_nano_quick / 1e6; // converto para milissegundos
    int chamada_quick = vetor.chamadas; // pego o número de chamadas do quickSort
    int comparacoes_quick = vetor.comparacoes; // pego o número de comparações do quickSort
    int movimentacoes_quick = vetor.movimentacoes; // pego o número de movimentações do quickSort    

    vetor.resetCounter();
    vetor.InduzirQuebras(QUEBRA, seed); // induzo as quebras no vetor informada no compilador

    auto start_ins = std::chrono::high_resolution_clock::now();
    insertion.insertionSort(vetor, 0, tam - 1); // ordeno o vetor pelo insertionSort
    auto end_ins = std::chrono::high_resolution_clock::now();
    auto tempo_nano_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ins - start_ins).count(); //pego em nanosegundos
    long double tempo_ms_ins = tempo_nano_ins / 1e6; // converto para milissegundos
    int chamada_ins = vetor.chamadas; // pego o número de chamadas do insertionSort
    int comparacoes_ins = vetor.comparacoes; // pego o número de comparações do insertionSort
    int movimentacoes_ins = vetor.movimentacoes; // pego o número de movimentações do insertionSort

    std::ofstream outfile("resultados.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << KEYSZ << ";"
                << PLSZ << ";"
                << VETSZ << ";"
                << QUEBRA << ";"
                << limiteParticao << ";"
                << limiteQuebras << ";"
                << chamada_ordenador << ";"
                << comparacoes_ordenador << ";"
                << movimentacoes_ordenador << ";"
                << chamada_quick << ";"
                << comparacoes_quick << ";"
                << movimentacoes_quick << ";"
                << chamada_ins << ";"
                << comparacoes_ins << ";"
                << movimentacoes_ins << ";"
                << std::fixed << std::setprecision(7) << tempo_ms_ordenador << ";"
                << std::fixed << std::setprecision(7) << tempo_ms_quick << ";"
                << std::fixed << std::setprecision(7) << tempo_ms_ins << std::endl; // gravo o tempo em milissegundos com 7 casas decimais
        outfile.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    }

}


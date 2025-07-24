#include <iostream>     // Para entrada e saída padrão
#include <iomanip>      // Para controlar a formatação de saída (como número de casas decimais)
#include <cstdlib>      // Para funções como srand48()
#include "../include/ordenador.hpp" // Declaração das funções principais do projeto
#include "../include/sortperf.hpp"  // Declaração da struct de performance e utilitários de medição

using namespace std;

int main(int argc, char** argv) {
    // Verifica se o usuário passou o nome do arquivo de entrada como argumento
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1; // Encerra com erro
    }

    // Redireciona a entrada padrão para o arquivo informado
    if (freopen(argv[1], "r", stdin) == nullptr) {
        cerr << "Erro ao abrir o arquivo " << argv[1] << '\n';
        return 1;
    }

    // Define a precisão dos números de ponto flutuante na saída para 9 casas decimais
    cout << fixed << setprecision(9);

    // Variáveis para os parâmetros lidos do arquivo
    int seed;
    double limiarCusto, a, b, c;
    int tam;

    // Lê da entrada: semente, limiar de custo, pesos a/b/c e tamanho do vetor
    cin >> seed >> limiarCusto >> a >> b >> c >> tam;
    srand48(seed); // Inicializa o gerador de números aleatórios com a semente

    // Aloca dinamicamente o vetor de inteiros com o tamanho especificado
    int* vet = new int[tam];
    for (int i = 0; i < tam; ++i) {
        cin >> vet[i]; // Lê os elementos do vetor
    }

    // Mostra informações iniciais do vetor, incluindo a quantidade de quebras
    cout << "size " << tam << " seed " << seed << " breaks " << contaQuebras(vet, tam) << endl << endl;;
    // ================================
    // FASE 1: Calibração do limiar da partição
    // ================================
    int limPart = determinaLimiarParticao(vet, tam, limiarCusto, a, b, c);

    // ================================
    // FASE 2: Calibração do limiar de quebras
    // ================================
    sortperf_t perf;
    quickSort3Ins(vet, 0, tam - 1, limPart, &perf); // Executa quicksort para avaliar performance
    resetcounter(&perf); // Zera os contadores para a próxima medição

    int limQuebras = determinaLimiarQuebras(limiarCusto, vet, tam, limPart, a, b, c, seed);

    // ================================
    // FASE 3: Ordenação final com parâmetros calibrados
    // ================================
    ordenadorUniversal(vet, tam, limPart, limQuebras, &perf);

    // Libera a memória alocada dinamicamente
    delete[] vet;
    return 0; // Fim
}
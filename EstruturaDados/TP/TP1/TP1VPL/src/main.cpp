#include "LimiarParticao.hpp"
#include "LimiarQuebra.hpp"
#include <fstream>

int main(int argc, char* argv[]) {

    int seed, tam; 
    double limiarCusto, parametroA, parametroB, parametroC;

    if (argc != 2) {
        std::cerr << "Erro: É preciso fornecer nome arquivo txt como argumento." << std::endl;
        return 1;
    }

    std::string nome_arquivo = argv[1];
    std::ifstream arquivo(nome_arquivo);

    arquivo >> seed;
    arquivo >> limiarCusto;
    arquivo >> parametroA;
    arquivo >> parametroB;
    arquivo >> parametroC;
    arquivo >> tam;

    Vetor vetor = Vetor(tam);
    for (int i = 0; i < tam; ++i) {
        arquivo >> vetor.vetor[i]; 
    }

    int breaks = vetor.breaks();

    std::cout << "size " << tam << " seed " << seed << " breaks " << breaks << std::endl;
    std::cout << std::endl;

    LimiarParticao limiarParticao = LimiarParticao(parametroA, parametroB, parametroC);
    int limiteParticao = limiarParticao.DeterminaLimiarParticao(vetor, tam, limiarCusto);

    QuicksortIns quickSort =  QuicksortIns(); 
    quickSort.quickSort3Ins(vetor, 0, tam - 1, limiteParticao); // ordeno o vetor para induzir o numero de quebras no vetor ordenado
    vetor.resetCounter();

    LimiarQuebra limiarQuebra = LimiarQuebra(parametroA, parametroB, parametroC);
    int limiteQuebras = limiarQuebra.DeterminaLimiarQuebra(vetor, tam, limiarCusto, limiteParticao, seed);

}
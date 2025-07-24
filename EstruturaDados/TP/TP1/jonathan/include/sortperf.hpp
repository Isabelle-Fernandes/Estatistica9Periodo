#ifndef SORTPERF_HPP
#define SORTPERF_HPP

// Define uma struct chamada sortperf_t que serve para medir a performance de algoritmos de ordenação.
// Ela registra o número de comparações (cmp), movimentações (move) e chamadas recursivas (calls).
typedef struct sortperf {
    int cmp;    // Quantidade de comparações feitas (ex: a < b)
    int move;   // Quantidade de movimentações (ex: trocas de elementos)
    int calls;  // Quantidade de chamadas de função (geralmente usada para recursão)
} sortperf_t;

// Reinicializa os contadores da struct para zero.
// Use antes de iniciar uma nova medição de performance.
void resetcounter(sortperf_t *s);

// Incrementa o número de comparações realizadas por um certo valor (num).
void inccmp(sortperf_t *s, int num);

// Incrementa o número de movimentações realizadas por um certo valor (num).
void incmove(sortperf_t *s, int num);

// Incrementa o número de chamadas recursivas realizadas por um certo valor (num).
void inccalls(sortperf_t *s, int num);

// Calcula o custo total da ordenação com base nos pesos a, b e c para comparações, movimentações e chamadas.
// Fórmula: custo = a * cmp + b * move + c * calls
long double getCost(sortperf_t *s, long double a, long double b, long double c);

// Embaralha o vetor 'vet' de tamanho 'size' por 'numShuffle' trocas aleatórias usando uma semente 'seed'.
// Ideal para testar algoritmos com dados aleatórios e reprodutíveis.
void shuffleVector(int *vet, int size, int numShuffle, int seed);

#endif
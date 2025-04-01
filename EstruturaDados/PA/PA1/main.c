//---------------------------------------------------------------------
// Arquivo      : evalenum.c
// Conteudo     : avaliacao de desempenho de algoritmos de ordenacao 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2023-11-04 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

typedef struct opt{
  int size;
  int seed;
  int alg;
} opt_t;

typedef struct sortperf{
  int cmp;
  int move;
  int calls;
} sortperf_t;

void resetcounter(sortperf_t * s){
// Descricao: inicializa estrutura
// Entrada: 
// Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t * s, int num){
// Descricao: incrementa o numero de comparacoes em num 
// Entrada: s, num
// Saida: s
  s->cmp += num;
}

void incmove(sortperf_t * s, int num){
// Descricao: incrementa o numero de movimentacoes de dados em num 
// Entrada: s, num
// Saida: s
  s->move += num;
}

void inccalls(sortperf_t * s, int num){
// Descricao: incrementa o numero de chamadas de função em num 
// Entrada: s, num
// Saida: s
  s->calls += num;
}

char * printsortperf(sortperf_t * s, char * str, char * pref){
// Descricao: gera string com valores de sortperf 
// Entrada: s, pref
// Saida: str

 sprintf(str,"%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls); 
 return str;
}


void initVector(int * vet, int size){
// Descricao: inicializa vet com valores aleatorios
// Entrada: vet
// Saida: vet
  int i;
  // inicializa a parte alocada da vetor com valores aleatorios
  for (i=0; i<size; i++){
    vet[i] = (int)(drand48()*size);
  }
}

void printVector(int * vet, int size){
// Descricao: printa vet com valores aleatorios
// Entrada: vet
// Saida: vet
  int i;
  for (i=0; i<size; i++){
    printf("%d ",vet[i]);
  }
  printf("\n");
}

void swap(int *xp, int *yp, sortperf_t *s){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s,3);
}

// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)
{
    // find the minimum element in the unsorted subarray `[i…n-1]`
    // and swap it with `arr[i]`
    int min = l;
    inccalls(s,1);
    for (int j = l + 1; j <= r; j++)
    {
        // if `arr[j]` is less, then it is the new minimum
	inccmp(s,1);
        if (arr[j] < arr[min]) {
            min = j;    // update the index of minimum element
        }
    }

    // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
    if (min!=l)
      swap(&arr[min], &arr[l], s);

    if (l + 1 < r) {
        recursiveSelectionSort(arr, l + 1, r, s);
    }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t * s) { 
  int min = l;

  for(int i = 0; i <= r; i++){
    for(int j = i + 1; j <= r; j++){
      if(arr[min] > arr[j]) min = j;
    }
    if(min != l) swap(&arr[min], &arr[l], s);
    
    min = ++l;
  }
 
  return;
}

//insertion sort
void insertionSort(int v[], int l, int r, sortperf_t * s) {
  
  for(int i = 1; i <= r; i++){
    int aux = v[l + i];
    int j = i - 1;
    while((j >= 0) && (aux < v[j])){
      swap(&v[j + 1], &v[j], s);
      j--;
    }

  }
  return;
}

// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

// quicksort partition using median of 3
void partition3(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
}

// standard quicksort partition
void partition(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
}

// standard quicksort
void quickSort(int * A, int l, int r, sortperf_t *s) { 
}

// quicksort with median of 3
void quickSort3(int * A, int l, int r, sortperf_t *s) { 
}

// quicksort with insertion for small partitions
void quickSortIns(int * A, int l, int r, sortperf_t *s) { 
}

// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int * A, int l, int r, sortperf_t *s) { 
}

int main (){
  sortperf_t s;
  int * vet;
  opt_t opt;

  opt.seed = 1;
  opt.size = 10;
  opt.alg = 1;

  vet = (int *) malloc((10+1)*sizeof(int));

  resetcounter(&s);
  srand48(opt.seed);
  initVector(vet, opt.size);
  vet[opt.size] = vet[0]; // for heapsort
  if (opt.size < 100) printVector(vet, opt.size);
  
  // execute algorithm
  insertionSort(vet, 0, opt.size-1, &s);

  if (opt.size<100) printVector(vet, opt.size);

  exit(0);
}

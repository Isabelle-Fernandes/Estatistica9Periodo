// A union-find algorithm to identify islands
#include <stdio.h>
#include <stdlib.h>

typedef struct subset {
	int parent;
	int rank;
}subset;

// A utility function to find set of an element i

int Find(subset subsets[], int i){
  if (subsets[i].parent == i){
    return i;
  } else {
    return Find(subsets, subsets[i].parent);
  }
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(subset subsets[], int xroot, int yroot){
// Attach smaller rank tree under root of high rank tree
// (Union by Rank)
  if (subsets[xroot].rank < subsets[yroot].rank)
    subsets[xroot].parent = yroot;
  else if (subsets[xroot].rank > subsets[yroot].rank)
    subsets[yroot].parent = xroot;
  // If ranks are same, then make one as root and
  // increment its rank by one
    else {
      subsets[yroot].parent = xroot;
      subsets[xroot].rank++;
    }
}

int rndnode(int nodes){ return (int)(drand48()*nodes); }  

int main(int argc, char *argv[]){

  if (argc < 5) { // 1 para o nome do programa + 3 para os nossos parametros
    // Imprime uma mensagem de erro na saida de erro padrao
    fprintf(stderr, "Uso: %s <numero_de_nos> <numero_de_pacotes> <semente_aleatoria>\n", argv[0]);
    fprintf(stderr, "Exemplo: %s 20 500 123\n", argv[0]);
    return 1; // Retorna 1 para indicar um erro
  }

  int seed = 1;
  int transportcapacity = atoi(argv[1]);
  int transportcost = 20;
  int transportinterval = atoi(argv[2]);
  int retrievecost = 1;
  int nodes = atoi(argv[3]);
  int numpackets = atoi(argv[4]);
  int conncomp = nodes;
  long atime=1;
  long rtime=10;
  int src, dst, fsrc, fdst;

  srand48(seed);

  subset * ss = (subset*)malloc(sizeof(subset)*nodes);
  for (int i=0; i<nodes; i++){
    ss[i].parent = i;
    ss[i].rank = 0;
  }
  int * graph = (int*) malloc(sizeof(int)*nodes*nodes);
  for (int i=0; i<nodes*nodes; i++) graph[i] = 0;

  printf("%d\n%d\n%d\n%d\n", transportcapacity, transportcost, 
         transportinterval, retrievecost);
 
  while(conncomp>1){
    do {
      src = rndnode(nodes);
      dst = rndnode(nodes);
    } while (src == dst);
    fsrc = Find(ss,src);
    fdst = Find(ss,dst);
    if (fsrc!=fdst){
      Union(ss,fsrc,fdst); 
      conncomp--;
      graph[src*nodes+dst] = 1;
      graph[dst*nodes+src] = 1;
    }
  }

  printf("%d\n",nodes);
  for (int i=0; i<nodes; i++){
    for (int j=0; j<nodes; j++){
      printf("%d",graph[i*nodes+j]);
      if (j<nodes-1){
        printf(" ");
      } else {
        printf("\n");
      }
    }
  }
 
  printf("%d\n",numpackets);
  for (int i=0; i<numpackets; i++){
    do {
      src = rndnode(nodes);
      dst = rndnode(nodes);
    } while (src == dst);
    atime += (long)(drand48()*rtime);
    printf("%ld pac %d org %d dst %d\n",atime,i,src,dst);
  }
  
  return numpackets;
}


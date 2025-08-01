#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
#include <algorithm>

typedef struct s_edge {
    int u;
    int v;
    int custo;

    bool operator<(const s_edge& outra) const {
        return custo < outra.custo;
    }
    
    bool operator>(const s_edge& outra) const {
        return custo > outra.custo;
    }

    bool operator==(const s_edge& outra) const {
        return custo == outra.custo;
    }

} Aresta;

typedef struct s_subset{
    int representante;
    int rank;
} Subconjunto;

class UnionFind{
public:
    UnionFind(int quantidade_subconjuntos);
    ~UnionFind();
    void Make(int x);
    int Find(int x);
    void Union(int x, int y);
private:
    int tamanho;
    Subconjunto* subconjuntos;
};

#endif
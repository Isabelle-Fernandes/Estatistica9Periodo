#include "CalculaRota.hpp" 
#include "Fila.hpp" 

void ImprimeRota(int* rota, int tamanho_rota) {
    std::cout << "Menor Rota: ";
    for (int i = 0; i < tamanho_rota; i++) {
        std::cout << rota[i] << " ";
    }
    std::cout << std::endl;
}

// Retorna um array com a rota. O primeiro elemento do array eh o tamanho da rota
int* BuscaMenorRota(Pacote &pacote, Grafo &grafo, int &tamanho_rota) {
    int origem = pacote.armazemOrigem; // Vertice de origem
    int destino = pacote.armazemDestino; // Vertice de destino

    int n = grafo.numeroVertices;

    // Estruturas de dados auxiliares
    bool* visitado = new bool[n]; 
    int* predecessor = new int[n];
    Fila fila; // Fila para a busca em largura (BFS)

    for (int i = 0; i < n; i++) {
        visitado[i] = false; // Inicializo o vetor com todsos os vertices como nao visitados
        predecessor[i] = -1; // -1 indica que nao ha predecessor
    }

    // Inicia a busca a partir da origem
    visitado[origem] = true;
    fila.enfileira(origem);

    // Loop principal da BFS
    while (!fila.estahVazia()) {
        int u = fila.desenfileira(); // Pega o proximo vertice da fila

        // Se encontramos o destino, podemos parar a busca
        if (u == destino) {
            break;
        }

        // Itera sobre os vizinhos do vertice 'u'
        Vertice* vizinho_atual = grafo.listaAdjacencia[u]->origem->prox;
        while (vizinho_atual != nullptr) {
            int v = vizinho_atual->vertice;
            if (!visitado[v]) {
                visitado[v] = true;
                predecessor[v] = u; // Marca 'u' como predecessor de 'v'
                fila.enfileira(v);
            }
            vizinho_atual = vizinho_atual->prox;
        }
    }

    // Reconstroi a rota a partir do destino
    if (predecessor[destino] == -1) {
        // Nao foi encontrado um caminho
        delete[] visitado;
        delete[] predecessor;
        return nullptr;
    }

    int* rota_invertida = new int[n];
    tamanho_rota = 0;
    int atual = destino;
    while(atual != -1) {
        rota_invertida[tamanho_rota] = atual;
        tamanho_rota++;
        atual = predecessor[atual];
    }

    // Cria o array final no formato correto (tamanho seguido da rota)
    int* rota_final = new int[tamanho_rota];
    for(int i = 0; i < tamanho_rota; i++) {
        rota_final[i] = rota_invertida[tamanho_rota - i - 1];
    }

    // Limpa a memória alocada
    delete[] visitado;
    delete[] predecessor;
    delete[] rota_invertida;

    return rota_final;
}

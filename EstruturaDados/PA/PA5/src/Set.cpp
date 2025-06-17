#include "Set.hpp"


StringSet::StringSet(int tamanho) {
    // Garante que o tamanho seja pelo menos 1 para evitar alocações de tamanho 0.
    int capacidade_inicial = (tamanho > 0) ? tamanho : 1;
    
    this->tamanhoOriginal = capacidade_inicial;
    this->tamanhoTabela = capacidade_inicial;
    this->tamanhoConjunto = 0;

    // Aloca o array de ElementoTabela
    this->tabela = new ElementoTabela[this->tamanhoTabela];

    // Inicializa todos os elementos da tabela como vazios
    for (int i = 0; i < this->tamanhoTabela; i++) {
        this->tabela[i].vazio = true;
        this->tabela[i].retirada = false;
    }
}

StringSet::~StringSet() {
    // Libera a memória alocada para a tabela
    delete[] this->tabela;
}



// Função de hash (djb2) que mapeia uma string para um índice da tabela.

int StringSet::Hash(string s) {
    unsigned long hash = 5381;
    for (char c : s) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % this->tamanhoTabela;
}

// Redimensiona a tabela hash para um novo tamanho e re-insere todos os elementos.

void StringSet::Resize(size_t novo_tamanho) {
    int antiga_capacidade = this->tamanhoTabela;
    ElementoTabela* tabela_antiga = this->tabela;

    // Atualiza para a nova capacidade e aloca a nova tabela
    this->tamanhoTabela = novo_tamanho;
    this->tabela = new ElementoTabela[this->tamanhoTabela];
    this->tamanhoConjunto = 0; // Será recontado durante a reinserção

    // Inicializa a nova tabela
    for (int i = 0; i < this->tamanhoTabela; i++) {
        this->tabela[i].vazio = true;
        this->tabela[i].retirada = false;
    }

    // Percorre a tabela antiga e insere os elementos válidos na nova
    for (int i = 0; i < antiga_capacidade; i++) {
        if (!tabela_antiga[i].vazio && !tabela_antiga[i].retirada) {
            this->Inserir(tabela_antiga[i].dado);
        }
    }

    // Libera a memória da tabela antiga
    delete[] tabela_antiga;
}


void StringSet::Rehash(int pos) {
    // A lógica de rehashing foi implementada em Resize
}

void StringSet::Inserir(string s) {
    // Verifica se o fator de carga excede 75% e redimensiona se necessário.
    if (static_cast<double>(this->tamanhoConjunto + 1) / this->tamanhoTabela > 0.75) {
        Resize(this->tamanhoTabela * 2);
    }

    int pos_inicial = Hash(s);
    int pos_insercao = -1;

    for (int i = 0; i < this->tamanhoTabela; i++) {
        int pos_atual = (pos_inicial + i) % this->tamanhoTabela;

        // Se o elemento já existe, não faz nada.
        if (!tabela[pos_atual].vazio && !tabela[pos_atual].retirada && tabela[pos_atual].dado == s) {
            return;
        }

        // Encontra o primeiro local disponível (removido ou vazio) para inserção.
        if (tabela[pos_atual].vazio || tabela[pos_atual].retirada) {
            pos_insercao = pos_atual;
            break;
        }
    }
    
    // Insere o elemento na posição encontrada
    if (pos_insercao != -1) {
        tabela[pos_insercao].dado = s;
        tabela[pos_insercao].vazio = false;
        tabela[pos_insercao].retirada = false;
        this->tamanhoConjunto++;
    }
}

void StringSet::Remover(string s) {
    int pos_inicial = Hash(s);
    for (int i = 0; i < this->tamanhoTabela; i++) {
        int pos_atual = (pos_inicial + i) % this->tamanhoTabela;

        // Se achou uma posição totalmente vazia, o elemento não existe.
        if (tabela[pos_atual].vazio) {
            return;
        }

        // Se achou o elemento, marca como retirado.
        if (!tabela[pos_atual].retirada && tabela[pos_atual].dado == s) {
            tabela[pos_atual].retirada = true;
            this->tamanhoConjunto--;
            return;
        }
    }
}

bool StringSet::Pertence(string s) {
    int pos_inicial = Hash(s);
    for (int i = 0; i < this->tamanhoTabela; i++) {
        int pos_atual = (pos_inicial + i) % this->tamanhoTabela;

        // Se achou uma posição totalmente vazia, o elemento não existe.
        if (tabela[pos_atual].vazio) {
            return false;
        }

        // Se achou o elemento, retorna verdadeiro.
        if (!tabela[pos_atual].retirada && tabela[pos_atual].dado == s) {
            return true;
        }
    }
    return false;
}


//Operações de Conjunto

StringSet* StringSet::Uniao(StringSet* S) {
    StringSet* resultado = new StringSet(this->tamanhoConjunto + S->tamanhoConjunto);

    // Insere todos os elementos deste conjunto
    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) {
            resultado->Inserir(this->tabela[i].dado);
        }
    }

    // Insere todos os elementos do outro conjunto (Inserir lida com duplicatas)
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado;
}

StringSet* StringSet::Intersecao(StringSet* S) {
    StringSet* resultado = new StringSet(min(this->tamanhoConjunto, S->tamanhoConjunto));

    // Percorre o menor conjunto e verifica se o elemento pertence ao maior
    StringSet* menor_conjunto = (this->tamanhoConjunto < S->tamanhoConjunto) ? this : S;
    StringSet* maior_conjunto = (menor_conjunto == this) ? S : this;

    for (int i = 0; i < menor_conjunto->tamanhoTabela; i++) {
        if (!menor_conjunto->tabela[i].vazio && !menor_conjunto->tabela[i].retirada) {
            if (maior_conjunto->Pertence(menor_conjunto->tabela[i].dado)) {
                resultado->Inserir(menor_conjunto->tabela[i].dado);
            }
        }
    }
    return resultado;
}

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {
    StringSet* resultado = new StringSet(this->tamanhoConjunto + S->tamanhoConjunto);

    // Adiciona elementos que estão em `this` mas não em `S`
    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) {
            if (!S->Pertence(this->tabela[i].dado)) {
                resultado->Inserir(this->tabela[i].dado);
            }
        }
    }

    // Adiciona elementos que estão em `S` mas não em `this`
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            if (!this->Pertence(S->tabela[i].dado)) {
                resultado->Inserir(S->tabela[i].dado);
            }
        }
    }
    return resultado;
}


// Impressão

void StringSet::Imprimir() {
    bool primeiro = true;
    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            if (!primeiro) {
                cout << " ";
            }
            cout << tabela[i].dado;
            primeiro = false;
        }
    }
    cout << endl;
}
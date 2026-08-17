#include <stdio.h>
#include <stdlib.h>

// 1. O Nó da Pilha (cada elemento individual)
typedef struct Elemento {
    int num;
    struct Elemento *prox;
} Elemento;

// 2. O Controlador da Pilha
typedef struct Pilha {
    Elemento *topo;
} Pilha;

// 3. Função para criar uma pilha vazia na memória
Pilha* criarPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void empilhar(Pilha *p, int valor) {
    // 1. Criar e preparar o novo nó
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->num = valor;

    // 2. O novo nó aponta para o antigo topo (NULL se a pilha estiver vazia)
    novo->prox = p->topo;

    // 3. O novo nó passa a ser o topo da pilha
    p->topo = novo;
    printf("[+] Empilhado: %d\n", valor);
}

int desempilhar(Pilha *p) {
    // 1. Verifica se a pilha já está vazia
    if (p->topo == NULL) {
        printf("[!] Erro: Pilha Vazia\n");
        return -1;
    }

    // 2. Cria variável auxiliar para guardar o nó que será removido
    Elemento *aux = p->topo;
    int valor = aux->num;

    // 3. O topo passa a ser o próximo elemento
    p->topo = p->topo->prox;

    free(aux); // Libera a memória do nó removido
    printf("[-] Removido: %d\n", valor);
    return valor;
}

// Retorna o elemento do topo sem remover
void consultarTopo(Pilha *p) {
    // 1. Checa se a pilha está vazia
    if (p->topo == NULL) {
        printf("[i] Pilha vazia!\n");
    } else {
        // 2. Imprime o valor do topo da pilha
        printf("[i] Topo: %d\n", p->topo->num);
    }
}

void imprimirPilha(Pilha *p) {
    // 1. Checa se a pilha está vazia
    if (p->topo == NULL) {
        printf("Pilha: [ VAZIA ]\n\n");
        return;
    }

    // 2. Cria um ponteiro temporário para não perder a referência do topo
    Elemento *atual = p->topo;
    printf("Pilha: [ TOPO ] ");

    // 3. Percorre toda a pilha imprimindo os elementos
    while (atual != NULL) {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("NULL [ BASE ]\n\n");
}

// Percorre a pilha contando os elementos
int tamanhoPilha(Pilha *p) {
    // 1. Cria um contador e um ponteiro auxiliar para percorrer a pilha
    int contador = 0;
    Elemento *atual = p->topo;

    // 2. Loop para passar pelos elementos
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    return contador;
}

int main() {
    Pilha *minhaPilha = criarPilha();

    printf("=======================================\n");
    printf("    DEMONSTRACAO COMPLETA DE PILHA     \n");
    printf("=======================================\n\n");

    // 1. Inserindo elementos
    empilhar(minhaPilha, 10);
    empilhar(minhaPilha, 20);
    empilhar(minhaPilha, 30);
    imprimirPilha(minhaPilha);

    // 2. Consultando tamanho e o topo
    printf("Tamanho atual da pilha: %d\n", tamanhoPilha(minhaPilha));
    consultarTopo(minhaPilha);
    printf("\n");

    // 3. Removendo um elemento
    desempilhar(minhaPilha);
    imprimirPilha(minhaPilha);

    // 4. Nova consulta de topo e tamanho
    printf("Tamanho atual da pilha: %d\n", tamanhoPilha(minhaPilha));
    consultarTopo(minhaPilha);
    printf("\n");

    // 5. Esvaziando a pilha completamente
    desempilhar(minhaPilha);
    desempilhar(minhaPilha);
    imprimirPilha(minhaPilha);

    // 6. Tentando remover de uma pilha vazia (Tratamento de erro)
    desempilhar(minhaPilha);

    return 0;
}
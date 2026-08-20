#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int valor;
    struct No* proximo;
} No;

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

void imprimirLista(No* head) {
    No* atual = head;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void liberarLista(No* head) {
    No* temp;
    while (head != NULL) {
        temp = head;
        head = head->proximo;
        free(temp);
    }
}

// =============================================================================
// BUBBLE SORT ORIGINAL (LISTA)
// =============================================================================
void bubbleSortOriginal(No** head, int tamanho, bool crescente, int *comparacoes, int *trocas) {
    if (head == NULL || *head == NULL) return;
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; ++i) {
        No** atual = head;

        while ((*atual) != NULL && (*atual)->proximo != NULL) {
            No* p1 = *atual;
            No* p2 = p1->proximo;
            bool deveTrocar = false;

            (*comparacoes)++; // Mede cada teste condicional de ordem
            if (crescente) {
                if (p1->valor > p2->valor) deveTrocar = true;
            } else {
                if (p1->valor < p2->valor) deveTrocar = true;
            }

            if (deveTrocar) {
                p1->proximo = p2->proximo;
                p2->proximo = p1;
                *atual = p2;
                (*trocas)++; // Mede o reajuste de ponteiros
            }

            atual = &((*atual)->proximo);
        }
    }
}

// =============================================================================
// BUBBLE SORT 1ª MELHORIA (LISTA)
// =============================================================================
void bubbleSortMelhoria1(No** head, int tamanho, bool crescente, int *comparacoes, int *trocas) {
    if (head == NULL || *head == NULL) return;
    *comparacoes = 0;
    *trocas = 0;
    No* fim = NULL;

    for (int i = 0; i < tamanho - 1; ++i) {
        No** atual = head;

        while ((*atual)->proximo != fim) {
            No* p1 = *atual;
            No* p2 = p1->proximo;
            bool deveTrocar = false;

            (*comparacoes)++;
            if (crescente) {
                if (p1->valor > p2->valor) deveTrocar = true;
            } else {
                if (p1->valor < p2->valor) deveTrocar = true;
            }

            if (deveTrocar) {
                p1->proximo = p2->proximo;
                p2->proximo = p1;
                *atual = p2;
                (*trocas)++;
            }

            atual = &((*atual)->proximo);
        }
        fim = *atual;
    }
}

// =============================================================================
// BUBBLE SORT 2ª MELHORIA (LISTA)
// =============================================================================
void bubbleSortMelhoria2(No** head, int tamanho, bool crescente, int *comparacoes, int *trocas) {
    if (head == NULL || *head == NULL) return;
    *comparacoes = 0;
    *trocas = 0;
    No* fim = NULL;

    for (int i = 0; i < tamanho - 1; ++i) {
        bool houveTroca = false;
        No** atual = head;

        while ((*atual)->proximo != fim) {
            No* p1 = *atual;
            No* p2 = p1->proximo;
            bool deveTrocar = false;

            (*comparacoes)++;
            if (crescente) {
                if (p1->valor > p2->valor) deveTrocar = true;
            } else {
                if (p1->valor < p2->valor) deveTrocar = true;
            }

            if (deveTrocar) {
                p1->proximo = p2->proximo;
                p2->proximo = p1;
                *atual = p2;
                houveTroca = true;
                (*trocas)++;
            }

            atual = &((*atual)->proximo);
        }
        fim = *atual;

        if (!houveTroca) break;
    }
}

// =============================================================================
// INSERTION SORT IN-PLACE (LISTA)
// =============================================================================
void insertionSort(No* head, int tamanho, bool crescente, int *comparacoes, int *atribuicoes) {
    if (head == NULL || head->proximo == NULL) return;
    *comparacoes = 0;
    *atribuicoes = 0;

    No* nos[tamanho];
    No* percorre = head;
    for (int k = 0; k < tamanho; ++k) {
        nos[k] = percorre;
        percorre = percorre->proximo;
    }

    for (int i = 1; i < tamanho; ++i) {
        int chave = nos[i]->valor;
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++; // Mede a verificação da condição do laço
            
            bool condição = crescente ? (nos[j]->valor > chave) : (nos[j]->valor < chave);
            if (!condição) break;

            nos[j + 1]->valor = nos[j]->valor; // Deslocamento
            (*atribuicoes)++;
            j--;
        }

        nos[j + 1]->valor = chave;
        (*atribuicoes)++; // Atribuição final da chave na posição correta
    }
}

// =============================================================================
// TESTES E COMPARATIVO PEDAGÓGICO
// =============================================================================
No* criarListaTeste() {
    No* head = criarNo(5);
    head->proximo = criarNo(8);
    head->proximo->proximo = criarNo(2);
    head->proximo->proximo->proximo = criarNo(1);
    head->proximo->proximo->proximo->proximo = criarNo(8);
    return head;
}

int main() {
    int n = 5;
    int comp, trocas;

    printf("=== COMPARATIVO DE OPERACOES (Vetor Entrada: [5 8 2 1 8]) ===\n\n");

    No* l1 = criarListaTeste();
    bubbleSortOriginal(&l1, n, true, &comp, &trocas);
    printf("[Bubble Original]  Comparacoes: %2d | Trocas de ponteiro: %2d | Resultado: ", comp, trocas);
    imprimirLista(l1);
    liberarLista(l1);

    No* l2 = criarListaTeste();
    bubbleSortMelhoria1(&l2, n, true, &comp, &trocas);
    printf("[Bubble 1a Melh.] Comparacoes: %2d | Trocas de ponteiro: %2d | Resultado: ", comp, trocas);
    imprimirLista(l2);
    liberarLista(l2);

    No* l3 = criarListaTeste();
    bubbleSortMelhoria2(&l3, n, true, &comp, &trocas);
    printf("[Bubble 2a Melh.] Comparacoes: %2d | Trocas de ponteiro: %2d | Resultado: ", comp, trocas);
    imprimirLista(l3);
    liberarLista(l3);

    No* l4 = criarListaTeste();
    insertionSort(l4, n, true, &comp, &trocas);
    printf("[Insertion Sort]  Comparacoes: %2d | Atribuicoes/Copias: %2d | Resultado: ", comp, trocas);
    imprimirLista(l4);
    liberarLista(l4);

    return 0;
}
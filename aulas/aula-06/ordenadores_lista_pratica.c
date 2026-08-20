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
// 1. BUBBLE SORT ORIGINAL
// =============================================================================
int bubbleSortOriginal(No** head, int tamanho, bool crescente, int *comparacoes, int *trocas) {
    if (head == NULL || *head == NULL) return;
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; ++i) {
        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirLista(*head);

        No** atual = head;

        while ((*atual) != NULL && (*atual)->proximo != NULL) {
            No* p1 = *atual;
            No* p2 = p1->proximo;
            bool deveTrocar = false;

            (*comparacoes)++; // Mede o teste de ordem de elementos
            if (crescente) {
                if (p1->valor > p2->valor) deveTrocar = true;
            } else {
                if (p1->valor < p2->valor) deveTrocar = true;
            }

            if (deveTrocar) {
                printf("Trocando %d e %d\n", p1->valor, p2->valor);
                p1->proximo = p2->proximo;
                p2->proximo = p1;
                *atual = p2;
                (*trocas)++; // Mede a reordenação física de ponteiros
                imprimirLista(*head);
            } else {
                printf("Sem troca entre %d e %d\n", p1->valor, p2->valor);
            }

            atual = &((*atual)->proximo);
        }
    }
    printf("\n--- FIM DA ORDENACAO ---");
    printf("\n[Resumo] Comparacoes: %d | Trocas: %d\n\n", *comparacoes, *trocas);
    return *comparacoes, *trocas;
}


// =============================================================================
// 2. BUBBLE SORT 1ª MELHORIA (Limite 'fim')
// =============================================================================
void bubbleSortMelhoria1(No** head, int tamanho, bool crescente, int *comparacoes, int *trocas) {
    if (head == NULL || *head == NULL) return;
    *comparacoes = 0;
    *trocas = 0;

    No* fim = NULL;

    for (int i = 0; i < tamanho - 1; ++i) {
        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirLista(*head);

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
                printf("Trocando %d e %d\n", p1->valor, p2->valor);
                p1->proximo = p2->proximo;
                p2->proximo = p1;
                *atual = p2;
                (*trocas)++;
                imprimirLista(*head);
            } else {
                printf("Sem troca entre %d e %d\n", p1->valor, p2->valor);
            }

            atual = &((*atual)->proximo);
        }
        fim = *atual;
    }
    printf("\n--- FIM DA ORDENACAO ---");
    printf("\n[Resumo] Comparacoes: %d | Trocas: %d\n\n", *comparacoes, *trocas);
}

// =============================================================================
// 3. BUBBLE SORT 2ª MELHORIA (Limite 'fim' + Flag 'houveTroca')
// =============================================================================
void bubbleSortMelhoria2(No** head, int tamanho, bool crescente, int *comparacoes, int *trocas) {
    if (head == NULL || *head == NULL) return;
    *comparacoes = 0;
    *trocas = 0;

    No* fim = NULL;

    for (int i = 0; i < tamanho - 1; ++i) {
        bool houveTroca = false;

        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirLista(*head);

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
                printf("Trocando %d e %d\n", p1->valor, p2->valor);
                p1->proximo = p2->proximo;
                p2->proximo = p1;
                *atual = p2;

                houveTroca = true;
                (*trocas)++;
                imprimirLista(*head);
            } else {
                printf("Sem troca entre %d e %d\n", p1->valor, p2->valor);
            }

            atual = &((*atual)->proximo);
        }
        fim = *atual;

        if (!houveTroca) {
            printf("Nenhuma troca realizada na passada %d. Vetor ja ordenado!\n", i + 1);
            break;
        }
    }
    printf("\n--- FIM DA ORDENACAO ---");
    printf("\n[Resumo] Comparacoes: %d | Trocas: %d\n\n", *comparacoes, *trocas);
}

// =============================================================================
// 4. INSERTION SORT IN-PLACE
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

        printf("\nPasso i = %d, chave = %d\n", i, chave);
        printf("Vetor antes da insercao: \n");
        imprimirLista(head);

        while (j >= 0) {
            (*comparacoes)++; // Mede cada teste de comparação da chave
            
            bool condição = crescente ? (nos[j]->valor > chave) : (nos[j]->valor < chave);
            if (!condição) break;

            nos[j + 1]->valor = nos[j]->valor; // Desloca para a direita (Atribuição)
            (*atribuicoes)++;
            
            printf("Deslocando %d para a posicao %d\n", nos[j]->valor, j + 1);
            imprimirLista(head);
            j = j - 1;
        }

        printf("Inserindo chave %d na posicao %d\n", chave, j + 1);
        nos[j + 1]->valor = chave;
        (*atribuicoes)++; // Mede o encaixe final da chave (Atribuição)
        imprimirLista(head);
    }
    printf("\n--- FIM DA ORDENACAO ---");
    printf("\n[Resumo] Comparacoes: %d | Atribuicoes (Copias): %d\n\n", *comparacoes, *atribuicoes);
}

// =============================================================================
// MAIN E CRIADOR DE LISTAS
// =============================================================================
No* criarLista() {
    No* head = criarNo(5);
    head->proximo = criarNo(8);
    head->proximo->proximo = criarNo(2);
    head->proximo->proximo->proximo = criarNo(1);
    head->proximo->proximo->proximo->proximo = criarNo(8);
    return head;
}

int main() {
    int n = 5;
    int comp, op;

    printf("================= BUBBLE SORT ORIGINAL =================\n");
    No* t1 = criarLista();
    comp,op=bubbleSortOriginal(&t1, n, true, &comp, &op);
    printf("Comparacoes: %d | Trocas: %d\n", comp, op);
    liberarLista(t1);

    printf("================= BUBBLE SORT 1a MELHORIA =================\n");
    No* t2 = criarLista();
    bubbleSortMelhoria1(&t2, n, true, &comp, &op);
    liberarLista(t2);

    printf("================= BUBBLE SORT 2a MELHORIA =================\n");
    No* t3 = criarLista();
    bubbleSortMelhoria2(&t3, n, true, &comp, &op);
    liberarLista(t3);

    printf("================= INSERTION SORT IN-PLACE =================\n");
    No* t4 = criarLista();
    insertionSort(t4, n, true, &comp, &op);
    liberarLista(t4);

    return 0;
}
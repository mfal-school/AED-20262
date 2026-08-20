#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int valor;
    struct No* proximo;
} No;

typedef struct {
    int comparacoes;
    int trocas; // No Insertion Sort, representa atribuições/cópias
} Estatisticas;

// =============================================================================
// FUNÇÕES AUXILIARES DE LISTA
// =============================================================================
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

// Cria uma cópia independente da lista para evitar contaminação entre testes
No* copiarLista(No* head) {
    if (head == NULL) return NULL;
    No* novaHead = criarNo(head->valor);
    No* atualOrigem = head->proximo;
    No* atualDestino = novaHead;

    while (atualOrigem != NULL) {
        atualDestino->proximo = criarNo(atualOrigem->valor);
        atualDestino = atualDestino->proximo;
        atualOrigem = atualOrigem->proximo;
    }
    return novaHead;
}

// =============================================================================
// ALGORITMOS DE ORDENAÇÃO
// =============================================================================
Estatisticas bubbleSortOriginal(No** head, int tamanho, bool crescente) {
    Estatisticas est = {0, 0};
    if (head == NULL || *head == NULL) return est;

    for (int i = 0; i < tamanho - 1; ++i) {
        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirLista(*head);

        No** atual = head;

        while ((*atual) != NULL && (*atual)->proximo != NULL) {
            No* p1 = *atual;
            No* p2 = p1->proximo;
            bool deveTrocar = false;

            est.comparacoes++;
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
                est.trocas++;
                imprimirLista(*head);
            } else {
                printf("Sem troca entre %d e %d\n", p1->valor, p2->valor);
            }

            atual = &((*atual)->proximo);
        }
    }
    printf("--- FIM DA ORDENACAO ---\n");
    return est;
}

Estatisticas bubbleSortMelhoria1(No** head, int tamanho, bool crescente) {
    Estatisticas est = {0, 0};
    if (head == NULL || *head == NULL) return est;

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

            est.comparacoes++;
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
                est.trocas++;
                imprimirLista(*head);
            } else {
                printf("Sem troca entre %d e %d\n", p1->valor, p2->valor);
            }

            atual = &((*atual)->proximo);
        }
        fim = *atual;
    }
    printf("--- FIM DA ORDENACAO ---\n");
    return est;
}

Estatisticas bubbleSortMelhoria2(No** head, int tamanho, bool crescente) {
    Estatisticas est = {0, 0};
    if (head == NULL || *head == NULL) return est;

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

            est.comparacoes++;
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
                est.trocas++;
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
    printf("--- FIM DA ORDENACAO ---\n");
    return est;
}

Estatisticas insertionSort(No* head, int tamanho, bool crescente) {
    Estatisticas est = {0, 0};
    if (head == NULL || head->proximo == NULL) return est;

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
            est.comparacoes++;

            bool precisaDeslocar;
            if (crescente) {
                precisaDeslocar = (nos[j]->valor > chave);
            } else {
                precisaDeslocar = (nos[j]->valor < chave);
            }

            if (!precisaDeslocar) {
                break;
            }

            nos[j + 1]->valor = nos[j]->valor;
            est.trocas++; // Contabiliza atribuição/deslocamento
            
            printf("Deslocando %d para a posicao %d\n", nos[j]->valor, j + 1);
            imprimirLista(head);
            j = j - 1;
        }

        printf("Inserindo chave %d na posicao %d\n", chave, j + 1);
        nos[j + 1]->valor = chave;
        est.trocas++; // Contabiliza a atribuição final da chave
        imprimirLista(head);
    }
    printf("--- FIM DA ORDENACAO ---\n");
    return est;
}

// =============================================================================
// FUNÇÃO DE AVALIAÇÃO DO CENÁRIO
// =============================================================================
void avaliarCenario(const char *nomeCenario, No *listaBase, int tamanho) {
    printf("\n=========================================================\n");
    printf(" %s\n", nomeCenario);
    printf("=========================================================\n");

    // 1. Bubble Sort Original
    printf("\n--- 1. BUBBLE SORT ORIGINAL ---\n");
    No *t1 = copiarLista(listaBase);
    Estatisticas e1 = bubbleSortOriginal(&t1, tamanho, true);
    liberarLista(t1);

    // 2. Bubble Sort 1ª Melhoria
    printf("\n--- 2. BUBBLE SORT 1a MELHORIA ---\n");
    No *t2 = copiarLista(listaBase);
    Estatisticas e2 = bubbleSortMelhoria1(&t2, tamanho, true);
    liberarLista(t2);

    // 3. Bubble Sort 2ª Melhoria
    printf("\n--- 3. BUBBLE SORT 2a MELHORIA ---\n");
    No *t3 = copiarLista(listaBase);
    Estatisticas e3 = bubbleSortMelhoria2(&t3, tamanho, true);
    liberarLista(t3);

    // 4. Insertion Sort In-Place
    printf("\n--- 4. INSERTION SORT IN-PLACE ---\n");
    No *t4 = copiarLista(listaBase);
    Estatisticas e4 = insertionSort(t4, tamanho, true);
    liberarLista(t4);

    // Tabela de Resumo do Cenário
    printf("\n---------------------------------------------------------\n");
    printf("              RESUMO METRICAS: %s\n", nomeCenario);
    printf("---------------------------------------------------------\n");
    printf("%-22s | %-12s | %-16s\n", "Algoritmo", "Comparacoes", "Trocas/Atribuicoes");
    printf("---------------------------------------------------------\n");
    printf("%-22s | %-12d | %-16d\n", "Bubble Sort Original", e1.comparacoes, e1.trocas);
    printf("%-22s | %-12d | %-16d\n", "Bubble Sort (1a Melh.)", e2.comparacoes, e2.trocas);
    printf("%-22s | %-12d | %-16d\n", "Bubble Sort (2a Melh.)", e3.comparacoes, e3.trocas);
    printf("%-22s | %-12d | %-16d\n", "Insertion Sort", e4.comparacoes, e4.trocas);
    printf("---------------------------------------------------------\n");
}

// =============================================================================
// ENTRADA DO USUÁRIO E GERAÇÃO DOS CENÁRIOS 
// =============================================================================
No* lerListaDoUsuario(int *tamanho) {
    int n, valor;
    No *head = NULL;
    No *tail = NULL;

    printf("Digite a quantidade de elementos (N): ");
    scanf("%d", &n);

    *tamanho = n;
    printf("Digite os %d elementos da lista (separados por espaco):\n", n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &valor);
        No *novo = criarNo(valor);
        if (head == NULL) {
            head = novo;
            tail = novo;
        } else {
            tail->proximo = novo;
            tail = novo;
        }
    }
    return head;
}

int main() {
    int n = 0;

    // 1. Leitura da lista inicial fornecida pelo aluno
    No *cenarioConvencional = lerListaDoUsuario(&n);

    // Os passos 2 e 3 foram implementados só para não exigir 3 leituras de listas do usuário! Caso precisa, é só ler três vezes e armazenar em 3 listas.
    // 2. Criação do Pior Cenário (Lista Invertida com base na entrada)
    No *cenarioPior = copiarLista(cenarioConvencional);
    Estatisticas aux;
    bubbleSortOriginal(&cenarioPior, n, false); // Ordena de forma decrescente (invertida)

    // 3. Criação do Melhor Cenário (Lista Ordenada com base na entrada)
    No *cenarioMelhor = copiarLista(cenarioConvencional);
    bubbleSortOriginal(&cenarioMelhor, n, true); // Ordena de forma crescente

    // 4. Execução dos testes e exibição limpa
    system("clear || cls"); // Limpa a tela para organizar a apresentação dos resultados

    avaliarCenario("CENARIO 1: Melhor Caso (Lista Ja Ordenada)", cenarioMelhor, n);
    avaliarCenario("CENARIO 2: Caso Convencional (Entrada do Usuario)", cenarioConvencional, n);
    avaliarCenario("CENARIO 3: Pior Caso (Lista em Ordem Inversa)", cenarioPior, n);

    // 5. Liberação da memória alocada
    liberarLista(cenarioConvencional);
    liberarLista(cenarioMelhor);
    liberarLista(cenarioPior);

    return 0;
}
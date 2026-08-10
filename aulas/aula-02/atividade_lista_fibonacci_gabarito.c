#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

// Inserção no início: O(1)
void inserirInicio(Node **head, int n) {
    Node *novo = (Node *) malloc(sizeof(Node));
    if (novo != NULL) {
        novo->valor = n;
        novo->prox = *head;
        *head = novo;
    }
}

// Inserção no fim CONVENCIONAL: O(n) por chamada
void inserirFimConvencional(Node **head, int n) {
    Node *novo = (Node *) malloc(sizeof(Node));
    if (novo == NULL) return;

    novo->valor = n;
    novo->prox = NULL;

    if (*head == NULL) {
        *head = novo;
        return;
    }

    Node *atual = *head;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
}

void imprimir(Node *head) {
    Node *atual = head;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL \n");
}

int tamanho(Node *head) {
    int contador = 0;
    while (head != NULL) {
        head = head->prox;
        contador++;
    }
    return contador;
}

void remover(Node **head) {
    if (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->prox;
        free(temp);
    }
}

int removerPosicao(Node **head, int posicao) {
    if (*head == NULL || posicao < 0) {
        printf("Posicao invalida ou lista vazia.\n");
        return -1;
    }

    if (posicao == 0) {
        Node *temp = *head;
        int valor = temp->valor;
        *head = temp->prox;
        free(temp);
        return valor;
    }

    Node *anterior = *head;
    for (int i = 0; i < posicao - 1 && anterior->prox != NULL; i++) {
        anterior = anterior->prox;
    }

    if (anterior->prox == NULL) {
        printf("Posicao invalida (fora do tamanho da lista).\n");
        return -1;
    }

    Node *alvo = anterior->prox;
    int valor = alvo->valor;
    anterior->prox = alvo->prox;
    free(alvo);
    return valor;
}

// ---------- main ----------

int main(void) {
    Node *head = NULL;
    int n, opcao;

    printf("Quantos numeros da sequencia de Fibonacci deseja gerar? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Valor invalido.\n");
        return 1;
    }

    printf("\nComo deseja inserir na lista?\n");
    printf("1 - No inicio (Ordem Inversa: ex. 2, 1, 1, 0)\n");
    printf("2 - No fim Convencional (Ordem Direta: ex. 0, 1, 1, 2)\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        if (opcao == 1) {
            inserirInicio(&head, a);
        } else {
            inserirFimConvencional(&head, a); // Percorre a lista toda a cada elemento
        }
        
        int prox = a + b;
        a = b;
        b = prox;
    }

    printf("\nLista ANTES da remocao:\n");
    imprimir(head);
    printf("Tamanho: %d\n", tamanho(head));

    // Removendo o primeiro elemento
    remover(&head);

    printf("\nLista DEPOIS da remocao (removido o primeiro):\n");
    imprimir(head);
    printf("Tamanho: %d\n", tamanho(head));

    // Desafio de remoção por posição
    if (tamanho(head) >= 3) {
        printf("\n Indique o elemento para remover (0 para o primeiro, 1 para o segundo, etc.): ");
        int posicaoRemover;
        scanf("%d", &posicaoRemover);
        int valorRemovido = removerPosicao(&head, posicaoRemover);
        printf("\nValor removido na posicao %d: %d\n", posicaoRemover, valorRemovido);
        printf("Lista apos remocao por posicao:\n");
        imprimir(head);
        printf("Tamanho: %d\n", tamanho(head));
    }

    return 0;
}
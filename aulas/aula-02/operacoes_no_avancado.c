#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

// Cria um novo nó com o valor informado
Node *criar_no(int valor) {
    Node *novo = (Node *) malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Insere um novo valor no início da lista
void inserir(Node **head, int n) {
    Node *novo = (Node *) malloc(sizeof(Node));
    if (novo != NULL) {
        novo->valor = n;
        novo->prox = *head;
        *head = novo;   // atualiza o head para apontar para o novo nó
    }
}

// Insere um novo valor na posição indicada (0 = início da lista)
// Retorna 1 se conseguiu inserir, 0 se a posição for inválida
int inserir_na_posicao(Node **head, int n, int pos) {
    if (pos < 0) {
        return 0; // posição inválida
    }

    // Caso especial: inserir no início é igual à função inserir()
    if (pos == 0) {
        Node *novo = criar_no(n);
        novo->prox = *head;
        *head = novo;
        return 1;
    }

    // Percorremos até o nó ANTERIOR à posição desejada
    Node *anterior = *head;
    for (int i = 0; i < pos - 1 && anterior != NULL; i++) {
        anterior = anterior->prox;
    }

    // Se anterior for NULL, a posição pedida está além do fim da lista
    if (anterior == NULL) {
        return 0;
    }

    Node *novo = criar_no(n);
    novo->prox = anterior->prox;
    anterior->prox = novo;
    return 1;
}

// Remove o nó na posição indicada (0 = início da lista)
// Retorna 1 se conseguiu remover, 0 se a posição for inválida
int remover_na_posicao(Node **head, int pos) {
    if (pos < 0 || *head == NULL) {
        return 0; // posição inválida ou lista vazia
    }

    Node *removido;

    // Caso especial: remover o início da lista
    if (pos == 0) {
        removido = *head;
        *head = (*head)->prox;
        free(removido);
        return 1;
    }

    // Percorremos até o nó ANTERIOR à posição desejada
    Node *anterior = *head;
    for (int i = 0; i < pos - 1 && anterior->prox != NULL; i++) {
        anterior = anterior->prox;
    }

    // Se não há nó na posição pedida, é inválida
    if (anterior->prox == NULL) {
        return 0;
    }

    removido = anterior->prox;
    anterior->prox = removido->prox;
    free(removido);
    return 1;
}

// Imprime todos os valores da lista, do início ao fim
void imprimir(Node *head) {
    Node *atual = head;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

// Libera toda a memória alocada pela lista
void liberar(Node *head) {
    Node *atual = head;
    while (atual != NULL) {
        Node *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int main() {
    Node *head = NULL;  // lista começa vazia

    inserir(&head, 10);
    inserir(&head, 20);
    inserir(&head, 30);

    imprimir(head);  // esperado: 30 20 10

    inserir_na_posicao(&head, 99, 2);
    printf("Apos inserir 99 na posicao 2:\n");
    imprimir(head);  // esperado: 30 20 99 10

    remover_na_posicao(&head, 2);
    printf("Apos remover a posicao 2:\n");
    imprimir(head);  // esperado: 30 20 10

    liberar(head);
    return 0;
}
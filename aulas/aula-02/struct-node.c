#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

Node *criar_no(int valor) {
    Node *novo = (Node *) malloc(sizeof(Node)); //reservando espaço para um nó
    if (novo == NULL) {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novo->valor = valor; //igual a (*novo).valor = valor;
    novo->prox = NULL; //igual a (*novo).prox = NULL;
    return novo;
}

int main(void) {
    Node *inicio = criar_no(10);
    inicio->prox = criar_no(20);
    printf("Primeiro no: %d\n", inicio->valor);
    printf("\nEndereco do primeiro no: %p\n", (void *)inicio);

    printf("\nSegundo no: %d\n", inicio->prox->valor);
    printf("\nEndereco do segundo no: %p\n", (void *)inicio->prox);   

    return 0;
}

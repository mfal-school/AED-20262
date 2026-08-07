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

// Imprime todos os valores da lista, do início ao fim
void imprimir(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->valor);
        head = head->prox;  
    }
    printf("NULL\n");
}

// Calcula o tamanho da lista encadeada
int tamanho(Node *head) {
	int contador = 0;
	while (head != NULL) {
		head = head-> prox;
		contador++;
	}
	return contador;
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

// Remove o primeiro nó da lista
void remover(Node **head) {
    if (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->prox;
        free(temp);
    }
}

// Remove o primeiro nó da lista e retorna seu valor
int remover_e_retornar(Node **head) {
    int valor = 0;
    if (*head != NULL) {
        valor = (*head)->valor;
        Node *temp = *head;
        *head = (*head)->prox;
        free(temp);
    }
    return valor;
}

int main() {
    Node *head = NULL;  // lista começa vazia

    inserir(&head, 10);
    inserir(&head, 20);
    inserir(&head, 30);
    inserir(&head, 40);
    inserir(&head, 50);

    printf("Tamanho da lista: %d\n", tamanho(head));  // esperado: 3
    imprimir(head); 

    printf("Removendo o primeiro nó...\n");
    int valor_removido = remover_e_retornar(&head);
    printf("Valor removido: %d\n", valor_removido); 

    printf("Tamanho da lista após remoção: %d\n", tamanho(head));  // esperado: 2
    imprimir(head); 

    liberar(head);
    return 0;
}
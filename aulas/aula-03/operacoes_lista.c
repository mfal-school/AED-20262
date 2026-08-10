#include <stdio.h>
#include <stdlib.h>

// 1. O Nó da Fila (cada elemento individual)
typedef struct Elemento {
    int num;
    struct Elemento *prox;
} Elemento;

// 2. O Controlador da Fila
typedef struct Fila {
    Elemento *inicio;
    Elemento *fim;
} Fila;

// 3. Função para criar uma fila vazia na memória
Fila* criarFila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enfileirar(Fila *f, int valor) {
    // 1. Criar e preparar o novo nó
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->num = valor;
    novo->prox = NULL;

    // 2. Se a fila estiver vazia, o novo nó é o início
    if (f->inicio == NULL) {
        f->inicio = novo;
    } else {
        // Caso contrário, insere no antigo fim
        f->fim->prox = novo;
    }

    // 3. O novo nó passa a ser sempre o fim da fila
    f->fim = novo;
    printf("[+] Inserido: %d\n", valor);
}

int desenfileirar(Fila *f) {
    // 1. Verifica se a fila já está vazia
    if (f->inicio == NULL) {
        printf("[!] Erro: Fila Vazia\n");
        return -1;
    }

    // 2. Cria variável auxiliar para guardar o nó que será removido
    Elemento *aux = f->inicio;
    int valor = aux->num;

    // 3. Remove o primeiro valor da fila
    // O inicio move para o proximo elemento
    f->inicio = f->inicio->prox;

    // Se o inicio virou NULL, a fila esvaziou totalmente
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(aux); // Libera a memória do nó removido
    printf("[-] Removido: %d\n", valor);
    return valor;
}

// Retorna o primeiro elemento sem remover
void consultarInicio(Fila *f) {
    //1. Checa se a fila está vazia
    if (f->inicio == NULL) {
        printf("[i] Fila vazia!\n");
    } else {
        // 2. Imprime o valor do primeiro elemento da fila
        printf("[i] Primeiro elemento: %d\n", f->inicio->num);
    }
}

void imprimirFila(Fila *f) {
    // 1. Checa se a fila está vazia
    if (f->inicio == NULL) {
        printf("Fila: [ VAZIA ]\n\n");
        return;
    }

    // 2. Cria um ponteiro temporário para não perder a referência do início da fila
    Elemento *atual = f->inicio;
    printf("Fila: [ INICIO ] ");

    // 3. Percorre toda a fila imprimindo os elementos
    while (atual != NULL) {
        printf("%d -> ", atual->num);
        atual = atual->prox;
    }
    printf("NULL [ FIM ]\n\n");
}

// Percorre a fila contando os elementos
int tamanhoFila(Fila *f) {
    // 1. Cria um contador e um ponteiro auxiliar para percorrer a fila
    int contador = 0;
    Elemento *atual = f->inicio;

    // 2. Loop para passar pelos elementos
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    return contador;
}

int main() {
    Fila *minhaFila = criarFila();

    printf("=======================================\n");
    printf("     DEMONSTRACAO COMPLETA DE FILA     \n");
    printf("=======================================\n\n");

    // 1. Inserindo elementos
    enfileirar(minhaFila, 10);
    enfileirar(minhaFila, 20);
    enfileirar(minhaFila, 30);
    imprimirFila(minhaFila);

    // 2. Consultando tamanho e o primeiro elemento
    printf("Tamanho atual da fila: %d\n", tamanhoFila(minhaFila));
    consultarInicio(minhaFila);
    printf("\n");

    // 3. Removendo um elemento (atendimento)
    desenfileirar(minhaFila);
    imprimirFila(minhaFila);

    // 4. Nova consulta de inicio e tamanho
    printf("Tamanho atual da fila: %d\n", tamanhoFila(minhaFila));
    consultarInicio(minhaFila);
    printf("\n");

    // 5. Esvaziando a fila completamente
    desenfileirar(minhaFila);
    desenfileirar(minhaFila);
    imprimirFila(minhaFila);

    // 6. Tentando remover de uma fila vazia (Tratamento de erro)
    desenfileirar(minhaFila);

    return 0;
}
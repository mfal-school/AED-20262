#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LIMITE_TOTAL 10
#define LIMITE_MEIA 5

typedef struct Usuario {
    int id;
    char nome[50];
    bool isFan;
    struct Usuario *prox;
} Usuario;

typedef struct Fila {
    Usuario *inicio;
    Usuario *fim;
    int tamanho;
} Fila;

typedef struct {
    int totalVendidos;
    int meiasVendidas;
} Bilheteria;

Fila* criarFila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int id, const char *nome, bool isFan) {
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->isFan = isFan;
    novo->prox = NULL;

    int pessoasAFrente = f->tamanho;

    if (f->inicio == NULL) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;

    printf("\n===================================================\n");
    printf("[+] BEM-VINDO(A), %s!\n", novo->nome);
    printf("    ID do Usuario: %d (%s)\n", novo->id, novo->isFan ? "Membro Fa-Clube" : "Publico Geral");
    printf("    -> Ha exatamente %d pessoas a sua frente na fila.\n", pessoasAFrente);
    printf("===================================================\n");
}

void atenderProximo(Fila *f, Bilheteria *b, int tipoIngresso) {
    if (f->inicio == NULL) {
        printf("\n[!] Nao ha ninguem na fila para ser atendido!\n");
        return;
    }

    if (b->totalVendidos >= LIMITE_TOTAL) {
        printf("\n[X] INGRESSOS TOTALMENTE ESGOTADOS!\n");
        return;
    }

    if (tipoIngresso == 2 && b->meiasVendidas >= LIMITE_MEIA) {
        printf("\n[!] A cota de meia-entrada (%d) já esgotou!\n", LIMITE_MEIA);
        printf("    O atendimento foi cancelado. Escolha Inteira para prosseguir.\n");
        printf("Escolha o tipo de ingresso (1 - Inteira / 2 - Meia): ");
        scanf("%d", &tipoIngresso);
        return;
    }

    Usuario *atendido = f->inicio;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    f->tamanho--;

    b->totalVendidos++;
    if (tipoIngresso == 2) {
        b->meiasVendidas++;
    }

    printf("\n[-] ATENDIMENTO CONCLUIDO COM SUCESSO:\n");
    printf("    Usuario: %s (ID: %d)\n", atendido->nome, atendido->id);
    printf("    Tipo de Ingresso: %s\n", (tipoIngresso == 2) ? "Meia-Entrada" : "Inteira");
    printf("    Ingressos Vendidos: %d/%d (Meias: %d/%d)\n", 
            b->totalVendidos, LIMITE_TOTAL, b->meiasVendidas, LIMITE_MEIA);

    free(atendido);
}

void imprimirFila(Fila *f) {
    if (f->inicio == NULL) {
        printf("\n[i] Estado da Fila: [ VAZIA ]\n");
        return;
    }

    printf("\n--- ESTADO ATUAL DA FILA (%d pessoas) ---\n", f->tamanho);
    Usuario *atual = f->inicio;
    int pos = 1;

    while (atual != NULL) {
        printf("  %dº lugar -> ID: %d | Fã: %s\n", 
               pos++, atual->id, atual->isFan ? "Sim" : "Não");
        atual = atual->prox;
    }
    printf("-----------------------------------------\n");
}

int main() {
    Fila *filaVirtual = criarFila();
    Bilheteria bilheteria = {0, 0};

    int opcao;
    int proximoId = 101; // Gerador automático de ID para facilitar

    do {
        printf("\n=======================================\n");
        printf("      BILHETERIA VIRTUAL - SHOW        \n");
        printf("=======================================\n");
        printf("1. Entrar na Fila (Novo Usuario)\n");
        printf("2. Atender Proximo da Fila (Comprar)\n");
        printf("3. Visualizar Fila Atual\n");
        printf("4. Consultar Status dos Ingressos\n");
        printf("0. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' do buffer do teclado

        switch (opcao) {
            case 1: {
                char nome[50];
                int respFan;

                printf("\n--- ENTRADA NA FILA ---\n");
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove a quebra de linha tratada pelo fgets

                printf("Voce eh membro do Fa-Clube? (1 - Sim / 0 - Nao): ");
                scanf("%d", &respFan);

                enfileirar(filaVirtual, proximoId++, nome, respFan == 1);
                break;
            }
            case 2: {
                if (filaVirtual->inicio == NULL) {
                    printf("\n[!] Nao ha usuarios na fila para atendimento!\n");
                    break;
                }

                int tipoIngresso;
                printf("\n--- ATENDIMENTO AO USUARIO: %s ---\n", filaVirtual->inicio->nome);
                printf("Escolha o tipo de ingresso (1 - Inteira / 2 - Meia): ");
                scanf("%d", &tipoIngresso);

                atenderProximo(filaVirtual, &bilheteria, tipoIngresso);
                break;
            }
            case 3:
                imprimirFila(filaVirtual);
                break;

            case 4:
                printf("\n--- PAINEL DE VENDAS ---\n");
                printf("Total Vendido: %d / %d\n", bilheteria.totalVendidos, LIMITE_TOTAL);
                printf("Meias Vendidas: %d / %d\n", bilheteria.meiasVendidas, LIMITE_MEIA);
                break;

            case 0:
                printf("\nEncerrando o sistema da bilheteria...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
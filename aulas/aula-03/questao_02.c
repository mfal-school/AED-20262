#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Limites configuráveis (para os alunos testarem com valores menores na aula)
#define LIMITE_TOTAL 10
#define LIMITE_MEIA 2

// 1. Estrutura do Usuário (Nó)
typedef struct Usuario {
    int id;
    char nome[50];
    bool isFan;
    struct Usuario *prox;
} Usuario;

// 2. Estrutura da Fila
typedef struct Fila {
    Usuario *inicio;
    Usuario *fim;
    int tamanho;
} Fila;

// 3. Estrutura do Estoque da Bilheteria
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

// -------------------------------------------------------------
// OPERAÇÃO: ENFILEIRAR (Com direcionamento por prioridade)
// -------------------------------------------------------------
void enfileirar(Fila *filaFans, Fila *filaGeral, int id, const char *nome, bool isFan) {
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->isFan = isFan;
    novo->prox = NULL;

    int pessoasAFrente = 0;

    // Se for FÃ, vai para a fila preferencial
    if (isFan) {
        pessoasAFrente = filaFans->tamanho;

        if (filaFans->inicio == NULL) {
            filaFans->inicio = novo;
        } else {
            filaFans->fim->prox = novo;
        }
        filaFans->fim = novo;
        filaFans->tamanho++;

    } else { 
        // Se for GERAL, precisa considerar TODOS os fãs + quem já está na fila geral!
        pessoasAFrente = filaFans->tamanho + filaGeral->tamanho;

        if (filaGeral->inicio == NULL) {
            filaGeral->inicio = novo;
        } else {
            filaGeral->fim->prox = novo;
        }
        filaGeral->fim = novo;
        filaGeral->tamanho++;
    }

    printf("\n===================================================\n");
    printf("[+] BEM-VINDO(A), %s!\n", novo->nome);
    printf("    ID: %d | Categoria: %s\n", novo->id, isFan ? "FA-CLUBE (PREFERENCIAL)" : "PUBLICO GERAL");
    printf("    -> Ha exatamente %d pessoas a sua frente na fila.\n", pessoasAFrente);
    printf("===================================================\n");
}

// -------------------------------------------------------------
// OPERAÇÃO: ATENDER PRÓXIMO (Prioridade Total para Fãs)
// -------------------------------------------------------------
void atenderProximo(Fila *filaFans, Fila *filaGeral, Bilheteria *b, int tipoIngresso) {
    // 1. Verifica se AMBAS as filas estão vazias
    if (filaFans->inicio == NULL && filaGeral->inicio == NULL) {
        printf("\n[!] Nao ha ninguém nas filas para atendimento!\n");
        return;
    }

    // 2. Validações do estoque de ingressos
    if (b->totalVendidos >= LIMITE_TOTAL) {
        printf("\n[X] INGRESSOS TOTALMENTE ESGOTADOS!\n");
        return;
    }

    if (tipoIngresso == 2 && b->meiasVendidas >= LIMITE_MEIA) {
        printf("\n[!] A cota de meia-entrada (%d) ja esgotou!\n", LIMITE_MEIA);
        printf("    O atendimento foi cancelado. Escolha Inteira para prosseguir.\n");
        return;
    }

    // 3. Escolhe de qual fila remover: FÃS tem prioridade absoluta!
    Fila *filaAtiva = NULL;
    if (filaFans->inicio != NULL) {
        filaAtiva = filaFans; // Atende o fã-clube primeiro
    } else {
        filaAtiva = filaGeral; // Só atende a geral se a de fãs estiver vazia
    }

    // Remove do início da fila escolhida
    Usuario *atendido = filaAtiva->inicio;
    filaAtiva->inicio = filaAtiva->inicio->prox;

    if (filaAtiva->inicio == NULL) {
        filaAtiva->fim = NULL;
    }
    filaAtiva->tamanho--;

    // Contabiliza a venda
    b->totalVendidos++;
    if (tipoIngresso == 2) {
        b->meiasVendidas++;
    }

    printf("\n[-] ATENDIMENTO CONCLUIDO COM SUCESSO:\n");
    printf("    Usuario: %s (ID: %d) [%s]\n", 
           atendido->nome, atendido->id, atendido->isFan ? "FA-CLUBE" : "GERAL");
    printf("    Tipo de Ingresso: %s\n", (tipoIngresso == 2) ? "Meia-Entrada" : "Inteira");
    printf("    Estoque Atual -> Vendidos: %d/%d (Meias: %d/%d)\n", 
            b->totalVendidos, LIMITE_TOTAL, b->meiasVendidas, LIMITE_MEIA);

    free(atendido);
}

// -------------------------------------------------------------
// IMPRIMIR AMBAS AS FILAS
// -------------------------------------------------------------
void imprimirFilas(Fila *filaFans, Fila *filaGeral) {
    printf("\n===================================================\n");
    printf("            ESTADO DA BILHETERIA VIRTUAL           \n");
    printf("===================================================\n");

    // Fila Preferencial (Fãs)
    printf("--- FILA PREFERENCIAL: FA-CLUBE (%d pessoas) ---\n", filaFans->tamanho);
    if (filaFans->inicio == NULL) {
        printf("  [ VAZIA ]\n");
    } else {
        Usuario *atual = filaFans->inicio;
        int pos = 1;
        while (atual != NULL) {
            printf("  %dº lugar -> ID: %d\n", pos++, atual->id);
            atual = atual->prox;
        }
    }

    // Fila Comum (Geral)
    printf("\n--- FILA COMUM: PUBLICO GERAL (%d pessoas) ---\n", filaGeral->tamanho);
    if (filaGeral->inicio == NULL) {
        printf("  [ VAZIA ]\n");
    } else {
        Usuario *atual = filaGeral->inicio;
        int pos = 1;
        while (atual != NULL) {
            printf("  %dº lugar (Geral) -> ID: %d\n", pos++, atual->id);
            atual = atual->prox;
        }
    }
    printf("===================================================\n");
}

// -------------------------------------------------------------
// MAIN COM MENU INTERATIVO
// -------------------------------------------------------------
int main() {
    Fila *filaFans = criarFila();
    Fila *filaGeral = criarFila();
    Bilheteria bilheteria = {0, 0};

    int opcao;
    int proximoId = 101;

    do {
        printf("\n--- MENU DA BILHETERIA (COM PRIORIDADE) ---\n");
        printf("1. Entrar na Fila (Novo Usuario)\n");
        printf("2. Atender Proximo da Fila (Comprar)\n");
        printf("3. Visualizar Filas\n");
        printf("4. Consultar Status dos Ingressos\n");
        printf("0. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                char nome[50];
                int respFan;

                printf("\nDigite seu nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Voce eh membro do Fa-Clube? (1 - Sim / 0 - Nao): ");
                scanf("%d", &respFan);

                enfileirar(filaFans, filaGeral, proximoId++, nome, respFan == 1);
                break;
            }
            case 2: {
                if (filaFans->inicio == NULL && filaGeral->inicio == NULL) {
                    printf("\n[!] Nao ha usuarios em nenhuma das filas!\n");
                    break;
                }

                // Identifica quem será atendido para mostrar o nome na pergunta
                Usuario *proximo = (filaFans->inicio != NULL) ? filaFans->inicio : filaGeral->inicio;

                int tipoIngresso;
                printf("\n--- ATENDENDO: %s [%s] ---\n", 
                       proximo->nome, proximo->isFan ? "FA-CLUBE" : "GERAL");
                printf("Escolha o tipo de ingresso (1 - Inteira / 2 - Meia): ");
                scanf("%d", &tipoIngresso);

                atenderProximo(filaFans, filaGeral, &bilheteria, tipoIngresso);
                break;
            }
            case 3:
                imprimirFilas(filaFans, filaGeral);
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
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
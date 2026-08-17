#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMITE_HISTORICO 5 //trocar para 20

// 1. O Nó da Pilha (cada ação individual)
typedef struct Acao {
    int id;
    char tipoAcao[20];
    char conteudo[100];
    struct Acao *prox;
} Acao;

// 2. O Controlador do Histórico
typedef struct Historico {
    Acao *topo;
    int quantidade;
} Historico;

// 3. Função para criar um histórico vazio na memória
Historico* criarHistorico() {
    Historico *h = (Historico*) malloc(sizeof(Historico));
    h->topo = NULL;
    h->quantidade = 0;
    return h;
}

// Verifica se o tipo de ação digitado está entre os permitidos
int tipoValido(const char *tipo) {
    const char *tiposPermitidos[] = {"digitar", "apagar", "colar", "formatar"};
    int total = 4;
    for (int i = 0; i < total; i++) {
        if (strcmp(tipo, tiposPermitidos[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Registrar uma nova ação (empilhar)
void registrarAcao(Historico *h, int id, const char *tipo, const char *conteudo) {
    if (h->quantidade >= LIMITE_HISTORICO) {
        printf("[!] Erro: Limite do historico atingido (%d acoes). Nao e possivel registrar.\n",
               LIMITE_HISTORICO);
        return;
    }

    Acao *nova = (Acao*) malloc(sizeof(Acao));
    nova->id = id;
    strncpy(nova->tipoAcao, tipo, sizeof(nova->tipoAcao) - 1);
    nova->tipoAcao[sizeof(nova->tipoAcao) - 1] = '\0';
    strncpy(nova->conteudo, conteudo, sizeof(nova->conteudo) - 1);
    nova->conteudo[sizeof(nova->conteudo) - 1] = '\0';

    // O novo nó aponta para a antiga ação do topo, e passa a ser o novo topo
    nova->prox = h->topo;
    h->topo = nova;
    h->quantidade++;

    printf("[+] Acao registrada: [%s] \"%s\" | Historico: %d/%d\n",
           nova->tipoAcao, nova->conteudo, h->quantidade, LIMITE_HISTORICO);
}

// Desfazer a última ação (desempilhar)
void desfazer(Historico *h) {
    if (h->topo == NULL) {
        printf("[!] Erro: Nao ha acoes para desfazer.\n");
        return;
    }

    Acao *aux = h->topo;
    h->topo = h->topo->prox;
    h->quantidade--;

    printf("[-] Acao desfeita: [%s] \"%s\" | Restam %d acao(oes) no historico\n",
           aux->tipoAcao, aux->conteudo, h->quantidade);

    free(aux);
}

// Consultar qual seria a próxima ação a ser desfeita, sem removê-la
void consultarProximoDesfazer(Historico *h) {
    if (h->topo == NULL) {
        printf("[i] Historico vazio - nada para desfazer.\n");
    } else {
        printf("[i] Proxima acao a ser desfeita: [%s] \"%s\"\n",
               h->topo->tipoAcao, h->topo->conteudo);
    }
}

// Imprime o histórico completo (do mais recente ao mais antigo)
void imprimirHistorico(Historico *h) {
    if (h->topo == NULL) {
        printf("Historico: [ VAZIO ]\n\n");
        return;
    }

    Acao *atual = h->topo;
    printf("Historico: [ TOPO ] ");
    while (atual != NULL) {
        printf("[%s]\"%s\" -> ", atual->tipoAcao, atual->conteudo);
        atual = atual->prox;
    }
    printf("NULL [ BASE ]\n\n");
}

// Libera toda a memória alocada ao encerrar o programa
void liberarHistorico(Historico *h) {
    Acao *atual = h->topo;
    while (atual != NULL) {
        Acao *aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(h);
}

// Remove o '\n' deixado pelo fgets no final da string
void removerQuebraDeLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void exibirInstrucoes() {
    printf("===================================================\n");
    printf("   ATIVIDADE - HISTORICO DE DESFAZER (PILHA / LIFO)\n");
    printf("===================================================\n\n");
    printf("Este programa simula o historico de acoes de um editor de texto,\n");
    printf("como o botao \"Desfazer\" (Ctrl+Z).\n\n");
    printf("Tipos de acao permitidos (digite exatamente como esta escrito):\n");
    printf("  - digitar\n");
    printf("  - apagar\n");
    printf("  - colar\n");
    printf("  - formatar\n\n");
    printf("Ao registrar uma acao, sera solicitado:\n");
    printf("  1) o TIPO da acao (uma das opcoes acima)\n");
    printf("  2) o CONTEUDO afetado (texto livre, ex: \"Ola mundo\")\n\n");
    printf("O historico tem capacidade maxima de %d acoes.\n", LIMITE_HISTORICO);
    printf("Use o menu abaixo para interagir com o sistema.\n");
}

int main() {
    Historico *editor = criarHistorico();
    int proximoId = 1;
    int opcao;
    char buffer[10];
    char tipo[20];
    char conteudo[100];

    exibirInstrucoes();

    do {
        printf("\n===== MENU - HISTORICO DE DESFAZER =====\n");
        printf("1 - Registrar nova acao\n");
        printf("2 - Desfazer (Ctrl+Z)\n");
        printf("3 - Consultar proxima acao a desfazer\n");
        printf("4 - Imprimir historico completo\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");

        fgets(buffer, sizeof(buffer), stdin);
        opcao = atoi(buffer);

        switch (opcao) {
            case 1:
                printf("Tipo da acao (digitar/apagar/colar/formatar): ");
                fgets(tipo, sizeof(tipo), stdin);
                removerQuebraDeLinha(tipo);

                if (!tipoValido(tipo)) {
                    printf("[!] Tipo invalido! Use: digitar, apagar, colar ou formatar.\n");
                    break;
                }

                printf("Conteudo da acao: ");
                fgets(conteudo, sizeof(conteudo), stdin);
                removerQuebraDeLinha(conteudo);

                registrarAcao(editor, proximoId, tipo, conteudo);
                proximoId++;
                break;

            case 2:
                desfazer(editor);
                break;

            case 3:
                consultarProximoDesfazer(editor);
                break;

            case 4:
                imprimirHistorico(editor);
                break;

            case 5:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("[!] Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 5);

    liberarHistorico(editor);
    return 0;
}
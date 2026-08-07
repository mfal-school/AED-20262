#include <stdio.h>

/*
 * EXEMPLO: Arrays em C - Fibonacci com "n" desconhecido de antemao
 * -------------------------------------------------------------------
 * Enunciado:
 *   - Precisamos armazenar n numeros da sequencia de Fibonacci em um array.
 *   - n NAO e conhecido de antemao (sera lido do usuario).
 *   - Apos o preenchimento, o usuario remove um item pelo indice.
 *   - Imprimimos o array antes e depois da remocao.
 *   - Discutimos a alocacao de memoria envolvida.
 */

#define CAPACIDADE_MAXIMA 100  // "chute" de um limite seguro

void imprimirArray(int vetor[], int capacidade, int usados) {
    printf("[ ");
    for (int i = 0; i < capacidade && i < usados + 5; i++) {
        // imprime os usados + uma amostra de posicoes vazias, para nao poluir a tela
        if (i < usados)
            printf("%d ", vetor[i]);
        else
            printf("_ ");
    }
    if (capacidade > usados + 5) printf("... ");
    printf("]\n");
}

int main(void) {

    int vetor[CAPACIDADE_MAXIMA]; 
    int n;

    // ---------- 1) Lendo n do usuario (nao sabemos de antemao) ----------
    printf("Quantos numeros da sequencia de Fibonacci deseja gerar? ");
    scanf("%d", &n);

    if (n <= 0 || n > CAPACIDADE_MAXIMA) {
        printf("Valor invalido. Escolha um n entre 1 e %d.\n", CAPACIDADE_MAXIMA);
        return 1;
    }

    // ---------- 2) Gerando a sequencia de Fibonacci ----------
    vetor[0] = 0;
    if (n > 1) vetor[1] = 1;
    for (int i = 2; i < n; i++) {
        vetor[i] = vetor[i - 1] + vetor[i - 2];
    }

    printf("\nCapacidade reservada em memoria: %d posicoes (%lu bytes)\n",
           CAPACIDADE_MAXIMA, CAPACIDADE_MAXIMA * sizeof(int));
    printf("Posicoes realmente usadas (n): %d (%lu bytes)\n",
           n, n * sizeof(int));
    printf("Memoria reservada e NAO usada: %d posicoes (%lu bytes)\n\n",
           CAPACIDADE_MAXIMA - n, (CAPACIDADE_MAXIMA - n) * sizeof(int));

    printf("Array ANTES da remocao:\n");
    imprimirArray(vetor, CAPACIDADE_MAXIMA, n);

    // ---------- 3) Lendo o indice a remover ----------
    int indice;
    printf("\nDigite o indice do item que deseja remover (0 a %d): ", n - 1);
    scanf("%d", &indice);

    if (indice < 0 || indice >= n) {
        printf("Indice invalido.\n");
        return 1;
    }

    printf("\nRemovendo o elemento no indice %d (valor = %d)...\n",
           indice, vetor[indice]);

    // Problema: nao existe "buraco" em um array.
    // Para remover, cada elemento apos o indice precisa ser
    // deslocado uma posicao para a esquerda.
    for (int i = indice; i < n - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    n--;  // uma posicao a menos esta "em uso" (mas a memoria continua reservada)

    printf("\nArray DEPOIS da remocao (note o deslocamento):\n");
    imprimirArray(vetor, CAPACIDADE_MAXIMA, n);

    // ---------- 4) Discussao sobre alocacao de memoria ----------
    printf("\n--- Discussao ---\n");
    printf("- O array ocupa SEMPRE %d posicoes na memoria (%lu bytes),\n",
           CAPACIDADE_MAXIMA, CAPACIDADE_MAXIMA * sizeof(int));
    printf("  independente de n ter sido 1 ou %d.\n", CAPACIDADE_MAXIMA);
    printf("- Essa memoria foi reservada no inicio do programa, antes\n");
    printf("  mesmo de sabermos o valor de n digitado pelo usuario.\n");
    printf("- Se o usuario tivesse pedido mais de %d numeros, o programa\n",
           CAPACIDADE_MAXIMA);
    printf("  simplesmente nao teria como atender (capacidade fixa).\n");
    printf("- A remocao custou ate %d deslocamentos de elementos (O(n)).\n",
           n - indice);

    return 0;
}
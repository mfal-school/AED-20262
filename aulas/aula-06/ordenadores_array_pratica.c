#include <stdio.h>
#include <stdbool.h>

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

void imprimirVetor(int vetor[], int tamanho) {
    printf("[ ");
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("]");
}

void copiarVetor(int origem[], int destino[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        destino[i] = origem[i];
    }
}

// ============================================================================
// 1. BUBBLE SORT ORIGINAL
// ============================================================================
void bubbleSortOriginal(int vetor[], int tamanho, bool crescente, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - 1; ++j) {
            bool deveTrocar = false;

            (*comparacoes)++; // Contabiliza a comparação de pares
            if (crescente) {
                if (vetor[j] > vetor[j + 1]) {
                    deveTrocar = true;
                }
            } else {
                if (vetor[j] < vetor[j + 1]) {
                    deveTrocar = true;
                }
            }

            if (deveTrocar) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++; // Contabiliza a troca realizada
            }
        }
    }
}

// ============================================================================
// 2. BUBBLE SORT COM 1ª MELHORIA (Limite do laço reduz com 'i')
// ============================================================================
void bubbleSortMelhoria1(int vetor[], int tamanho, bool crescente, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; ++i) {
        // Laço interno reduz a cada passada: tamanho - 1 - i
        for (int j = 0; j < tamanho - 1 - i; ++j) {
            bool deveTrocar = false;

            (*comparacoes)++; // Contabiliza a comparação de pares
            if (crescente) {
                if (vetor[j] > vetor[j + 1]) {
                    deveTrocar = true;
                }
            } else {
                if (vetor[j] < vetor[j + 1]) {
                    deveTrocar = true;
                }
            }

            if (deveTrocar) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++; // Contabiliza a troca realizada
            }
        }
    }
}

// ============================================================================
// 3. BUBBLE SORT COM 2ª MELHORIA (Flag de Troca / Interrupção Antecipada)
// ============================================================================
void bubbleSortMelhoria2(int vetor[], int tamanho, bool crescente, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; ++i) {
        bool houveTroca = false; // Reseta a flag no início da passada

        for (int j = 0; j < tamanho - 1 - i; ++j) {
            bool deveTrocar = false;

            (*comparacoes)++; // Contabiliza a comparação de pares
            if (crescente) {
                if (vetor[j] > vetor[j + 1]) {
                    deveTrocar = true;
                }
            } else {
                if (vetor[j] < vetor[j + 1]) {
                    deveTrocar = true;
                }
            }

            if (deveTrocar) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++; // Contabiliza a troca realizada
                houveTroca = true;
            }
        }

        // Se nenhuma troca ocorreu na passada inteira, encerra o laço externo
        if (!houveTroca) {
            break;
        }
    }
}

// ============================================================================
// FUNÇÃO AUXILIAR PARA AVALIAR E EXIBIR OS RESULTADOS DE UM CENARIO
// ============================================================================
void testarCenario(const char *nomeCenario, int vetorOriginal[], int tamanho) {
    int copia[10]; // Buffer para armazenar a cópia do vetor
    int comparacoes, trocas;

    printf("\n==================================================\n");
    printf("%s\n", nomeCenario);
    printf("Vetor de Entrada: ");
    imprimirVetor(vetorOriginal, tamanho);
    printf("\n--------------------------------------------------\n");

    // 1. Original
    copiarVetor(vetorOriginal, copia, tamanho);
    bubbleSortOriginal(copia, tamanho, true, &comparacoes, &trocas);
    printf("[Original]    Comparacoes: %2d | Trocas: %2d | Final: ", comparacoes, trocas);
    imprimirVetor(copia, tamanho);
    printf("\n");

    // 2. 1ª Melhoria
    copiarVetor(vetorOriginal, copia, tamanho);
    bubbleSortMelhoria1(copia, tamanho, true, &comparacoes, &trocas);
    printf("[1a Melhoria] Comparacoes: %2d | Trocas: %2d | Final: ", comparacoes, trocas);
    imprimirVetor(copia, tamanho);
    printf("\n");

    // 3. 2ª Melhoria
    copiarVetor(vetorOriginal, copia, tamanho);
    bubbleSortMelhoria2(copia, tamanho, true, &comparacoes, &trocas);
    printf("[2a Melhoria] Comparacoes: %2d | Trocas: %2d | Final: ", comparacoes, trocas);
    imprimirVetor(copia, tamanho);
    printf("\n");
}

// ============================================================================
// MAIN DE EXECUÇÃO
// ============================================================================
int main() {
    // CenArios de Teste (N = 5 elementos)
    int casoMelhor[]    = { 1, 2, 5, 8, 8 };
    int casoAleatorio[] = { 5, 8, 2, 1, 8 };
    int casoPior[]      = { 8, 8, 5, 2, 1 };

    int n = sizeof(casoMelhor) / sizeof(casoMelhor[0]);

    testarCenario("CENARIO 1: Melhor Caso (Vetor Ja Ordenado)", casoMelhor, n);
    testarCenario("CENARIO 2: Caso Medio / Aleatrio", casoAleatorio, n);
    testarCenario("CENARIO 3: Pior Caso (Vetor Invertido)", casoPior, n);

    printf("==================================================\n\n");

    return 0;
}
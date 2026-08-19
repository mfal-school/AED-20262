#include <stdio.h>
#include <stdbool.h>

void imprimirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubbleSortOriginal(int vetor[], int tamanho, bool crescente) {
    for (int i = 0; i < tamanho - 1; ++i) {
        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirVetor(vetor, tamanho);

        for (int j = 0; j < tamanho - 1; ++j) {
            bool deveTrocar = false;

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
                printf("Trocando %d e %d\n", vetor[j], vetor[j + 1]);
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                imprimirVetor(vetor, tamanho);
            } else {
                printf("Sem troca entre %d e %d\n", vetor[j], vetor[j + 1]);
            }
        }
    }
    printf("--- FIM DA ORDENACAO ---\n\n");
}

void bubbleSortMelhoria1(int vetor[], int tamanho, bool crescente) {
    for (int i = 0; i < tamanho - 1; ++i) {
        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirVetor(vetor, tamanho);

        // Limite do laço reduz a cada passada (tamanho - 1 - i)
        for (int j = 0; j < tamanho - 1 - i; ++j) {
            bool deveTrocar = false;

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
                printf("Trocando %d e %d\n", vetor[j], vetor[j + 1]);
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                imprimirVetor(vetor, tamanho);
            } else {
                printf("Sem troca entre %d e %d\n", vetor[j], vetor[j + 1]);
            }
        }
    }
    printf("--- FIM DA ORDENACAO ---\n\n");
}

void bubbleSortMelhoria2(int vetor[], int tamanho, bool crescente) {
    // Laço 1 (Externo): Controla o número de passadas
    for (int i = 0; i < tamanho - 1; ++i) {
        bool houveTroca = false; // Reseta a flag a cada nova passada

        printf("\nPassada %d\n", i + 1);
        printf("Vetor no inicio da passada: ");
        imprimirVetor(vetor, tamanho);

        // Laço 2 (Interno): Faz as comparações (1ª Melhoria: limite reduz com 'i')
        for (int j = 0; j < tamanho - 1 - i; ++j) {
            bool deveTrocar = false;

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
                printf("Trocando %d e %d\n", vetor[j], vetor[j + 1]);
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                
                houveTroca = true; // Marca que houve alteração no vetor
                imprimirVetor(vetor, tamanho);
            } else {
                printf("Sem troca entre %d e %d\n", vetor[j], vetor[j + 1]);
            }
        }

        // 2ª Melhoria: Se não houve nenhuma troca nesta passada, encerra o algoritmo
        if (!houveTroca) {
            printf("Nenhuma troca realizada na passada %d. Vetor ja ordenado!\n", i + 1);
            break; // Interrompe o laço externo (for i)
        }
    }
    printf("--- FIM DA ORDENACAO ---\n\n");
}


int main() {
    int dados[] = { 5, 8, 2, 1, 8 };
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("================= BUBBLE SORT ORIGINAL =================\n");
    int teste1[] = { 5, 8, 2, 1, 8 };
    bubbleSortOriginal(teste1, n, true);

    printf("================= BUBBLE SORT 1a MELHORIA =================\n");
    int teste2[] = { 5, 8, 2, 1, 8 };
    bubbleSortMelhoria1(teste2, n, true);

    printf("================= BUBBLE SORT 2a MELHORIA =================\n");
    int teste3[] = { 5, 8, 2, 1, 8 };
    bubbleSortMelhoria2(teste3, n, true);

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

void imprimirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void insertionSort(int vetor[], int tamanho, bool crescente) {
    for (int i = 1; i < tamanho; ++i) {
        int chave = vetor[i];
        int j = i - 1;

        printf("\nPasso i = %d, chave = %d\n", i, chave);
        printf("Vetor antes da insercao: \n");
        imprimirVetor(vetor, tamanho);

        if(crescente==true) {
            while (j >= 0 && vetor[j] > chave) {
                vetor[j + 1] = vetor[j]; // Deslocando o elemento

                printf("Deslocando %d para a posicao %d\n", vetor[j], j + 1);
                imprimirVetor(vetor, tamanho);
                j = j - 1;
            }
        } else {
            while (j >= 0 && vetor[j] < chave) {
                vetor[j + 1] = vetor[j]; // Deslocando o elemento

                printf("Deslocando %d para a posicao %d\n", vetor[j], j + 1);
                imprimirVetor(vetor, tamanho);
                j = j - 1;
            }
        }
        printf("Inserindo chave %d na posicao %d\n", chave, j + 1);
        vetor[j + 1] = chave; //Insere a chave na posição correta
        imprimirVetor(vetor, tamanho);
    }
    printf("--- FIM DA ORDENACAO ---\n\n");
}



int main() {
    int dados1[] = { 11, 10, 9, 8, 7 };
    int n1 = sizeof(dados1) / sizeof(dados1[0]);

    printf("Vetor Original: ");
    imprimirVetor(dados1, n1);

    printf("Ordem Crescente: \n");
    insertionSort(dados1, n1, true);

    int dados2[] = { 11, 10, 9, 8, 7 };
    int n2 = sizeof(dados2) / sizeof(dados2[0]);

    printf("Ordem Decrescente: \n");
    insertionSort(dados2, n2, false);
    
    return 0;
}
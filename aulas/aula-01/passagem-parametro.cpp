#include <stdio.h>

void somaUm (int idade){
    idade++;
    printf("\n Idade dentro da funcao: %d", idade);
}

void somaUmPonteiro (int *idade){
    (*idade)++; // ou *idade = *idade + 1;
    printf("\n Idade dentro da funcao: %d", *idade);
}   

int main(){
    int idade = 0;
    printf("\n Digite a idade: ");
    scanf("%d", &idade);

    printf("\n Idade antes da funcao: %d", idade);
    somaUm(idade);
    printf("\n Idade depois da funcao: %d", idade);

    printf("\n\n");

    printf("\n Idade antes da funcao: %d", idade);
    somaUmPonteiro(&idade);
    printf("\n Idade depois da funcao: %d", idade);

    printf("\n");

    return 0;
}

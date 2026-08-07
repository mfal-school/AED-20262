#include <stdio.h>

int main(){
    int idade1 = 1;
    int idade2 = 2;
    int *ptrIdade;

    ptrIdade = &idade1;

    printf("\n Valor da variável %d", idade1);  
    printf("\n Endereço da variável %p",&idade1); 

    printf("\n Valor da variável apontada %d", *ptrIdade);
    printf("\n Endereço apontado %p", ptrIdade); 
    printf("\n Endereço do ponteiro %p", &ptrIdade); 
    printf("\n");

    return 0;
}

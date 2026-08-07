#include <stdio.h>
#include <string.h>

typedef struct{
     char nome[40];
	 char cor[20];
     int idade;
}Gato;

int main(){
	Gato gatinho;
	strcpy(gatinho.nome, "garfield");
	strcpy(gatinho.cor,"laranja");
	gatinho.idade = 4;
	
	printf("\nO nome do gato é: %s", gatinho.nome);
	printf("\nA cor do gato é: %s", gatinho.cor);
	printf("\nA idade do gato é: %d", gatinho.idade);
	printf("\n");

	return 0;
}

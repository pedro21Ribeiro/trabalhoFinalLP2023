#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int main(void){
    char nome[tamNome];
    int tipoDeConta;
    double saldo;
   /* 
    printf("Nome: ");
    scanf("%s", nome);
    printf("Tipo de conta: ");
    scanf("%d", &tipoDeConta);
    printf("saldo:  ");
    scanf("%lf", &saldo);*/
    adicionarUsuarios("./users.bin", nome, tipoDeConta, saldo);
    
    popularVetor("./users.bin");
    printf("id: %d\n", usuarios[0] -> id);
    printf("nome: %s\n", usuarios[0] -> nome);
    printf("tipo de conta: %d\n", usuarios[0] -> tipoDeConta);
    printf("saldo: %lf\n", usuarios[0] -> saldo);
}

#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int main(void){
    Conta cliente;

    int opcao;
    int i = 1;
    
while (i != 0)
{
    printf("\n\t\tBANCO COMMITY\n\n");
    printf("1 - Pesquisar por nome\n");
    printf("2 - SAIR\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        printf("Digite o nome do cliente: \n");
        //scanf("%c", user);
        //buscar_por_nome(user);
        cliente = buscar_por_nome("jonas");

        printf("ID: %d\n", cliente.id);
        printf("Nome: %s\n", cliente.nome);
        printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
        printf("Saldo: %0.2lf\n", cliente.saldo);
        break;
    case 2:
        printf("Digite 0 para sair\n");
        scanf("%d", &i);
        break;
    default:
        printf("Opcao Inválida\n");
        break;
    }
    

}

printf("FIM DO WHILE!\n");


    //cliente = buscar_por_nome("jonas");
    //cliente = buscar_por_id(1);
    //printf("ID: %d\n", cliente.id);
    //printf("Nome: %s\n", cliente.nome);
    //printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
    //printf("Saldo: %0.2lf\n", cliente.saldo);
    

}

#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int main(void){
    Conta cliente;
    char user[51];
    char temp;

    int opcao, id;
    int i = 1;
    
    cliente = buscar_por_id(56);

    printf("id:  %d\n", cliente.id);

while (i != 0)
{
    printf("\n\t\tBANCO COMMITY\n\n");
    printf("0 - SAIR\n");
    printf("1 - Pesquisar por nome\n");
    printf("2 - Buscar por CPF\n");
    printf("3 - Cadastrar usuário\n");
    printf("4 - Realizar movimentação (por id)\n");
    printf("5 - Ver movimento\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 0:
        printf("Digite 0 para sair\n");
        scanf("%d", &i);
        break;

    case 1:
        scanf("%c", &temp);
        printf("Digite o nome do cliente: ");
        scanf("%[^\n]", user);
        cliente = buscar_por_nome(user);

        printf("\nID: %d\n", cliente.id);
        printf("Nome: %s\n", cliente.nome);
        printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
        printf("Saldo: %0.2lf\n", cliente.saldo);
        break;
    case 2:
        cliente = buscar_por_cpf();

        printf("\nID: %d\n", cliente.id);
        printf("Nome: %s\n", cliente.nome);
        printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
        printf("Saldo: %0.2lf\n", cliente.saldo);
        break;
    case 3:
        add_user_terminal();
        break;
    case 4:
        add_movimento_terminal();
        break;
    case 5:
        printf("Digite o ID do usuário para buscar as movimentações:  ");
        scanf("%d", &id);
        retornoMovimento(id);
        break;
    default:
        printf("Opcao Inválida\n");
        break;
    }
    

}

printf("FIM DO WHILE!\n");

return 0;

}


    //cliente = buscar_por_nome("jonas");
    //cliente = buscar_por_id(1);
    //printf("ID: %d\n", cliente.id);
    //printf("Nome: %s\n", cliente.nome);
    //printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
    //printf("Saldo: %0.2lf\n", cliente.saldo);
    
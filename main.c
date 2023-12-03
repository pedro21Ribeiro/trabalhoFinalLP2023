#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int main(void){
    Conta cliente;
    char user[51];
    char novoDado[75];
    char temp;
    int confirmar;
    double valor;
    int opcao, id, editar;
    int i = 1;

while (i != 0)
{
    printf("\n\t\tBANCO COMMITY\n\n");
    printf("0 - SAIR\n");
    printf("1 - Pesquisar por nome\n");
    printf("2 - Buscar por CPF\n");
    printf("3 - Cadastrar usuário\n");
    printf("4 - Realizar movimentação (por id)\n");
    printf("5 - Ver movimento\n");
    printf("6 - Buscar por ID\n");
    printf("7 - Alterar dados de usuário\n");
    printf("8 - Realizar deposito\n");
    printf("9 - Deletar usuários\n");
    printf("10 - Imprimir todos os usuários\n");
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
        
        if (cliente.id == 0){
            printf("Não existe ninguém com esse nome no banco de bados\n");
        }else
        {
            printf("\nID: %d\n", cliente.id);
            printf("Nome: %s\n", cliente.nome);
            printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
            printf("Saldo: %0.2lf\n", cliente.saldo);
        }
        break;
    case 2:
        cliente = buscar_por_cpf();

        if (cliente.id == 0){
            printf("Não existe ninguém com esse CPF no banco de bados\n");
        }else
        {
            printf("\nID: %d\n", cliente.id);
            printf("Nome: %s\n", cliente.nome);
            printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
            printf("Saldo: %0.2lf\n", cliente.saldo);
        }
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
    case 6:
        scanf("%c", &temp);
        printf("Digite o ID do cliente: ");
        scanf("%d", &id);
        cliente = buscar_por_id(id);

        if (cliente.id == 0){
            printf("Não existe ninguém com esse ID no banco de bados\n");
            break;
        }   
        printf("\nID: %d\n", cliente.id);
        printf("Nome: %s\n", cliente.nome);
        printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
        printf("Saldo: %0.2lf\n", cliente.saldo);
        break;
    case 7:
        printf("Qual dado será alterado?\n");
        printf("1 - Nome\n");
        printf("2 - CPF\n");
        printf("3 - Tipo de conta\n");
        printf("4 - Saldo\n");
        scanf("%d", &editar);

        printf("Digite o ID do usuário que será alterado:  ");
        scanf("%d", &id);

        scanf("%c", &temp);
        printf("Digite um novo dado:  ");
        scanf("%[^\n]", novoDado);

        alterar_users(id, editar, novoDado);
        break;    
    case 8:
        printf("Digite a ID do usuários que será feito o deposito:  ");
        scanf("%d", &id);
        printf("Digite o valor que será depositado:  ");
        scanf("%lf", &valor);
        
        deposito(valor, id);
    break;
    case 9:
        printf("Digite o ID do usuário que será deletado:  ");
        scanf("%d", &id);

        deletarUsuario(id);
    break;
    case 10:
        printf("Serão impressos todos os usuários isso pode levar um tempo deseja continuar mesmo assim? 0 - Não | 1 - Sim\n");
        scanf("%d", &confirmar);
        if(!confirmar){
            printf("Cancelando operação\n");
        }else{
           todosUsuários(); 
        }
        break;
    default:
        printf("Opcao Inválida\n");
        break;
    }
}

printf("BYE!\n");

return 0;

}

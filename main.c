#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int main(void){
    Conta cliente;

    cliente = retornoUsers("SELECT * FROM users WHERE id='1'");
    printf("Nome: %d\n", cliente.id);
    printf("Nome: %s\n", cliente.nome);
    printf("Nome: %d\n", cliente.tipoDeConta);
    printf("Nome: %0.2lf\n", cliente.saldo);

}

#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int main(void){
    Conta cliente;


    cliente = buscar_por_nome("jonas");
    cliente = buscar_por_id(1);
    printf("ID: %d\n", cliente.id);
    printf("Nome: %s\n", cliente.nome);
    printf("Tipo de Conta: %d\n", cliente.tipoDeConta);
    printf("Saldo: %0.2lf\n", cliente.saldo);

}

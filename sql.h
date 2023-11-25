#include "funcoes.h"

Conta retornoUsers(char query[600]);
Movimento retornoMovimento(char query[600]);
void adicionarUser(char nome[51], int tipoDeConta, double saldo);
void adicionarMovimento(int sender, int reciver, double valor, char data[11]);
void usersSemRetorno(char query[600]);

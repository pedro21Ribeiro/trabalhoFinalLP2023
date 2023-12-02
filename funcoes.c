#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"
#include <mysql.h>
#include <string.h>
#include <time.h>

char *server = "localhost";//Servidor
char *user = "root"; //Usuário (recomendo criar outro sem ser o root)
char *password = "2023"; //Senha do usuário
char *database = "banco"; //O database a ser acessado

void deletarUsuario(int id){
    Conta check;
    check = buscar_por_id(id);

    if (check.id == 0){
        printf("Usuário não existem, cancelando operação\n");
        return;
    }

    char query [600];
    sprintf(query, "DELETE FROM users WHERE id = '%d' LIMIT 1;", id);
    usersSemRetorno(query);
    printf("Usuários deletado com sucesso\n");
}


void alterar_users(int id, int dado, char *novoDado){ //id do usuário de será alterado, dado > qual dado será alterado, novoDado > dados alterados
    char query [600];
    char valor [75];
    switch (dado)
    {
    case 1:
        strcpy(valor,"nome");
        break;
    case 2:
        strcpy(valor,"cpf");
        break;
    case 3:
        strcpy(valor,"tipo"); //tipo de conta
        break;
    case 4:
        strcpy(valor,"saldo");           
        break;
    default:
        break;
    }
    sprintf(query, "UPDATE users SET %s = '%s' WHERE id = '%d' LIMIT 1;", valor, novoDado, id);
    usersSemRetorno(query);
}

void deposito(double valor, int id){
    Conta check; 
    double saldoNovo;
    char *value;
    check = buscar_por_id(id);

    if(check.id == 0){
        printf("Usuários inexistente, cancelando a operação\n");
        return;
    }
    if (valor <= 0){
        printf("Valor não pode ser negativo ou 0, cancelando operação\n");
        return;
    }

    saldoNovo = check.saldo + valor;
    sprintf(value, "%f", saldoNovo);
    alterar_users(id, 4, value);
}


void add_movimento_terminal(){
    int idEnvio;
    int idRecebimento;
    double valor;


    printf("Digite o id da conta que vai enviar o dinheiro:  ");
    scanf("%d", &idEnvio);
    printf("Digite o id da conta que ira receber o dinheiro:   ");
    scanf("%d", &idRecebimento);
    printf("Digite o valor da transação:   ");
    scanf("%lf", &valor);

    transferir_dinheiro(idEnvio, idRecebimento, valor);
}
//passar o valor da conta usando id's
void transferir_dinheiro(int contaEnvio, int contaRecebimento, double valor){
    Conta Recebimento;
    Conta Envio;
    int opt;
    double saldoNovo;
    char query[600];
    time_t currentTime;
    struct tm *localTime;
    char data[11];
    
    time(&currentTime);
    localTime = localtime(&currentTime);

    strftime(data, sizeof(data), "%Y-%m-%d", localTime);


    //checando id envio
    Envio = buscar_por_id(contaEnvio);
    if(Envio.id == 0){
        printf("Id da conta envio invalido ou inexistente\n");
        return;
    }

    //checando id Recebimento
    Recebimento = buscar_por_id(contaRecebimento);
    if(Recebimento.id == 0){
        printf("Id da conta Recebimento invalido ou inexistente\n");
        return;
    }

    //checando se valor é valido
    if(valor <= 0.0000){
        printf("Valor não pode ser negativo cancelando transferencia \n");
        return;
    }

    
    //Aviso sobre divida
    if(valor > Envio.saldo){
        while (opt != 1) {
            printf("Valor da transação maior que o saldo atual\n");
            printf("Continuar com a transação gerará divida. Continuar 0 - Não | 1 - Sim\n");
            scanf("%d", &opt);
            if(opt == 0){
                printf("Cancelando transação\n");
                return;
            }else if(opt == 1){
                printf("Sim foi escolhido será gerado divida\n");
            }else {
                printf("Opção invalida!!\n");
            }
        }

    }
    
    saldoNovo = Envio.saldo - valor;

    sprintf(query, "UPDATE users SET saldo = '%lf' WHERE id = %d LIMIT 1;", saldoNovo, contaEnvio);

    usersSemRetorno(query);

    saldoNovo = Recebimento.saldo + valor;

    sprintf(query, "UPDATE users SET saldo = '%lf' WHERE id = %d LIMIT 1;", saldoNovo, contaRecebimento);

    usersSemRetorno(query);

    adicionarMovimento(contaEnvio, contaRecebimento, valor, data);
    printf("Movimentacao realizada com sucesso\n");
}




void add_user_terminal(){
    char nome[51];
    int tipoDeConta;
    double saldo;
    long long int numCpf;
    char cpf[15];
    char queryVerificacao[600];
    Conta verificar;

    int opt;
    char temp;


    //Recebimento e declaração de variaveis
    scanf("%c", &temp);
    printf("Digite o nome do cliente a ser adicinado:  ");
    scanf("%[^\n]", nome);
    printf("Digite o seu cpf (somente os numeros):   ");
    scanf("%lld", &numCpf);
    printf("Digite o tipo da conta:   ");
    scanf("%d", &tipoDeConta);
    printf("Digite o seu deposito inicial ou 0 se preferiri não investir:   ");
    scanf("%lf", &saldo);
    scanf("%c", &temp);

    formatarCpf(numCpf, cpf);

    sprintf(queryVerificacao, "SELECT * FROM users WHERE cpf = '%s';", cpf);
    verificar = retornoUsers(queryVerificacao);

    if(verificar.id != 0){
        while(1){
            printf("CPF já cadastrado digite 1 para cadastrar novamente ou 0 para cancelar\n");
            scanf("%d", &opt);
            if(opt == 0){
                return;
            }else if(opt == 1){
                add_user_terminal();
            }else{
                printf("Opção invaldia\n");
            }
        }
        
    }



    if(saldo < 0){
        while(1){
            printf("Saldo inicial não pode ser negativo digite 1 para cadastrar novamente ou 0 para cancelar\n");
            scanf("%d", &opt);
            if(opt == 0){
                return;
            }else if(opt == 1){
                add_user_terminal();
            }else{
                printf("Opção invaldia\n");
            }
        }
        
    }
    adicionarUser(nome, tipoDeConta, saldo, cpf);
    printf("Usuários adicionado com sucesso\n");
}

Conta retornoUsers(char query[600]){
    //Declarasção das varravéis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); //Iniciando a estrutura SQL com o MySql
	
        //conectando-se a DB
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    Conta cliente = {0, "", 0, 0.0};

	    //Envio de querrys SQL, é o que está Aspas
    
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    res = mysql_store_result(conn);//Guardando o resultado da querry

            //passa valor por valor para cada fileira retornada
	while ((row = mysql_fetch_row(res)) != NULL){
        cliente.id = atoi(row[0]);
        strcpy(cliente.nome, row[1]);
        cliente.tipoDeConta = atoi(row[2]);
        cliente.saldo = atof(row[3]);
        cliente.cpf = atoi(row[4]);
        cliente.numeroDaConta = atoi(row[5]);
    }

    //limpa os resultados
	mysql_free_result(res);
    //termina a conexão
	mysql_close(conn);
    return cliente;
}

Movimento retornoMovimento(int id){
    //Declaração das variavéis SQL em ordem, Conexão, Resultado e Fileira
    char query[600];
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); //Iniciando a estrutura SQL com o MySql
	
        //conectando-se a DB
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    Movimento movimento= {0, 0, 0, 0, ""};    

	    //Envio de querrys SQL, é o que está Aspas
    sprintf(query,"SELECT * FROM movimentos WHERE contaSaida = '%d' OR contaEntrada = '%d'",id, id);
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    res = mysql_store_result(conn);//Guardando o resultado da querry

            //passa valor por valor para cada fileira retornada
	while ((row = mysql_fetch_row(res)) != NULL){
        movimento.id = atoi(row[0]);
        movimento.sender = atoi(row[1]);
        movimento.reciver = atoi(row[2]);
        movimento.valor = atof(row[3]);
        strcpy(movimento.data, row[4]);

        if (movimento.sender == id){
            printf("Enviado R$ %0.2f para a conta de id %d no dia %s\n", movimento.valor, movimento.reciver, movimento.data);
        }
        else{
            printf("Recebeu R$ %.02f para a conta de id %d no dia %s\n", movimento.valor, movimento.sender, movimento.data);
        }
       }

    //limpa os resultados
	mysql_free_result(res);
    //termina a conexão
	mysql_close(conn);
    
    return movimento;
}

void adicionarUser(char name[51], int tipoDeConta, double saldo, char cpf[15]){
    //Declarasção das varravéis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); //Iniciando a estrutura SQL com o MySql
	
        //conectando-se a DB
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    char query[600];
    
    sprintf(query,"INSERT INTO users (nome, tipo, saldo, cpf) VALUES ('%s', '%d', '%lf', '%s');", name, tipoDeConta, saldo, cpf);


	if (mysql_query(conn, query)) {
		printf("erro na query\n");
	}
}

void adicionarMovimento(int sender, int reciver, double valor, char data[11]){
    //Declaração das varavéis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); //Iniciando a estrutura SQL com o MySql
	
        //conectando-se a DB
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    char query[600];
    
    sprintf(query,"INSERT INTO movimentos (contaSaida, contaEntrada, valorMovimento, dataMovimento) VALUES ('%d', '%d', '%lf', '%s');", sender, reciver, valor, data);


	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
}

void usersSemRetorno(char query[600]){
    //Declaração das varavéis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); //Iniciando a estrutura SQL com o MySql
	
        //conectando-se a DB
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
}

Conta buscar_por_nome(char nome[51]){
    char query[600]; //
    sprintf(query, "SELECT * FROM users WHERE nome = '%s'; ",nome);
    return retornoUsers (query);

}
Conta buscar_por_id(int id){
    char query[600];
    sprintf(query, "SELECT * FROM users WHERE id = '%d'; ", id);
    return retornoUsers(query);
}

Conta buscar_por_cpf(){
    long long int numCpf;
    char cpf[15];
    char query[600];

    printf("Digite o CPF a ser buscado (somente numeros):    ");
    scanf("%lld", &numCpf);
    formatarCpf(numCpf, cpf);
    sprintf(query,"SELECT * FROM users WHERE cpf = '%s'; ", cpf);
    return retornoUsers(query);
}

void formatarCpf(long long int numCpf, char *cpf) {
    // Convert the number to a string
    char numberString[12];  // One extra space for the null terminator
    snprintf(numberString, sizeof(numberString), "%lld", numCpf);

    // Ensure the number is exactly 11 digits
    if (strlen(numberString) != 11) {
        printf("Error: O numero não é do tamanho de 11 digitos\n");
        return;
    }

    // Format the string as xxx.xxx.xxx-xx
    snprintf(cpf, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c",
             numberString[0], numberString[1], numberString[2],
             numberString[3], numberString[4], numberString[5],
             numberString[6], numberString[7], numberString[8],
             numberString[9], numberString[10]);
}

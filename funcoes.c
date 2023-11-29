#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"
#include <mysql.h>
#include <string.h>

p_contas usuarios[MAX];


char *server = "localhost";//Servidor
char *user = "root"; //Usuário (recomendo criar outro sem ser o root)
char *password = "2023"; //Senha do usuário
char *database = "banco"; //O database a ser acessado


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
    }

    //limpa os resultados
	mysql_free_result(res);
    //termina a conexão
	mysql_close(conn);
    return cliente;
}

Movimento retornoMovimento(char query[600]){
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
	
    Movimento movimento= {0, 0, 0, 0, ""};    

	    //Envio de querrys SQL, é o que está Aspas
    
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
       }

    //limpa os resultados
	mysql_free_result(res);
    //termina a conexão
	mysql_close(conn);
    
    return movimento;
}

void adicionarUser(char nome[51], int tipoDeConta, double saldo){
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
    
    sprintf(query,"INSERT INTO users (nome, tipo, saldo) VALUES (%s, %d, %lf)", nome, tipoDeConta, saldo);


	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
}

void adicionarMovimento(int sender, int reciver, double valor, char data[11]){
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
    
    sprintf(query,"INSERT INTO movimentos (contaSaida, contaEntrada, valorMovimento, dataMovimento) VALUES (%d, %d, %lf, %s)", sender, reciver, valor, data);


	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
}

void usersSemRetorno(char query[600]){
    //Declarasção das varravéis SQL em ordem, Conexão, Resultado e Fileira
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
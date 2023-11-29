#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"
#include <mysql.h>
#include <string.h>

p_contas usuarios[MAX];


char *server = "localhost";//Servidor
char *user = "sistema"; //Usuário (recomendo criar outro sem ser o root)
char *password = "senhaForte1234"; //Senha do usuário
char *database = "banco"; //O database a ser acessado


int popularVetor(char *arquivo){
    FILE *fp = NULL;
    fp = fopen(arquivo, "rb");
    if(fp == NULL){
        return 1;
    }
    

    for(int i = 0; i<MAX; i++){
        usuarios[i] = (p_contas)malloc(sizeof(Conta));
        fread(usuarios[i], sizeof(Conta), 1, fp);
    }

    fclose(fp);
    return 0;
}

int adicionarUsuarios(char *arquivo, char nome[tamNome], int tipoDeConta, double saldo){
    int i = 0;
    popularVetor(arquivo);
    FILE *fp = NULL;
    fp = fopen(arquivo, "wb");
    fwrite("abc", sizeof("abc"), 1, fp);
    fclose(fp);
    
    fp = fopen(arquivo, "wb");

    if(fp == NULL){
        return 1;
    }
    //Esse for está vazio pois o objetivo dele é chegar no ultimo usuário adicionado
    /*for(i=0;i<MAX;i++){
        if(usuarios[i]->id!= i+1){
            break;
        }
    }*/
    usuarios[i] = (p_contas)(malloc(sizeof(Conta)));
    usuarios[i] -> id = 1;
    /*for(int j =0; j < tamNome; j++){
        usuarios[i] -> nome[j] = nome[j];
    }*/
    usuarios[i] -> tipoDeConta = 1;
    usuarios[i] -> saldo = 100;
    
    fwrite(&usuarios, sizeof(usuarios), 1, fp);
    fclose(fp);
    return 0;
}

Conta retornoUsers(char query[600]){
    //Declarasção das varravéis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); //Iniciando a estrutura SQL com o MySql
	
        //conectando-se a DB
	if (!mysql_real_connect(conn, server, user, password, database, 0, "mysql", 0)) {
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
	
    Movimento movimento = {0, 0, 0, 0, ""};    

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

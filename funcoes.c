#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"
#include <mysql.h>
#include <string.h>
#include <time.h>

//Variáveis de de conexão ao banco de dados
char *server = "localhost";//Servidor
char *user = "sistema"; //Usuário (recomendo criar outro sem ser o root)
char *password = "senhaForte1234"; //Senha do usuário
char *database = "banco"; //O database a ser acessado

//Função para deletar um usuário com base no ID
void deletarUsuario(int id){
    Conta check = {0, "", 0, 0.0, 0}; // Variável para verificar se o usuário existe
    check = buscar_por_id(id); // Verifica se o usuário existe no banco de dados

    if (check.id == 0){
        printf("Usuário não existem, cancelando operação\n");
        return;
    }
	
    
    char query [600]; // String para armazenar a query SQL
    //Cria uma query SQL para deletar o usuário do banco de dados
    sprintf(query, "DELETE FROM users WHERE id = '%d' LIMIT 1;", id);
    usersSemRetorno(query); // Execução da query SQL para deletar o usuário
    printf("Usuários deletado com sucesso\n");
}

// Função para alterar informações de um usuário
void alterar_users(int id, int dado, char *novoDado){ //id do usuário de será alterado, dado > qual dado será alterado, novoDado > dados alterados
    char query [600]; // String para armazenar a query SQL
    char queryVerificacao[600]; // String para armazenar a query de verificação
    char valor [75]; // String para armazenar o nome do campo que será alterado
    char cpfFormatado[15]; // String para armazenar o CPF formatado

    // Verifica se o usuário existe baseado no ID fornecido
    Conta check = {0, "", 0, 0.0, 0};
    switch (dado)
    {
    case 1:
        strcpy(valor,"nome"); // Campo a ser alterado: nome
        break;
    case 2:
        strcpy(valor,"cpf"); // Campo a ser alterado: cpf
        fomratarCpfString(novoDado, cpfFormatado); // Formata o novo CPF
        sprintf(queryVerificacao, "SELECT * FROM users WHERE cpf = '%s';", cpfFormatado);
        check = retornoUsers(queryVerificacao); // Verifica se o CPF já está cadastrad
        if(check.id != 0){
            printf("CPF já cadastrado cancelando operação\n");
            return;
        }
        sprintf(query, "UPDATE users SET cpf = '%s' WHERE id = '%d' LIMIT 1;", cpfFormatado, id);
        usersSemRetorno(query); // Atualiza o CPF do usuário no banco de dados
        printf("Dados alterado com sucesso\n");
        return;
        break;
    case 3:
        strcpy(valor,"tipo"); // Campo a ser alterado: tipo de conta
        break;
    case 4:
        strcpy(valor,"saldo"); // Campo a ser alterado: saldo
        break;
    default:
        break;
    }
    // Criação e execução da query SQL para atualizar os dados do usuário
    sprintf(query, "UPDATE users SET %s = '%s' WHERE id = '%d' LIMIT 1;", valor, novoDado, id);
    usersSemRetorno(query);
    printf("Dados alterado com sucesso\n");
}

// Função para realizar um depósito na conta de um usuário
void deposito(double valor, int id){
    Conta check = {0, "", 0, 0, 0}; // Variável para verificar se o usuário existe
    double saldoNovo; // Variável para armazenar o novo saldo
    char value[87]; // String para armazenar o valor formatado como string
    check = buscar_por_id(id); // Verifica se o usuário com o ID fornecido existe

    if(check.id == 0){
        printf("Usuários inexistente, cancelando a operação\n");
        return;
    }
    if (valor <= 0){
        printf("Valor não pode ser negativo ou 0, cancelando operação\n");
        return;
    }

    
    saldoNovo = check.saldo + valor; // Calcula o novo saldo
    sprintf(value, "%f", saldoNovo); // Converte o novo saldo para string
    alterar_users(id, 4, value); // Atualiza o saldo do usuário no banco de dados
    printf("Deposito realizado com sucesso\n");
}

// Função para adicionar uma transação entre contas
void add_movimento_terminal(){
    int idEnvio; // ID da conta que enviará o dinheiro
    int idRecebimento; // ID da conta que receberá o dinheiro
    double valor; // Valor a ser transferido entre as contas

    // Solicitação de entrada de dados pelo usuário
    printf("Digite o id da conta que vai enviar o dinheiro:  ");
    scanf("%d", &idEnvio);
    printf("Digite o id da conta que ira receber o dinheiro:   ");
    scanf("%d", &idRecebimento);
    printf("Digite o valor da transação:   ");
    scanf("%lf", &valor);

    // Chamada à função para transferir dinheiro entre as contas
    transferir_dinheiro(idEnvio, idRecebimento, valor);
}

// Função para transferir dinheiro entre contas utilizando ID's
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

    // Checagem da conta de envio
    Envio = buscar_por_id(contaEnvio);
    if(Envio.id == 0){
        printf("Id da conta envio invalido ou inexistente\n");
        return;
    }

    // Checagem da conta de recebimento
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

    // Atualização do saldo da conta de envio
    saldoNovo = Envio.saldo - valor;

    sprintf(query, "UPDATE users SET saldo = '%lf' WHERE id = %d LIMIT 1;", saldoNovo, contaEnvio);

    usersSemRetorno(query);

    // Atualização do saldo da conta de recebimento
    saldoNovo = Recebimento.saldo + valor;

    sprintf(query, "UPDATE users SET saldo = '%lf' WHERE id = %d LIMIT 1;", saldoNovo, contaRecebimento);

    usersSemRetorno(query);

     // Adição do movimento ao banco de dados
    adicionarMovimento(contaEnvio, contaRecebimento, valor, data);
    printf("Movimentacao realizada com sucesso\n");
}

// Função para adicionar um novo usuário ao banco de dados
void add_user_terminal(){
    char nome[51];
    int tipoDeConta;
    double saldo;
    long long int numCpf;
    char cpf[15];
    char queryVerificacao[600];
    Conta verificar = {0, "", 0, 0, 0};

    int opt;
    char temp;

    // Recebe e armazena os dados do novo usuário
    scanf("%c", &temp);
    printf("Digite o nome do cliente a ser adicinado (Max. 50 caracteres):  ");
    scanf("%[^\n]", nome);
    printf("Digite o seu cpf (somente os numeros do cpf):   ");
    scanf("%lld", &numCpf);
    printf("Digite o tipo da conta (numérico):   ");
    scanf("%d", &tipoDeConta);
    printf("Digite o seu deposito inicial ou 0 se preferir não investir:   ");
    scanf("%lf", &saldo);
    scanf("%c", &temp);

    // Formata o CPF
    formatarCpf(numCpf, cpf);

    // Verifica se o CPF já está cadastrado
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

    // Verifica se o saldo inicial é válido
    if(saldo < 0){
        while(1){
            printf("Saldo inicial não pode ser negativo digite 1 para cadastrar novamente ou 0 para cancelar\n");
            scanf("%d", &opt);
            if(opt == 0){
                return;
            }else if(opt == 1){
                add_user_terminal(); // Chamada recursiva para tentar adicionar um novo usuário
            }else{
                printf("Opção invaldia\n");
            }
        }
        
    }

    // Adiciona o novo usuário ao banco de dados
    adicionarUser(nome, tipoDeConta, saldo, cpf);
    printf("Usuários adicionado com sucesso\n");
}

// Função que realiza uma consulta SQL e retorna os detalhes de um usuário
Conta retornoUsers(char query[600]){
    //Declaração das variáveis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	conn = mysql_init(NULL); // Inicialização da estrutura MySQL
	
        // Conexão ao banco de dados
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    Conta cliente = {0, "", 0, 0.0}; // Inicialização de um objeto Conta para armazenar os dados do usuário

	//Envio de querrys SQL, é o que está Aspas

	// Execução da query SQL fornecida como parâmetro
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    res = mysql_store_result(conn);// Armazena o resultado da consulta

        // Percorre os resultados da consulta
	while ((row = mysql_fetch_row(res)) != NULL){
	// Preenche os dados do usuário na estrutura Conta
        cliente.id = atoi(row[0]);
        strcpy(cliente.nome, row[1]);
        cliente.tipoDeConta = atoi(row[2]);
        cliente.saldo = atof(row[3]);
        cliente.cpf = atoi(row[4]);
    }

    // Libera a memória do resultado da consulta
	mysql_free_result(res);
     // Fecha a conexão com o banco de dados
	mysql_close(conn);
    return cliente; // Retorna os dados do usuário recuperados do banco de dados
}

// Função para buscar e exibir os movimentos financeiros de uma conta
Movimento retornoMovimento(int id){
    //Declaração das variavéis SQL em ordem, Conexão, Resultado e Fileira
    char query[600]; //String para armazenar a query SQL
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
    //constantes para a conexão a DataBase

	
	conn = mysql_init(NULL); // Inicialização da estrutura MySQL
	
        // Conexão ao banco de dados
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    Movimento movimento= {0, 0, 0, 0, ""};    

    // Criação da query SQL para buscar movimentos relacionados ao ID da conta
    sprintf(query,"SELECT * FROM movimentos WHERE contaSaida = '%d' OR contaEntrada = '%d'",id, id);

	// Execução da query SQL
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    res = mysql_store_result(conn); // Armazena o resultado da consulta

        // Iteração sobre os resultados da consulta
	while ((row = mysql_fetch_row(res)) != NULL){
	// Preenchimento dos dados do movimento na estrutura Movimento
        movimento.id = atoi(row[0]);
        movimento.sender = atoi(row[1]);
        movimento.reciver = atoi(row[2]);
        movimento.valor = atof(row[3]);
        strcpy(movimento.data, row[4]);

	// Verifica se o movimento é uma transferência de saída ou de entrada e exibe a informação correspondente
        if (movimento.sender == id){
            printf("Enviado R$ %0.2f para a conta de id %d no dia %s\n", movimento.valor, movimento.reciver, movimento.data);
        }
        else{
            printf("Recebeu R$ %.02f para a conta de id %d no dia %s\n", movimento.valor, movimento.sender, movimento.data);
        }
       }

    // Libera a memória do resultado da consulta
	mysql_free_result(res);
    // Fecha a conexão com o banco de dados
	mysql_close(conn);
    
    return movimento; // Retorna as informações do movimento recuperadas do banco de dados
}

// Função para adicionar um novo usuário ao banco de dados
void adicionarUser(char name[51], int tipoDeConta, double saldo, char cpf[15]){
    
    MYSQL *conn; // Conexão com o banco de dados
	

	
	conn = mysql_init(NULL); // Inicialização da estrutura MySQL
	
        // Conexão ao banco de dados
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    char query[600];
	
    // Criação da query SQL para inserir um novo usuário
    sprintf(query,"INSERT INTO users (nome, tipo, saldo, cpf) VALUES ('%s', '%d', '%lf', '%s');", name, tipoDeConta, saldo, cpf);

	// Execução da query SQL
	if (mysql_query(conn, query)) {
		printf("erro na query\n");
	}
}

// Função para adicionar um movimento financeiro ao banco de dados
void adicionarMovimento(int sender, int reciver, double valor, char data[11]){
    
    MYSQL *conn; // Conexão com o banco de dados
	
    
	
	conn = mysql_init(NULL); // Inicialização da estrutura MySQL
	
        // Conexão ao banco de dados
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
    char query[600];

    // Criação da query SQL para inserir um novo registro de movimento
    sprintf(query,"INSERT INTO movimentos (contaSaida, contaEntrada, valorMovimento, dataMovimento) VALUES ('%d', '%d', '%lf', '%s');", sender, reciver, valor, data);

	// Execução da query SQL
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
}

// Função para executar consultas no banco de dados que não retornam resultados
void usersSemRetorno(char query[600]){
    
    MYSQL *conn; // Conexão com o banco de dados

	
	conn = mysql_init(NULL); // Inicialização da estrutura MySQL
	
        // Conexão ao banco de dados
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	// Execução da query SQL fornecida como parâmetro
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
}

// Função para buscar um usuário pelo nome
Conta buscar_por_nome(char nome[51]){
    char query[600]; // String para armazenar a query SQL
    sprintf(query, "SELECT * FROM users WHERE nome = '%s'; ",nome);
    return retornoUsers (query);

}

// Função para buscar um usuário pelo ID
Conta buscar_por_id(int id){
    char query[600]; // String para armazenar a query SQL
    sprintf(query, "SELECT * FROM users WHERE id = '%d'; ", id);
    return retornoUsers(query);
}

// Função para buscar um usuário pelo CPF
Conta buscar_por_cpf(){
    long long int numCpf; // Variável para armazenar o número do CPF
    char cpf[15]; // String para armazenar o CPF formatado
    char query[600]; // String para armazenar a query SQL

    printf("Digite o CPF a ser buscado (somente os numeros do cpf):    ");
    scanf("%lld", &numCpf);
    formatarCpf(numCpf, cpf); // Formata o CPF inserido para o formato de busca no banco de dados
    sprintf(query,"SELECT * FROM users WHERE cpf = '%s'; ", cpf);
    return retornoUsers(query);
}

// Função para formatar um número de CPF para o formato XXX.XXX.XXX-XX
void formatarCpf(long long int numCpf, char *cpf) {
    // String temporária para converter o número de CPF em formato de string
    char numberString[12];  // One extra space for the null terminator
    snprintf(numberString, sizeof(numberString), "%lld", numCpf); // Converte o número de CPF para string

    // Verifica se o número de CPF possui 11 dígitos
    if (strlen(numberString) != 11) {
        printf("Error: O numero não é do tamanho de 11 digitos\n");
        return;
    }

    // Formata o número de CPF no padrão xxx.xxx.xxx-xx
    snprintf(cpf, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c",
             numberString[0], numberString[1], numberString[2],
             numberString[3], numberString[4], numberString[5],
             numberString[6], numberString[7], numberString[8],
             numberString[9], numberString[10]);
}

// Função para formatar uma string de CPF para o formato XXX.XXX.XXX-XX
void fomratarCpfString(char *antigo, char *novo){

    // Formata o número de CPF no padrão xxx.xxx.xxx-xx
    snprintf(novo, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c",
    antigo[0], antigo[1], antigo[2],
    antigo[3], antigo[4], antigo[5],
    antigo[6], antigo[7], antigo[8],
    antigo[9], antigo[10]);
}

// Função para exibir detalhes de todos os usuários no banco de dados
void todosUsuários(){
    //Declarasção das varravéis SQL em ordem, Conexão, Resultado e Fileira
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	
	conn = mysql_init(NULL); // Inicialização da estrutura MySQL
	
        // Conexão ao banco de dados
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	    // Consulta SQL para selecionar todos os usuárioss
	if (mysql_query(conn, "SELECT * FROM users;")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    res = mysql_store_result(conn); // Armazenamento do resultado da consulta

    // Exibição das informações de cada usuário
    printf("---------------------------------------------------------------------------");
	while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n");
        printf("ID: %s\n", row[0]);
        printf("NOME: %s\n", row[1]);
        printf("TIPO DE CONTA:  %s\n", row[2]);
        printf("SALDO:  %s\n", row[3]);
        printf("CPF:  %s\n", row[4]);
        printf("\n");
    }

    // Liberação de recursos do resultado
	mysql_free_result(res);
    // Fechamento da conexão com o banco de dados
	mysql_close(conn);
}

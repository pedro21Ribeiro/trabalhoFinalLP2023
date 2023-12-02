//Olá mundo
//Comando de compilação: cc main.c funcoes.h funcoes.c  -o main -lmysqlclient

#define tamNome 51//mude para aumentar o tamnho possivel do nome

typedef struct{
    int id;
    char nome[tamNome];
    int tipoDeConta;
    double saldo;
    int cpf;
    int numeroDaConta;
} Conta;

typedef struct{
    int id;
    int sender;
    int reciver;
    double valor;
    char data[11];
} Movimento;


Conta retornoUsers(char query[600]);
Movimento retornoMovimento(int id);
void adicionarUser(char name[51], int tipoDeConta, double saldo, char cpf[15]);
void adicionarMovimento(int sender, int reciver, double valor, char data[11]);
void usersSemRetorno(char query[600]);
Conta buscar_por_nome(char nome[51]);
Conta buscar_por_id(int id);
void add_user_terminal();
void formatarCpf(long long int numCpf, char *cpf);
void add_movimento_terminal();
void transferir_dinheiro(int contaEnvio, int contaRecebimento, double valor);
Conta buscar_por_cpf();

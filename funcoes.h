//Olá mundo
//Comando de compilação: cc main.c funcoes.h funcoes.c  -o main -lmysqlclient

#define MAX 100//Mude  o valor para mudar o numero máximo de usuários
#define tamNome 51//mude para aumentar o tamnho possivel do nome

typedef struct{
    int id;
    char nome[tamNome];
    int tipoDeConta;
    double saldo;
} Conta;

typedef struct{
    int id;
    int sender;
    int reciver;
    double valor;
    char data[11];
} Movimento;

typedef Conta *p_contas;

extern p_contas usuarios[MAX];




int popularVetor(char *arquivo);
int adicionarUsuarios(char *arquivo, char nome[tamNome], int tipoDeConta, double saldo);
Conta retornoUsers(char query[600]);
Movimento retornoMovimento(char query[600]);
void adicionarUser(char nome[51], int tipoDeConta, double saldo);
void adicionarMovimento(int sender, int reciver, double valor, char data[11]);
void usersSemRetorno(char query[600]);
Conta buscar_por_nome(char nome[51]);
Conta buscar_por_id(int id);